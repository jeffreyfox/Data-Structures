//file for divide and conquer
#ifndef DEVIDECONQUER_H
#define DEVIDECONQUER_H

#include <iostream>
#include <vector>
#include <string>
#include <climits>

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

#endif
