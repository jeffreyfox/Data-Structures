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
}

#endif
}

#endif
