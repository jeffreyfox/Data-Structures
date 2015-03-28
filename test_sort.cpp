#include "sort.h"

extern ostream& operator<<(ostream& os, const vector<double>& vec);
extern ostream& operator<<(ostream& os, const vector<int>& vec);

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

	//sort n numbers with values varying from 0 to n3-1. (CLRS 8.3-4)
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
