#include "DivideConquer.h"

extern ostream& operator<<(ostream& os, const vector<double>& vec);
extern ostream& operator<<(ostream& os, const vector<int>& vec);

void testDivideConquer(int argc, char* argv[])
{
	MergeSort ms;
	int tmp[] = {2, 4, 5, 7, 1, 2, 3, 6};
	vector<int> arr(tmp, tmp+sizeof(tmp)/sizeof(int));
	cout << "Before sort, arr = " << arr << endl;
	ms.sort(arr);
	cout << "After  sort, arr = " << arr << endl;

	int aa[] = {4, 2, 7, 9, 11, 6};
	vector<int> arr2(aa, aa+sizeof(aa)/sizeof(int));
	int sum = 12;
	TwoSum ts(arr2, sum);
	ts.solve();

	int bb[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	//int bb[] = {-13, -3, -25, -20};
	vector<int> b(bb, bb+sizeof(bb)/sizeof(int));
	MaxSubArray test1(b), test2(b), test3(b);
	test1.solve1(); test1.printSol();
	test2.solve2(); test2.printSol();
	test3.solve3(); test3.printSol();

	MaxSubArray test4(b, true), test5(b, true), test6(b, true);
	test4.solve1(); test4.printSol();
	test5.solve2(); test5.printSol();
	test6.solve3(); test6.printSol();
}
