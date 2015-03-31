#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class QuickSort {
public:
	QuickSort(bool r, int m) : randomized(r), method(m) {}

	//qsort
	void sort(vector<int> &arr) {
		int n = arr.size();
		sortUtil(arr, 0, n-1);
	}

	void sortUtil(vector<int> &arr, int p, int r) {
		if(r <= p) return;	
		int q, t;
		if(method == 1) q = partition1(arr, p, r);
		else if(method == 2) q = partition2(arr, p, r);
		else if(method == 3) q = partition3(arr, p, r); //Hoare
		else partition4(arr, p, r, q, t);

		if(method == 1 || method == 2) {
			sortUtil(arr, p, q-1);
			sortUtil(arr, q+1, r);
		} else if(method == 3){ //Hoare
			sortUtil(arr, p, q); 
			sortUtil(arr, q+1, r);
		} else {
			sortUtil(arr, p, q-1); 
			sortUtil(arr, t+1, r);
		}
	}

	//select the i-th order statistic in array
	int select(vector<int> &arr, int i) {
		int n = arr.size();
		if(i < 1 || i > n) exit(1);
		return selectUtil(arr, 0, n-1, i);
	}
	int selectUtil(vector<int> &arr, int p, int r, int i) {
		if(r == p) return arr[p];
		int q = partition1(arr, p, r);
		int k = q-p+1; //length of first half
		if(i == k) return arr[q];
		else if(i < k) return selectUtil(arr, p, q-1, i);
		else return selectUtil(arr, q+1, r, i-k);
	}

	//partition method 1 (CLRS), use arr[r] as pivot
	int partition1(vector<int> &arr, int p, int r) {
		if(randomized) {
			int i = rand(p, r);
			swap(arr[i], arr[r]);
		}

		int x = arr[r];
		int i(p), j(p);
		for(j = p; j < r; ++j) {
			if(arr[j] <= x) swap(arr[i++], arr[j]);
		}
		swap(arr[r], arr[i]);
		return i;
	}

	//partition method 2 (Algorithms in C++), use arr[r] as pivot
	int partition2(vector<int> &arr, int p, int r) {
		if(randomized) {
			int i = rand(p, r);
			swap(arr[i], arr[r]);
		}

		int x = arr[r]; //last element as pivot
		int i = p-1, j = r;
		while(1) {
			while(arr[++i] < x); //A[i] is first element >= x
			while(arr[--j] > x) if(j == p) break; //A[j] is first element <= x
			if(i < j) swap(arr[i], arr[j]);
			else break;
		}
		swap(arr[i], arr[r]);
		return i;
	}

	//method 3: Hoare partition (CLRS), use arr[p] as pivot
	int partition3(vector<int> &arr, int p, int r) {
		if(randomized) {
			int i = rand(p, r);
			swap(arr[i], arr[p]);
		}

		int x = arr[p];
		int i = p-1, j = r+1;
		while(1) {
			while(arr[--j] > x);
			while(arr[++i] < x);
			if(i < j) swap(arr[i], arr[j]);
			else return j;
		}
	}

	//method 4: partition with equal element values (3-color sort)
	void partition4(vector<int> &arr, int p, int r, int &q, int &t) {
		int x = arr[r];
		int lo(p), mid(p), hi(r);
		//arr[p .. lo-1] < x
		//arr[lo .. mid-1] = x
		//arr[mid .. hi] ??
		//arr[hi+1 .. r] > x
		while(mid <= hi) {
			if(arr[mid] < x) swap(arr[lo++], arr[mid++]);
			else if(arr[mid] == x) mid++;
			else swap(arr[mid], arr[hi--]);
		}
		q = lo; t = mid-1;
	}

	void swap(int &a, int &b) {
		int t = a; a = b; b = t;
	}

	int rand(int p, int r) {
		int l = r-p+1;
		return (int) p+l*1.0*std::rand()/RAND_MAX;
	}
private:
	bool randomized;
	int method;
};

