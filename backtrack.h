/// file for backtracking
#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <vector>
#include <climits>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

class KnightsTour {
public:
	KnightsTour(int nn) : n (nn), step(0) {
		//8 possible moves of the knight
		int xm[8] = {2, 1, -1, -2, -2, -1,  1,  2};
		int ym[8] = {1, 2,  2,  1, -1, -2, -2, -1};
		xmove = vector<int>(xm, xm+8);
		ymove = vector<int>(ym, ym+8);
	}

	///Solve the knigths tour problem
	bool solve() {
		visited.resize(n, vector<bool>(n, false));
		sol.resize(n, vector<int>(n, -1));
		return solveUtil(0, 0);
	}

	//check site (i, j)
	bool solveUtil(int i, int j) {
		visited[i][j] = true;
		sol[i][j] = step++;
		if(step == n*n) return true;
		int newi, newj;
		for(int k = 0; k < 8; ++k) { //try the next move
			newi = i + xmove[k], newj = j + ymove[k];
			if(isValidPos(newi, newj) && !visited[newi][newj]) {
				if(solveUtil(newi, newj)) return true; //found a solution
			}
		}
		//not found a solution, backtrace
		step--;
		sol[i][j] = -1;
		visited[i][j] = false;
		return false;
	}

	void printSol() {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				printf(" %2d ", sol[i][j]);
			}
			printf("\n");
		}
	}
	bool isValidPos(int i, int j) {
		return i >= 0 && i < n && j >= 0 && j < n;
	}
	vector<vector<bool> > visited; 
	vector<vector<int> > sol; // solution (steps)
	int step;

private:
	vector<int> xmove, ymove;
	int n; //dimension of the chess board (n x n)
};

class NQueen {
public:
	NQueen(int nn) : n (nn) {
		col.resize(n, -1);
	}

	///Solve the knigths tour problem
	bool solve() {
		return solveUtil(0);
	}

	//check row i
	bool solveUtil(int i) {
		if(i == n) return true;
		for(int j = 0; j < 8; ++j) { //try the j-th column
			if(canPlace(i, j)) {
				col[i] = j;
				if(solveUtil(i+1)) return true; //found a solution
			}
		}
		//not found a solution, backtrace
		col[i] = -1;
		return false;
	}

	void printSol() {
		for(int i = 0; i < n; ++i) {
			string str(n, '.');
			str[col[i]] = 'Q';
			cout << str << endl;
		}
	}
	bool canPlace(int i, int j) {
		//check attacking positions of already placed ones
		for(int k = 0; k < i; ++k) {
			if(j == col[k] || std::abs(col[k] - j) == i - k) return false;
		}
		return true;
	}

private:
	int n; //dimension of the chess board (n x n)
	vector<int> col;
};

#endif
