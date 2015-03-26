//file for divide and conquer
#ifndef DEVIDECONQUER_H
#define DEVIDECONQUER_H

#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <cassert>
#include <algorithm>
#include <cfloat>
#include <cmath>

using namespace std;

class MergeSort {
public:
	MergeSort() {}

	void sort(vector<int> &arr) {
		int n = arr.size();
		sortUtil(arr, 0, n-1);
	}

	//sort arr[p..r]
	void sortUtil(vector<int> &arr, int p, int r) {
		if(r > p) { //only sort when sub-array has >1 elements
			int q = p + (r-p)/2;
			sortUtil(arr, p, q); //sort left part
			sortUtil(arr, q+1, r); //sort right part
			merge(arr, p, q, r); //merge two parts
		}
	}

	//merge two sorted arrays arr[p..q] and arr[q+1..r]
	void merge(vector<int> &arr, int p, int q, int r) {
		int L1 = q-p+1, L2 = r-q; //lengths of two parts

		//create temporary arrays with sentinel
		vector<int> left(arr.begin()+p, arr.begin()+p+L1);
		vector<int> right(arr.begin()+q+1, arr.begin()+q+1+L2);
		left.push_back(INT_MAX); right.push_back(INT_MAX); //sentinel

		int i = 0, j = 0;
		for(int k = p; k <= r; ++k) //now put elements back to arr from left and right
			arr[k] = (left[i] <= right[j]) ? left[i++] : right[j++];
	}

private:

};

class TwoSum {
public:
	TwoSum(vector<int>& a, int s) : arr(a), sum(s) {}
	void solve() {
		vector<int> S1(arr), S2;
		unsigned n = arr.size(), i(0);
		MergeSort ms;
		ms.sort(S1); //sort S1
		RemoveDuplicates(S1); //remove duplicates in S1

		n = S1.size(); //update length

		S2 = S1; //construct S2 as sum-S1, in reverse fasion
		for(i = 0; i < n; ++i) S2[i] = sum - S1[n-i-1];

		S1.insert(S1.end(), S2.begin(), S2.end()); 	//combine two array
		ms.merge(S1, 0, n-1, 2*n-1); //merge two sorted arrays

		//check for duplicates
		for(i = 0; i < 2*n-1; ++i) {
			if(S1[i] == S1[i+1]) {
				cout << "Exist two elements : (" << S1[i] << " " << sum - S1[i] << ") whose sum is "<< sum <<endl;
				break;
			}
		}
		if(i == 2*n-1) cout << "Not exist two elements whose sum is "<< sum <<endl;
	}

	//removed duplicates of a sorted array
	void RemoveDuplicates(vector<int>& num) {
		int i(0), j(1), n = num.size();
		int nd(0); //number of duplicates
		while(1) {
			while(j < n && num[j] == num[i]) j++, nd++;
			if(j == n) break;
			//num[j] is first element not equal to num[i]
			num[++i] = num[j++];
		}
		num.resize(n-nd);
	}

private:
	vector<int> arr;
	int sum;
};

class MaxSubArray {
public:
	struct Element {
		int istart, iend, maxSum;
		Element(int is, int ie, int ms) : istart(is), iend(ie), maxSum(ms) {}
		Element() : istart(-1), iend(-1), maxSum(INT_MIN) {}
	};

	MaxSubArray(const vector<int> &ar, bool allow_empty = false) : arr(ar), sol(), allowEmpty(allow_empty) {}

	//Brute force search. O(n2)
	void solve1() {
		sol.maxSum = allowEmpty ? 0 : INT_MIN;
		int sum = 0;
		int i, j, n(arr.size());
		for(i = 0; i < n; ++i) { //starting at i
			sum = 0;
			for(j = i; j < n; ++j) { //ending at j
				sum += arr[j];
				if(sum > sol.maxSum) sol = Element(i, j, sum);
			}
		}
	}

	//divide and conquer O(nlgn)
	void solve2() {
		int n = arr.size();
		sol = solveUtil(0, n-1);
	}

