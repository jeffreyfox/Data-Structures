#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
#include <algorithm>

using namespace std;

namespace ArrayLib {

	/// Find the contiguous subarray within an array (can be empty) which has the largest sum.
	int maxSubArray(int num[], int n) {
		int max_ending_here(0), max_all(INT_MIN);
		for(int k = 0; k < n; ++k) {
			max_ending_here = max(0, max_ending_here + num[k]);
			max_all = max(max_ending_here, max_all);
		}
		return max_all;
	}

	/// Find the contiguous subarray within an array (cannot be empty) which has the largest sum.
	int maxSubArray2(int num[], int n) {
		int max_ending_here(0), max_all(INT_MIN);
		for(int k = 0; k < n; ++k) {
			max_ending_here = max(0, max_ending_here) + num[k];
			max_all = max(max_ending_here, max_all);
		}
		return max_all;
	}

	/// Find the maximum sum of a subsequence with the constraint that no 2 numbers in the sequence 
	/// should be adjacent in the array. 
	int maxSubArray3(int num[], int n) {
		int max_ending_here(INT_MIN), max_not_ending_here(INT_MIN);
		for(int k = 0; k < n; ++k) {
			int new_max_ending_here = max(max_not_ending_here, 0) + num[k];
			max_not_ending_here = max(max_ending_here, max_not_ending_here);
			max_ending_here = new_max_ending_here;
		}
		return max(max_not_ending_here, max_ending_here);
	}

	/// Find the index of the ceiling of x in num (linear search)
	int ceiling1(const vector<int>& num, int x) {
		unsigned i = 0;
		while(i < num.size() && num[i] < x) i++;
		if(i == num.size()) return -1;
		else return i; //i is the first element >= x
	}

	/// Find the index of the ceiling of x in num (binary search)
	int ceiling2(const vector<int>& num, int x) {
		//[0, lo-1] < x
		//[hi+1, n] >= x
		//[lo, hi] undetermined
		int n = num.size();
		if(x > num.back()) return -1;
		int lo(0), hi(n-1), mid(0);
		while(lo <= hi) {
			mid = lo + (hi-lo)/2;
			if(num[mid] < x) lo = mid+1;
			else hi = mid-1;
		}
		return lo; //here lo = hi+1
	}

	struct pair {
		int min;
		int max;
		pair(): min(0), max(0) {}
		pair(int mn, int mx) : min(mn), max(mx) {}
	};

	struct pair minMax(const vector<int>& num) {
		int n = num.size();
		assert(n >= 0);
		if(n == 1) return pair(num[0], num[0]);
		int min(0), max(0), tmin(0), tmax(0);
		if(num[0] > num[1]) { max = num[0]; min = num[1]; }
		else { min = num[0]; max = num[1]; }
		int j;
		for(j = 2; j+1 < n; j += 2) {
			if(num[j] > num[j+1]) { tmax = num[j]; tmin = num[j+1]; }
			else { tmin = num[j]; tmax = num[j+1]; }
			if(tmax > max) max = tmax;
			if(tmin < min) min = tmin;
		}
		return pair(min, max);
	}

	/// Find the smallest positive number missing from the array in O(n) time using constant extra space
	int firstMissingPositive(vector<int>& num) {
		int n = num.size();
		int i, j;
		//for all k >= 0, num[k] should contain k+1;
		for(i = 0; i < n; ++i) {
			while(num[i] >= 1 && num[i] <= n && num[i] != i+1) {
				j = num[i]-1; //destination index
				if(num[i] != num[j]) swap(num[i], num[j]); 
				else break; //need this to avoid infinite loop! e.g [1,1]
			}
		}
		for(i = 0; i < n; ++i) 
			if(num[i] != i+1) return i+1;
		return i+1;
	}

	/// Slightly different form	
	int firstMissingPositive2(vector<int>& num) {
		int n = num.size();
		int i(0), j(0), toFill(-1);
		for(; i < n; ++i) {
			toFill = -1;
			j = i; 
			while(j >= 0 && j < n && num[j] != j+1) {
				swap(toFill, num[j]);
				j = toFill-1; //destination of toFill value
			}
		}

		for(i = 0; i < n; ++i)
			if(num[i] != i+1) return i+1;
		return i+1;
	}

