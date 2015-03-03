#include "array.h"

void testArray(int argc, char* argv[])
{
	int a[8] = {-2, -3, 4, -1, -2, 1, 5, -3};
	cout << "max-subarray (allowing empty) is " << maxSubArray(a, 8) << endl;
	cout << "max-subarray (not allowing empty) is " << maxSubArray2(a, 8) << endl;
	int b[8] = {-2, -3, -4, -1, -2, -1, -5, -3};
	cout << "max-subarray (allowing empty) is " << maxSubArray(b, 8) << endl;
	cout << "max-subarray (not allowing empty) is " << maxSubArray2(b, 8) << endl;
}