	Element solveUtil(int p, int r) {
		if(r == p) {
			if(allowEmpty) {
				if(arr[p] > 0) return Element(p, p, arr[p]); //istart = iend = p, maxSum = arr[p]
				else return Element(-1, -1, 0); //empty
			} else 
				return Element(p, p, arr[p]); //istart = iend = p, maxSum = arr[p]
		} else {
			int q = p + (r-p)/2;
			Element solL = solveUtil(p, q); //left
			Element solR = solveUtil(q+1, r); //right
			Element solC = getMaxCrossing(p, q, r);
			if(solL.maxSum > solR.maxSum) return solL.maxSum > solC.maxSum ? solL : solC;
			else return solR.maxSum > solC.maxSum ? solR : solC;
		}
	}

	//maximum subarray of arr[p..r] and crossing arr[q]
	Element getMaxCrossing(int p, int q, int r) {
		int i(q), maxiL(q), maxiR(q);
		int sumL(0), sumR(0);
		int maxSumL(0), maxSumR(0);
		//left
		for(i = q-1; i >= p; --i)  {
			sumL += arr[i];
			if(sumL > maxSumL) maxiL = i, maxSumL = sumL;
		}
		//right 
		for(i = q+1; i <= r; ++i)  {
			sumR += arr[i];
			if(sumR > maxSumR) maxiR = i, maxSumR = sumR;
		}
		return Element(maxiL, maxiR, maxSumL+maxSumR+arr[q]);
	}

	//Dynamic programming. O(n)
	void solve3() {
		sol.maxSum = allowEmpty ? 0 : INT_MIN;
		int max_ending_here = 0;
		int n = arr.size();
		int i(0), j(0); //start and end
		for(j = 0; j < n; ++j) { //check sub-array ending at arr[j]
			if(max_ending_here > 0) {
				max_ending_here += arr[j]; //use subarray arr[i..j]
			} else {
				max_ending_here = arr[j]; //use subarray arr[j] only
				i = j; //start at j (only include arr[j])
			}
			//update sol if found a new max
			if(max_ending_here > sol.maxSum) sol = Element(i, j, max_ending_here);
		}
	}

	void printSol() {
		cout << "maximum sum is " << sol.maxSum << ": (";
		if(sol.istart == -1) cout << "NULL";
		else {
			for(int k = sol.istart; k <= sol.iend; ++k) cout << arr[k] << " ";
		}
		cout << ")" << endl;
	}

private:
	vector<int> arr;
	Element sol;
	bool allowEmpty; //allow empty sub-array
};

class ChipTest {
public:
	struct Chip {
		int index;
		char tag;
		Chip() : index(-1), tag('b') {}
		Chip(int i, char t) : index(i), tag(t) {}
	};

	ChipTest(int tot, int bad) : nTot(tot), nBad(bad) { 
		if(nTot - nBad <= nBad) throw std::invalid_argument("Bad chips should be less than half of total!\n");
		chips.resize(nTot);
		for(int k = 0; k < nTot; ++k) chips[k].index = k, chips[k].tag = 'g';
	}

	void init(int seed) {
		srand(seed);
		for(int k = 0; k < nBad; ++k) {
			double rd = rand();
			int idx = 1.0*nTot*rand()/RAND_MAX;
			while(idx >= nTot || chips[idx].tag == 'b') idx = 1.0*rand()*nTot/RAND_MAX;
			chips[idx].tag = 'b';
		}
		print();
	}

	void init(vector<int> bad) {
		for(int k = 0; k < bad.size(); ++k) 
			chips[bad[k]].tag = 'b';
		print();
	}

	void print() {
		cout << nBad << " out of " << nTot << " chips are bad : (";
		for(int k = 0; k < nTot; ++k) 
			if(chips[k].tag == 'b') cout << k << " ";
		cout << ") " << endl;
		cout << nTot - nBad << " out of " << nTot << " chips are good : (";
		for(int k = 0; k < nTot; ++k) 
			if(chips[k].tag == 'g') cout << k << " ";
		cout << ") " << endl;
	}

