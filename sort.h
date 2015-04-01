#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

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
		return int(p+l*1.0*std::rand()/RAND_MAX);
	}
private:
	bool randomized;
	int method;
};

//select k-th order statistics from arrays
class SelectKth {
public:

	//Binary search algorithm to selelect k-th order statistics from two SORTED arrays. Average O(m+n) time.
	int Select(vector<int> &A, vector<int> &B, int k) {
		int n1 = A.size();
		int n2 = B.size();
		if(n1 == 0) return B[k-1];
		else if(n2 == 0) return A[k-1];
		int idx = SelectUtil(A, B, 0, n1-1, k);
		if(idx >= 0) return A[idx];
		else {
			idx = SelectUtil(B, A, 0, n2-1, k);
			return B[idx];
		}
	}

	//Utility function to find the k-th order static in A+B in A[l .. r]
	int SelectUtil(vector<int> &A, vector<int> &B, int l, int r, int k) {
		cout << "Select ("<<l << " " << r << ") k = " << k <<endl;
		if(r < l) return -1;
		int m = (l+r)/2, n = B.size();
		int x = A[m];
		//x is <= m+1 elements in A, check if x is <= k-(m+1) elements in B
		int q = k-m-1;
		cout << "m = " << m << ", x = " << A[m] <<", q = " << q <<endl;
		if(q < 0) return SelectUtil(A, B, l, m-1, k); //search left (A[l .. m-1])
		else if(q > n) return SelectUtil(A, B, m+1, r, k); //search right (A[m+1 .. r])
		else if(q == 0) {
			if(x <= B[q]) return m;
			else return SelectUtil(A, B, l, m-1, k);
		} else if (q == n) {
			if( x >= B[q-1]) return m;
			else return SelectUtil(A, B, m+1, r, k);
		} else {
			if(x >= B[q-1] && x <= B[q]) return m;
			else if (x > B[q]) return SelectUtil(A, B, l, m-1, k);
			else return SelectUtil(A, B, m+1, r, k);
		}
	}

	//Random algorithm to select k-th order statistics from unsorted array. Expected O(n) time, worst-case O(n2) time
	int RSelect(vector<int> &arr, int k) {
		int n = arr.size();
		return RSelectUtil(arr, 0, n-1, k);
	}

	//Deterministic algorithm to select k-th order statistics from unsorted array. Expected O(n) time, worst-case O(n) time
	int DSelect(vector<int> &arr, int k) {
		int n = arr.size();
		return DSelectUtil(arr, 0, n-1, k);
	}

	//Utility function to select k-th order statistics from sub-array arr[p..r] (random)
	int RSelectUtil(vector<int> &arr, int p, int r, int k) {
		if(p == r) return arr[p]; //only one element in array, just return it
		int i = rand(p, r); 
		swap(arr[i], arr[r]);//use random pivot
		int q = partition(arr, p, r);
		int l = q-p+1;
		if(l == k) return arr[q];
		else if(l > k) return RSelectUtil(arr, p, q-1, k);
		else return RSelectUtil(arr, q+1, r, k-l);
	}

	//Utility function to select k-th order statistics from sub-array arr[p..r] (deteriministic)
	int DSelectUtil(vector<int> &arr, int p, int r, int k) {
		if(p == r) return arr[p]; //only one element in array, just return it

		//find median of medians
		int n = r-p+1, i(0);
		int nmed = (n+4)/5; //number of medians as ceiling of n/5.0, can also use (n-1)/5+1, or n/5 + (n%5!=0)
		vector<int> medians(nmed, 0);
		for(i = 0; i < nmed-1; ++i) medians[i] = findMedian(arr, p+i*5, p+i*5+4);
		medians[i] = findMedian(arr, p+i*5, r); //last one
		int mom = DSelectUtil(medians, 0, nmed-1, nmed/2); // (lower) median of medians

		//find median index using linear search
		int midx = -1;
		for(i = p; i <= r; ++i) {
			if(arr[i] == mom) { 
				midx = i; break; 
			}
		}
		//partition using median of medians
		swap(arr[midx], arr[r]);
		int q = partition(arr, p, r);
		int len = q-p+1;
		if(len == k) return arr[q];
		else if(len > k) return DSelectUtil(arr, p, q-1, k);
		else return DSelectUtil(arr, q+1, r, k-len);
	}

private:

	//find lower median of arr[p..r] using insertion sort
	int findMedian(vector<int> &arr, int p, int r) {
		int i(p), j(p);
		for(i = p+1; i <= r; ++i) {
			int v = arr[i];
			for(j = i-1; j >=p; --j) {
				if(arr[j] > v) arr[j+1] = arr[j];
				else break;
			}
			arr[j+1] = v;
		}
		return arr[(p+r)/2]; //lower median
	}

	//partition of arr[p .. r] using arr[r] as pivot
	int partition(vector<int> &arr, int p, int r) {
		int x = arr[r];
		int i(p), j(p);
		for(j = p; j < r; ++j) {
			if(arr[j] <= x) swap(arr[i++], arr[j]);
		}
		swap(arr[i], arr[r]);
		return i;
	}

	//randomly select a number from p to r
	int rand(int p, int r) {
		return int(p + (r-p+1)*1.0*std::rand()/RAND_MAX);
	}

	void swap(int &a, int &b) {
		int t = a; a = b; b = t;
	}
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
			buckets[unsigned(arr[i]*n)].push_back(arr[i]);
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
