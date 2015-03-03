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
}

#endif
