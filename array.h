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
	void LeftRotate1(vector<int>& num, int d) {
		if(num.empty()) return;
		int n = num.size();
		d = d % n;
		if(d == 0) return;
		vector<int> tmp(num.begin(), num.begin()+d); //store first k-elements in tmp array
		for(int j = 0; j < n-d; ++j) num[j] = num[j+d];
		for(int j = 0; j < d; ++j) num[j+n-d] = tmp[j];
	}

	/// Left rotation of array (rotate one at a time)
	void LeftRotate2(vector<int>& num, int d) {
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
	void LeftRotate3(vector<int>& num, int d) {
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
	void LeftRotate4(vector<int>& num, int d) {
		if(num.empty()) return;
		int n = num.size();
		d = d % n;
		if(d == 0) return;
		reverse(num, 0, n);
		reverse(num, 0, n-d);
		reverse(num, n-d, n);
	}

	void LeftRotateUtil(vector<int>& num, int beg, int end, int d);

	/// Left rotation of array (block swap algorithm)
	void LeftRotate5(vector<int>& num, int d) {
		if(num.empty()) return;
		int n = num.size();
		d = d % n;
		if(d == 0) return;
		LeftRotateUtil(num, 0, n, d);
	}

	/// Utility function to rotate num's subarray [beg, end) to the left by d
	void LeftRotateUtil(vector<int>& num, int beg, int end, int d) {
		int n = end-beg;
		if(d == n-d) swap(num, beg, beg+d, d); //we are done!
		else if(d < n-d) { //left side shorter
			swap(num, beg, end-d, d);
			LeftRotateUtil(num, beg, end-d, d);
		} else {
			swap(num, beg, beg+d, n-d);
			LeftRotateUtil(num, end-d, end, d-(n-d));
		}
	}
}

#endif
