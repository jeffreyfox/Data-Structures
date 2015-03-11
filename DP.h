/// file for dynamic programming
#ifndef DP_H
#define DP_H

#include <vector>

using namespace std;

/// Class to solve longest common sequence problem (CLRS 15.4)
class LCS {
public:
	/// constructor
	LCS(const string &s, const string &t) : x(s), y(t) {
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

	void print2D() {
		int m = x.size(), n = y.size();
		for(int i = 0; i <= m; ++i) {
			for(int j = 0; j <= n; ++j) cout << len[i][j] << " ";
			cout << endl;
		}
	}


private:
	string x, y;
	vector<vector<int> > len; //lengths of LCS of xi and yj
};

#endif