//Bucket sort, assume array is uniformly distributed between 0 and 1
class BucketSort {
public:
	void sort(vector<double>& arr) {
		int n = arr.size();
		if(n <= 1) return;
		vector<vector<double> > buckets(n);
		//create buckets
		for(int i = 0; i < n; ++i)
			buckets[arr[i]*n].push_back(arr[i]);
		//sort within buckets
		for(int i = 0; i < n; ++i) 
			std::sort(buckets[i].begin(), buckets[i].end());
		//collect all buckets
		int k = 0;
		for(int i = 0; i < n; ++i) {
			cout << "bucket " << i << " : ";
			for(int j = 0; j < buckets[i].size(); ++j) {
				arr[k++] = buckets[i][j];
				cout << buckets[i][j] << " ";
			}
			cout << endl;
		}
	}
};

class RadixSort {
public:
	RadixSort(int r) : radix(r) {}
	void sort(vector<int>& arr) {
		int n = arr.size();
		if(n <= 1) return;
		int maxnum = arr[0];
		for(int i = 1; i < arr.size(); ++i)
			if(arr[i] > maxnum) maxnum = arr[i];

		for(int exp = 1; exp <= maxnum; exp *= radix)
			countSort(arr, exp);
	}

	//if we know number of digits before hand
	void sort2(vector<int>& arr, int digits) {
		int exp = 1;
		for(int d = 0; d < digits; ++d) {
			countSort(arr, exp);
			exp *= radix;
		}
	}

	//count sort where values (arr[i]/exp)%radix vary from 0 to r-1
	void countSort(vector<int> &arr, int exp) { //exp = 1, 10, 100 ...
		cout << "countSort exp = " <<exp << endl; 
		int n = arr.size();
		vector<int> output(n, 0); //sorted array
		vector<int> count(radix, 0); //0 ~ k-1
		//count
		for(int i = 0; i < n; ++i) count[(arr[i]/exp)%radix] ++;
		for(int j = 1; j < radix; ++j) count[j] += count[j-1];
		//start from back for stableness
		for(int i = n-1; i >= 0; --i) output[--count[(arr[i]/exp)%radix]] = arr[i]; 
		arr = output; //copy result to arr
	}

private:
	int radix;
};

class Heap {
public:
	Heap(int max_l) : maxL(max_l), size(0) {
		head = new int [maxL];
		arr = head-1; //pointer such that first element is arr[1]
		cout << "initializing heap of size " << maxL << endl;
	}
	~Heap() { delete [] head;}

	void Init(int num[], int n) {
		if(n > maxL) {
			cout << "Overflow! " << endl;
			exit(1);
		}
		size = n;
		for(int i = 0; i < n; ++i) head[i] = num[i];
	}

	//build heap
	void BuildHeap() {
		for(int i = size/2; i >= 1; --i) FixDown(i);
	}

	bool Empty() { return size == 0; }

	int GetMax() { return arr[1];}

	int ExtractMax() {
		if(size == 0) { cout << "Underflow!" << endl; exit(2);}
		Swap(arr[size--], arr[1]);
		FixDown(1);
		return arr[size+1];
	}

	//fix down (check if arr[i] needs to be swapped with children)
	void FixDown(int i) {
		while(i > 0) {
			int largest = i;
			int l = Left(i), r = Right(i);
			if( l <= size && arr[l] > arr[largest]) largest = l;
			if( r <= size && arr[r] > arr[largest]) largest = r;
			if(largest != i) {
				Swap(arr[largest], arr[i]);
				i = largest;
			} else break;
		}
	}

	void FixUp(int i) {
		while(i > 1) {
			int p = Parent(i);
			if(arr[p] < arr[i]) {
				Swap(arr[p], arr[i]);
				i = p;
			} else break;
		}
	}

	int Left(int i) {return 2*i;}
	int Right(int i) {return 2*i+1;}
	int Parent(int i) {return i/2;}
	void Swap(int &a, int &b) { int t = a; a = b; b = t;}

private:
	int* head; //point to the head of array
	int* arr; //one less the beginning of array
	int maxL; //max length
	int size; //size
};

#endif
