#include "backtrack.h"

void testKnightsTour(int argc, char* argv[])
{
	int n = 8;
	KnightsTour kt(n);
	bool success = kt.solve();
	if(success) kt.printSol();
	else cout << "Solution does not exist! " << endl;
}

void testNQueen(int argc, char* argv[])
{
  int n = 8;
	NQueen nq(n);
	bool success = nq.solve();
	if(success) nq.printSol();
	else cout << "Solution does not exist! " << endl;
}

void testSudoku(int argc, char* argv[])
{
	const int N = 9;
	int grid[N][N] = {
		{3, 0, 6, 5, 0, 8, 4, 0, 0},
		{5, 2, 0, 0, 0, 0, 0, 0, 0},
		{0, 8, 7, 0, 0, 0, 0, 3, 1},
		{0, 0, 3, 0, 1, 0, 0, 8, 0},
		{9, 0, 0, 8, 6, 3, 0, 0, 5},
		{0, 5, 0, 0, 9, 0, 6, 0, 0},
		{1, 3, 0, 0, 0, 0, 2, 5, 0},
		{0, 0, 0, 0, 0, 0, 0, 7, 4},
		{0, 0, 5, 2, 0, 6, 3, 0, 0}};
		vector<vector<int> > g(N, vector<int>(N, 0));
		for(int i = 0; i < N; ++i) 
			for(int j = 0; j < N; ++j) 
				g[i][j] = grid[i][j];
		Sudoku sdk(N, g);
		bool success = sdk.solve();
		if(success) cout << "Found a solution." << endl;
		else cout << "Solutoin not found!" << endl;
		sdk.printSol();
}
