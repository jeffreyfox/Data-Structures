/// file for dynamic programming
#ifndef DP_H
#define DP_H

#include <vector>

using namespace std;

/// Class to solve longest common subsequence problem (CLRS 15.4)
class LCS {
public:
	/// constructor
	LCS(const string &s, const string &t) {
		if(s.size() > t.size()) { x = s; y = t;} //y has smaller size
		else { x = t; y = s; }
		int m = x.size(), n = y.size();
		//len[i][j] is the length of LCS of x[0..i-1] and y[0..j-1]
		len.resize(m+1, vector<int>(n+1, 0));
	}

	// calculate LCS length using 2D array len
	int LCSLength() {
		int i, j;
		int m = x.size(), n = y.size();
		for(i = 0; i <= m; ++i) len[i][0] = 0;
		for(j = 1; j <= n; ++j) len[0][j] = 0;
		for(i = 1; i <= m; ++i) {
			for(j = 1; j <= n; ++j) {
				if(x[i-1] == y[j-1]) len[i][j] = len[i-1][j-1] + 1;
				else len[i][j] = max(len[i][j-1], len[i-1][j]);
			}
		}
		return len[m][n];
	}

	/// calculate LCS length using 2 1D arrays of size n+1 and O(1) additional space
	int LCSLength2() {
		int i, j;
		int m = x.size(), n = y.size();
		vector<int> curr(n+1, 0), last(n+1, 0); //current row, last row
		for(i = 1; i <= m; ++i) { // loop of rows
			for(j = 1; j <= n; ++j) { // loop within row
				if(x[i-1] == y[j-1]) curr[j] = last[j-1] + 1;
				else curr[j] = max(curr[j-1], last[j]);
				len[i][j] = curr[j]; //fill len[i][j] just for debugging purpose
			}
			last = curr; //update last
		}
		return curr[n];
	}

	/// calculate LCS length using only 1 1D array of size n+1 and O(1) additional space
	int LCSLength3() {
		int i, j;
		int m = x.size(), n = y.size();
		vector<int> curr(n+1, 0);
		int last = 0; //last value of c[i][j-1]
		for(i = 1; i <= m; ++i) { // loop of rows
			last = curr[0];
			for(j = 1; j <= n; ++j) { // loop within row
				int tmp = curr[j]; //old value of curr[j]
				if(x[i-1] == y[j-1]) curr[j] = last + 1;
				else curr[j] = max(curr[j-1], curr[j]);
				len[i][j] = curr[j]; //fill len[i][j] just for debugging purpose
				last = tmp; //update last
			}
		}
		return curr[n];
	}

	/// construct LCS from the len table
	string constructLCS() {
		string lcs;
		int i = x.size(), j = y.size();
		while(i > 0 && j > 0) {
			if(x[i-1] == y[j-1]) { 
				lcs = x[i-1] + lcs; 
				i--; j--;
			} else if(len[i][j-1] > len[i-1][j]) j--;
			else i--;
		}
		return lcs;
	}

	/// print the 2D len table
	void print2D() {
		int m = x.size(), n = y.size();
		for(int i = 1; i <= m; ++i) {
			for(int j = 1; j <= n; ++j) cout << len[i][j] << " ";
			cout << endl;
		}
	}

private:
	string x, y; //strings (y is shorter)
	vector<vector<int> > len; //lengths of LCS of xi and yj
};

/// Class to solve longest increasing subsequence problem (CLRS 15.5)
/// solve function calculate LIS length and constructs the sequence using dynamic programming
class LIS {
public:
	LIS(const vector<int>& vec) : num(vec), n(vec.size()), LISlen(0) {}

	int getLISlen() { return LISlen;}
	vector<int> getLISvec() { return LISvec;}

	/// My method: use two arrays linc and lexc. O(n*n)
	void solve0() {
		vector<int> p(n, -1); //p[i]: num[i]'s predecessor in the LIS of num[0..i] ending at num[i] (i = 0 .. n-1)
		vector<int> linc(n, 0); //len[i]: length of LIS of num[0..i] ending at num[i] (i = 0 .. n-1)
		vector<int> lexc(n, 0); //len[i]: length of LIS of num[0..i] not ending at num[i] (i = 0 .. n-1)
		linc[0] = 1; lexc[0] = 0; //LIS of an array of only one element
		int i, j;
		for(i = 1; i < n; ++i) { // check LIS ending at num[i]
			linc[i] = 1; // length is at least one (subsequence having only num[i])
			lexc[i] = max(linc[i-1], lexc[i-1]);
			for(j = 0; j < i; ++j) {
				if(num[j] <= num[i] && linc[i] < linc[j] + 1) { //found a longer IS ending at num[i]
					linc[i] = linc[j] + 1; //update length of IS ending at num[i]
					p[i] = j; //update predecessor of num[i]
				}
			}
		}
		//find the length of LIS by scanning the len array
		LISlen = max(linc[n-1], lexc[n-1]);

		j = n-1; //find ending position of LIS
		while(lexc[j] > linc[j]) j--;
		//now j is the last element of LIS, construct LIS from p[] array
		while(j != -1) {
			LISvec.insert(LISvec.begin(), num[j]);
			j = p[j];
		}
	}

	/// Standard method: use one array len. O(n*n)
	void solve1() {
		vector<int> p(n, -1); //p[i]: num[i]'s predecessor in the LIS of num[0..i] ending at num[i] (i = 0 .. n-1)
		vector<int> len(n, 0); //len[i]: length of LIS of num[0..i] ending at num[i] (i = 0 .. n-1)
		len[0] = 1; //LIS of an array of only one element
		int i, j;
		for(i = 1; i < n; ++i) { // check LIS ending at num[i]
			len[i] = 1; // length is at least one (subsequence having only num[i])
			for(j = 0; j < i; ++j) {
				if(num[j] <= num[i] && len[i] < len[j] + 1) { //found a longer IS ending at num[i]
					len[i] = len[j] + 1; //update length of IS ending at num[i]
					p[i] = j; //update predecessor of num[i]
				}
			}
		}
		//find the length of LIS by scanning the len array
		LISlen = 0;
		j = -1; //ending position of LIS
		for(i = 0; i < n; ++i) 
			if(len[i] > LISlen) { LISlen = len[i]; j = i;}

			//construct LIS from p[] array
			while(j != -1) {
				LISvec.insert(LISvec.begin(), num[j]);
				j = p[j];
			}
	}

	///  O(n*log n) method, using binary search
	void solve2();

	///  Variant of O(n*log n) method, using binary search
	void solve3();

private:
	vector<int> num; //number array
	int n; //size of array
	int LISlen; //length of LIS
	vector<int> LISvec; //LIS vector
};

#endif
