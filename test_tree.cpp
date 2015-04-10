#include "BSTree.h"
#include "RBTree.h"

extern ostream& operator<<(ostream& os, const vector<double>& vec);
extern ostream& operator<<(ostream& os, const vector<int>& vec);

void testBST(int argc, char* argv[])
{
	int i = 0, N = 13, m = 50, seed = 10;
	BSTree bst;

	if(seed != 0) { //initialize randomly
		srand(seed);
		for(i = 0; i < N; ++i) { 
			int key = m*(1.0*rand()/RAND_MAX); 
			if(bst.search(key) == bst.nullnode()) {
				cout << key << " ";
				bst.insert(new BSTreeNode(key));
			}
		}
		cout << endl;
	} else { //read from stdin
		for(i = 0; i < N; ++i) { 
			int key = i+1; 
			if(bst.search(key) == bst.nullnode()) {
				cout << key << " ";
				bst.insert(new BSTreeNode(key));
			}
		}
		cout << endl;
	}
	cout << "Binary search tree in-order : " << endl;
	bst.printInOrder(); cout << endl;
	cout << "Binary search tree level-order : " << endl;
	bst.printLevelOrder();
	cout << endl;

	cout << "Searching keys upto " << m << " ... " << endl;
	for(int k = 0; k <= m; k+=1) {
		BSTreeNode *t = bst.search(k);
		if(t != bst.nullnode()) { 
			cout << "("<<t->key << ") ";
			bst.remove(t);
		}
	}
	cout << endl;
	cout << "Binary search tree in-order : " << endl;
	bst.printInOrder(); cout << endl;
}

void testRBT(int argc, char* argv[])
{
	int i = 0, N = 13, m = 50, seed = 10;
	RBTree rbt;

	if(seed != 0) { //initialize randomly
		srand(seed);
		for(i = 0; i < N; ++i) { 
			int key = m*(1.0*rand()/RAND_MAX); 
			if(rbt.search(key) == rbt.nullnode()) {
				cout << key << " ";
				rbt.insert(new RBTreeNode(key));
			}
		}
		cout << endl;
	} else { //read from stdin
		for(i = 0; i < N; ++i) { 
			int key = i+1; 
			if(rbt.search(key) == rbt.nullnode()) {
				cout << key << " ";
				rbt.insert(new RBTreeNode(key));
			}
		}
		cout << endl;
	}
	cout << "Red-black tree in-order : " << endl;
	rbt.printInOrder(); cout << endl;
	cout << "Red-black tree level-order : " << endl;
	rbt.printLevelOrder();
	cout << endl;

	cout << "Searching keys upto " << m << " ... " << endl;
	for(int k = 0; k <= m; k+=1) {
		RBTreeNode *t = rbt.search(k);
		if(t != rbt.nullnode()) { 
			cout << "("<<t->key << ") ";
			rbt.remove(t);
		}
	}
	cout << endl;
	cout << "Red-black tree in-order : " << endl;
	rbt.printInOrder(); cout << endl;
}
