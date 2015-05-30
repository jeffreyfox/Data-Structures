#include "sort.h"

extern ostream& operator<<(ostream& os, const vector<double>& vec);
extern ostream& operator<<(ostream& os, const vector<int>& vec);

void testOrderStatistics(int argc, char* argv[])
{
	int num2[] = {13,19,9,5,12,8,7,4,21,2,6,11};
	int n2 = sizeof(num2)/sizeof(int);

	SelectKth sol;
	for(int i = 1; i <= n2; ++i) {
		vector<int> arr5(num2, num2+n2), arr6(arr5);
		int v1 = sol.RSelect(arr5, i);
		int v2 = sol.DSelect(arr6, i);
		if(v1 == v2) cout << "Order static " << i << " of array is " << v1 << endl;
		else cout << "Error! Inconsistent order static " << i << " of array !" << endl;
	}

	const int m = 0, n = 22;
	int r = 300;
	int seed = 20;
	srand(seed);
	vector<int> A(m, 0), B(n, 0), C(m+n, 0);
	for(int i = 0; i < m; ++i) {
		C[i] = A[i] = r*1.0*rand()/RAND_MAX;		
	}
	for(int i = 0; i < n; ++i) {
		C[i+m] = B[i] = r*1.0*rand()/RAND_MAX;
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	sort(C.begin(), C.end());
	cout << A << endl;
	cout << B << endl;
	cout << C << endl;
	for(int i = 1; i <= m+n; ++i) {
		int v = sol.Select(A, B, i);
		cout << i << "-th order statistic of array is " << v << endl;
	}
}

void testQuickSort(int argc, char* argv[])
{
	int seed = 23;
	srand(seed);
	bool random = false;
	QuickSort qs1(random, 1), qs2(random, 2), qs3(random, 3), qs4(random, 4);
	int num[] = {13,19,9,5,12,8,7,4,21,2,6,11};
	//	int num[20];
	//	for(int k = 0; k < 20; ++k) num[k] = 5*1.0*rand()/RAND_MAX;
	int n = sizeof(num)/sizeof(int);
	vector<int> arr1(num, num+n), arr2 = arr1, arr3 = arr1, arr4 = arr1;
	cout << arr1 << endl;

	qs1.sort(arr1);
	cout << arr1 << endl;

	qs2.sort(arr2);
	cout << arr2 << endl;

	qs3.sort(arr3);
	cout << arr3 << endl;

	qs4.sort(arr4);
	cout << arr4 << endl;

}

void testBucketSort(int argc, char* argv[])
{
	BucketSort bsort;
	int n = 20;
	int seed = 20;
	srand(seed);
	vector<double> num(n, 0);
	for(int i = 0; i < n; ++i) {
		num[i] = 1.0*rand()/RAND_MAX;
	}
	cout << num << endl;
	bsort.sort(num);
	cout << num << endl;
}

void testRadixSort(int argc, char* argv[])
{
	RadixSort rsort(10);

	int n = 10, m = 10000;
	int seed = 20;
	srand(seed);
	vector<int> num(n, 0);
	for(int i = 0; i < n; ++i) {
		num[i] = m*1.0*rand()/RAND_MAX;
	}
	cout << num << endl;
	rsort.sort(num);
	cout << num << endl;

	//sort n numbers with values varying from 0 to n3-1.
	n = 13;
	RadixSort rsort2(n);  // use n as radix
	vector<int> num2(n, 0);
	for(int i = 0; i < n; ++i) {
		num2[i] = n*n*n*1.0*rand()/RAND_MAX;
	}
	cout << num2 << endl;
	rsort2.sort2(num2, 3);
	cout << num2 << endl;
}

void testHeap(int argc, char* argv[])
{
	const int n = 10, m = 300;
	int seed = 200;
	srand(seed);
	int num[n] = {0};
	for(int i = 0; i < n; ++i) {
		num[i] = m*1.0*rand()/RAND_MAX;
	}
	for(int i = 0; i < n; ++i) cout << num[i] << " ";
	cout << endl;
	Heap hp(100);
	hp.Init(num, n);
	hp.BuildHeap();
	while(!hp.Empty()) {
		int max = hp.ExtractMax();
		cout << max << " ";
	}
	cout << endl;
}
