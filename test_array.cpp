#include "array.h"

void testArray(int argc, char* argv[])
{
	int a[8] = {-2, -3, 4, -1, -2, 1, 5, -3};
	cout << "max-subarray (allowing empty) is " << maxSubArray(a, sizeof(a)/sizeof(int)) << endl;
	cout << "max-subarray (not allowing empty) is " << maxSubArray2(a, sizeof(a)/sizeof(int)) << endl;
	int b[8] = {-2, -3, -4, -1, -2, -1, -5, -3};
	cout << "max-subarray (allowing empty) is " << maxSubArray(b, sizeof(b)/sizeof(int)) << endl;
	cout << "max-subarray (not allowing empty) is " << maxSubArray2(b, sizeof(b)/sizeof(int)) << endl;
	int c[5] = {3, 2, 5, 10, 7};
	cout << "max-subarray (non-consecutive) is " << maxSubArray3(c, sizeof(c)/sizeof(int)) << endl;

	vector<int> cc(c, c+sizeof(c)/sizeof(int));
	ArrayLib::pair mm = minMax(cc);
	cout << "min, max of array cc is " << mm.min << " " << mm.max << endl;

	int d[] = {1, 2, 8, 10, 10, 12, 19};
	int x = 0;
	vector<int> dd(d, d+sizeof(d)/sizeof(int));
	int ceil_idx = ceiling2(dd, x);
	if(ceil_idx >= 0) cout << "celing of " << x << " in array d = " << dd[ceil_idx] << endl;
	else cout << "celing of " << x << " in array d does not exist!" << endl;

	vector<int> arr(8);
	for(unsigned k = 0; k < arr.size(); ++k) arr[k] = k+1;
	for(unsigned  k = 0; k < arr.size(); ++k) cout << arr[k] << " ";
	cout << endl;
	leftRotate5(arr, 3);
	for(unsigned  k = 0; k < arr.size(); ++k) cout << arr[k] << " ";
	cout << endl;
}