	/// 2-color sort followed by tagging positive as negative
	int firstMissingPositive3(vector<int>& num) {
		int n = num.size();
		//first segregate non-positive numbers to back (2-color sort)
		int lo(0), hi(n-1);
		while(lo <= hi) {
			if(num[lo] > 0) lo++;
			else swap(num[lo], num[hi--]);
		}
		int i(0), j(0);
		//now hi is the end of positive numbers, lo is start of negative numbers
		//if found one integer, mark corresponding entry to negative
		for(i = 0; i < lo; ++i) {
			int j = abs(num[i]) -1; // j is always positive
			if(j < lo && num[j] > 0)  num[j] = -num[j];
		}
		//the first positive number is the one
		for(i = 0; i < lo; ++i) 
			if(num[i] > 0) return i+1;
		return i+1;  
	}

	/// Swap
	void swap(int &a, int &b) {
		int t = a; a = b; b = t;
	}

	/// calculate gcd
	int gcd(int a, int b) {
		assert(a && b);
		if(a == 1 || b == 1) return 1;
		if(a == b) return a;
		if(a > b) return gcd(a-b, b);
		else return gcd(a, b-a);
	}

	/// Reverse an array between beg and end-1
	void reverse(vector<int>& num, int beg, int end) {
		int n = end - beg;
		for(int i = 0; i < n/2; ++i) {
			swap(num[beg+i],num[end-1-i]);
		}
	}

	/// Block swap array segments starting at s1, s2 with length of len
	void swap(vector<int>& num, int s1, int s2, int len) {
		for(int i = 0; i < len; ++i) swap(num[s1+i], num[s2+i]);
	}

	/// Left rotation of array (using temporary array)
	void leftRotate1(vector<int>& num, int d) {
		if(num.empty()) return;
		int n = num.size();
		d = d % n;
		if(d == 0) return;
		vector<int> tmp(num.begin(), num.begin()+d); //store first k-elements in tmp array
		for(int j = 0; j < n-d; ++j) num[j] = num[j+d];
		for(int j = 0; j < d; ++j) num[j+n-d] = tmp[j];
	}

	/// Left rotation of array (rotate one at a time)
	void leftRotate2(vector<int>& num, int d) {
		if(num.empty()) return;
		int n = num.size();
		d = d % n;
		if(d == 0) return;
		for(int j = 0; j < d; ++j) { 
			//shift array to left by one step
			int tmp = num[0];
			for(int i = 0; i < n-1; ++i) num[i] = num[i+1];
			num[n-1] = tmp;
		}
	}

	/// Left rotation of array (juggling algorithm)
	void leftRotate3(vector<int>& num, int d) {
		if(num.empty()) return;
		int n = num.size();
		d = d % n;
		if(d == 0) return;
		int i(0), j(0), k(0), tmp(0);
		for(i = 0; i < gcd(n, d); ++i) {
			tmp = num[i];
			j = i;
			while(1) {
				k = (j+d)%n;
				if(k == i) break; //k reaches i, j is one step before
				num[j] = num[k];
				j = k;
			}
			num[j] = tmp;
		}
	}

	/// Left rotation of array (revesal algorithm)
	void leftRotate4(vector<int>& num, int d) {
		if(num.empty()) return;
		int n = num.size();
		d = d % n;
		if(d == 0) return;
		reverse(num, 0, n);
		reverse(num, 0, n-d);
		reverse(num, n-d, n);
	}

	void leftRotateUtil(vector<int>& num, int beg, int end, int d);

	/// Left rotation of array (block swap algorithm)
	void leftRotate5(vector<int>& num, int d) {
		if(num.empty()) return;
		int n = num.size();
		d = d % n;
		if(d == 0) return;
		leftRotateUtil(num, 0, n, d);
	}

	/// Utility function to rotate num's subarray [beg, end) to the left by d
	void leftRotateUtil(vector<int>& num, int beg, int end, int d) {
		int n = end-beg;
		if(d == n-d) swap(num, beg, beg+d, d); //we are done!
		else if(d < n-d) { //left side shorter
			swap(num, beg, end-d, d);
			leftRotateUtil(num, beg, end-d, d);
		} else {
			swap(num, beg, beg+d, n-d);
			leftRotateUtil(num, end-d, end, d-(n-d));
		}
	}
}

#endif
