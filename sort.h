#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
