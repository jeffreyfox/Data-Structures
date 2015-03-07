#include "array.h"

void testArray(int argc, char* argv[])
{
	int a[8] = {-2, -3, 4, -1, -2, 1, 5, -3};
	cout << "max-subarray (allowing empty) is " << maxSubArray(a, 8) << endl;
	cout << "max-subarray (not allowing empty) is " << maxSubArray2(a, 8) << endl;
	int b[8] = {-2, -3, -4, -1, -2, -1, -5, -3};
	cout << "max-subarray (allowing empty) is " << maxSubArray(b, 8) << endl;
	cout << "max-subarray (not allowing empty) is " << maxSubArray2(b, 8) << endl;
	int c[5] = {3, 2, 5, 10, 7};
	cout << "max-subarray (non-consecutive) is " << maxSubArray3(c, sizeof(c)/sizeof(int)) << endl;

	vector<int> arr(8);
	for(unsigned k = 0; k < arr.size(); ++k) arr[k] = k+1;
	for(unsigned  k = 0; k < arr.size(); ++k) cout << arr[k] << " ";
	cout << endl;
	LeftRotate5(arr, 3);
	for(unsigned  k = 0; k < arr.size(); ++k) cout << arr[k] << " ";
	cout << endl;
}
