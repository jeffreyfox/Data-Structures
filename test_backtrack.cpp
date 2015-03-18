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
