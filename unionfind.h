#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>
using namespace std;

class UnionFind {
public:
	UnionFind(int NN) : N(NN) { 
		arr.resize(N);
		for(int k = 0; k < N; ++k) arr[k] = k;
	}
	int Find(int i) { 
		while(arr[i] != i) i = arr[i];
		return i;
	}
	void Union(int i, int j) {
		i = Find(i); j = Find(j); 
		arr[i] = j;
	}
protected:
	int N;
	vector<int> arr;
};
#endif