	int PairTest(Chip chip1, Chip chip2) {
		int t1, t2;
		if(chip1.tag == 'g') t2 = (chip2.tag == 'g') ? 1 : 0; //chip1 is good
		else t2 = (1.0*rand()/RAND_MAX > 0.5) ? 1 : 0; //random
		if(chip2.tag == 'g') t1 = (chip1.tag == 'g') ? 1 : 0; //chip2 is good
		else t1 = (1.0*rand()/RAND_MAX > 0.5) ? 1 : 0; //random
		return (t1 << 1) + t2;
	}

	int findGood() { 
		int idx = findGoodUtil(chips);
		assert(chips[idx].tag == 'g');
		return idx;
	}

	int findGoodUtil(const vector<Chip> &cps) {
		int n = cps.size();
		if(n <= 1) return cps[0].index;
		vector<Chip> newcps;
		for(int k = 0; k+1 < n; k+=2) {
			int res = PairTest(cps[k], cps[k+1]);
			if(res == 3) newcps.push_back(cps[k]); //only keep one of 'good-good'
		}
		//odd case
		if(newcps.size() % 2 == 0) newcps.push_back(cps[n-1]); //the number of pairs is even, add last entry to array
		return findGoodUtil(newcps);
	}

private:
	vector<Chip> chips;
	int nTot;
	int nBad;
};

struct Point {
	double x, y;
	Point(): x(0.0), y(0.0) {}
	Point(double xx, double yy) : x(xx), y(yy) {}
};

bool compareX(Point p1, Point p2) { return p1.x < p2.x; }
bool compareY(Point p1, Point p2) { return p1.y < p2.y; }

class NearestPoints {
public:


	NearestPoints(const vector<Point> &p) : n(p.size()), pts(p) {}

	//O(n2) brute-force solution
	double solve1() {
		double minD = DBL_MAX;
		for(int i = 0; i < n; ++i) {
			for(int j = i+1; j < n; ++j) {
				minD = min(minD, getDist(pts[i],pts[j]));
			}
		}
		return minD;
	}

	//O(nlgn) solution
	double solve2() {
		vector<Point> psx(pts), psy(pts);
		sort(psx.begin(), psx.end(), compareX);//sort x-coordinate
		sort(psy.begin(), psy.end(), compareY);//sort y-coordinate
		return minDist(pts_sort_x, 0, n-1, psy);
	}

	//get minimum distance between points indiced l to r in x-coordinate sorted point array psx.
	//y-coordinate sorted array is used as auxiliary information for strip point search
	double minDist(const vector<Point>& pts_sort_x, int l, int r, const vector<Point>& psy) {
		if(r == l) return DBL_MAX; //only one point
		if(r == l + 1) return getDist(pts_sort_x[l], pts_sort_x[r]); //two points
		int m = (l+r)/2; //middle pivot point
		const Point& pivot = psx[m];
		vector<Point> psy_left, psy_right;//points sort y on the left, right of pivot point
		for(int k = 0; k < psy.size(); ++k) { //partition psy according to pivot
			if(psy[k].x <= pivot.x) psy_left.push_back(psy[k]);
			else psy_right.push_back(psy[k]);
		}
		double minL = minDist(psx, l, m, psy_left);
		double minR = minDist(psx, m+1, r, psy_right);
		double minD = min(minL, minR);
		vector<Point> strip_pts; //strip points (sorted by y-coordinate)
		for(int k = 0; k < psy.size(); ++k) {
			if(fabs(psy[k].x - pivot.x) < minD) strip_pts.push_back(psy[k]); 
		}
		int nstrip = strip_pts.size();
		for(int i = 0; i < nstrip; ++i) { //check all strip points (sorted by y-coordinate)
			for(int j = i+1; j < nstrip && strip_pts[j].y - strip_pts[i].y < minD; ++j) { //at most 7 times
				double dist = getDist(strip_pts[j], strip_pts[i]);
				if(dist < minD) minD = dist;
			}
		}
		return minD;
	}

	double getDist(Point p1, Point p2) {
		return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
	}

private:
	int n; //number of points
	vector<Point> pts;
};

#endif
