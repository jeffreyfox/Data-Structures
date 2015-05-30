#include "BSTree.h"
#include "RBTree.h"
#include "IntervalTree.h"

extern ostream& operator<<(ostream& os, const vector<double>& vec);
extern ostream& operator<<(ostream& os, const vector<int>& vec);

void swap(int &a, int &b) 
{
	int t = a; a = b; b = t;
}

void randPerm(vector<int>& num) 
{
	int n = num.size();
	for(int i = 0; i < n; ++i) {
		//random number between i and n-1
		int len = n-i;
		int r = i + len*1.0*rand()/(double(RAND_MAX)+1);
		swap(num[i], num[r]);
	}
}

//brute-force way of counting inversion, O(n2)
int countInversion1(const vector<int>& num)
{
	int n = num.size(), r = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = i+1; j < n; ++j) {
			if(num[i] > num[j]) r++;
		}
	}
	return r;
}

//Red-black tree implementation of counting inversion, O(nlgn)
int countInversion2(const vector<int>& num)
{
	int n = num.size(), r = 0;
	RBTree rbt;
	for(int i = 0; i < n; ++i) {
		RBTreeNode *t = new RBTreeNode(num[i]);
		rbt.insert(t);
		r += rbt.size() - rbt.rank(t);
	}
	return r;
}

//Brute-force method of counting pairs of intersecting chords on a circle, O(n2)
//chords values are permutations of 1 .. 2N. num[0, 1] gives the first chord
int countIntChords1(const vector<int>& chords) 
{
	int n = chords.size()/2; //number of chords
	int c = 0;
	for(int i = 0; i < n; i++) {//chord #i
		for(int j = i+1; j < n; j++) { //chord #j
			int s1 = min(chords[2*i], chords[2*i+1]), e1 = max(chords[2*i], chords[2*i+1]);
			int s2 = min(chords[2*j], chords[2*j+1]), e2 = max(chords[2*j], chords[2*j+1]);
			if( (s1 < s2 && s2 < e1 && e1 < e2) || (s2 < s1 && s1 < e2 && e2 < e1) ) c++;
		}
	}
	return c;
}

//Brute-force method of counting pairs of intersecting chords on a circle, O(n2)
int countIntChords2(const vector<int>& chords)
{
	int np = chords.size(); //number of points
	int nc = chords.size()/2; //number of chords
	int c = 0;
	vector<int> mapping(np+1, 0);
	for(int i = 0; i < np; i += 2) {
		mapping[chords[i]] = chords[i+1];
		mapping[chords[i+1]] = chords[i];
	}

	RBTree rbt;
	for(int i = 1; i <= np; i++) {//point #i
		if(mapping[i] > i) { //starting point of a chord 
			rbt.insert(new RBTreeNode(i));
		} else { //ending point of a chord
			RBTreeNode *t = rbt.search(mapping[i]);
			c += rbt.size() - rbt.rank(t);
			rbt.remove(t);
		}
	}
	return c;
}

void testBST(int argc, char* argv[])
{
	int i = 0, N = 30, m = 100, seed = 800;
	BSTree bst;

	if(seed != 0) { //initialize randomly
		srand(seed);
		for(i = 0; i < 1000000; ++i) rand();
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

	cout << "Removing keys between " << m/4 << " and " << m*3/4 << " ... " << endl;
	for(int k = m/4; k <= m*3/4; k++) {
		BSTreeNode *t = bst.search(k);
		if(t != bst.nullnode()) { 
			cout << "("<<t->key << ") ";
			bst.remove(t);
		}
	}
	cout << endl;
	cout << "Binary search tree in-order : " << endl;
	bst.printInOrder(); cout << endl;
	cout << endl;
}

void testIntervalTree(int argc, char* argv[])
{
	int i = 0, N = 20, m = 50, seed = 800;
	IntervalTree tree;

	srand(seed);
	for(i = 0; i < 1000000; ++i) rand();
	for(i = 0; i < N; ++i) { 
		int r1 = m*(1.0*rand()/RAND_MAX); 
		int r2 = m*(1.0*rand()/RAND_MAX);
		int start = min(r1, r2), end = max(r1, r2);
		if(tree.search(start) == tree.nullnode()) {
			cout << "(" << start << "-" << end << ") ";
			tree.insert(new IntervalTreeNode(Interval(start, end)));
		}
	}
	cout << endl;

	cout << "Binary search tree in-order : " << endl;
	tree.printInOrder(); cout << endl;
	cout << "Binary search tree level-order : " << endl;
	tree.printLevelOrder();
	cout << endl;

	cout << "Removing keys between " << m/4 << " and " << m*3/4 << " ... " << endl;
	for(int k = m/4; k <= m*3/4; k++) {
		IntervalTreeNode *t = tree.search(k);
		if(t != tree.nullnode()) { 
			cout << "("<<t->interval.start << "-" << t->interval.end << ", " << t->max << ") ";
			tree.remove(t);
		}
	}
	cout << endl;
	cout << "Binary search tree in-order : " << endl;
	tree.printInOrder(); cout << endl;
	cout << "Binary search tree level-order : " << endl;
	tree.printLevelOrder();
	cout << endl;
}

void testRBT(int argc, char* argv[])
{
	int i = 0, N = 30, seed = 3;
	RBTree rbt;
	vector<int> num(N);
	if(seed != 0) { //initialize randomly
		srand(seed);
		for(i = 0; i < 100000; ++i) rand();
		for(i = 0; i < N; ++i) num[i] = i+1;
		randPerm(num); //random permutation
		for(i = 0; i < N; ++i) { 
			int key = num[i];	
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

	//test select function
	for(int i = 0; i <= N; ++i) { //i = 0 will return null
		RBTreeNode *t = rbt.select(i);
		if(t != rbt.nullnode()) cout << "(" << i << " " << t->key << ") ";
	}
	cout << endl;

	//test rank function
	for(int i = 0; i <= N; ++i) { //i = 0 will return null
		RBTreeNode *t = rbt.search(i);
		if(t != rbt.nullnode()) cout << "(" << i << " " << rbt.rank2(t) << ") ";
	}
	cout << endl;

	int a = N/4, b = N*3/4;
	cout << "Enumerating keys between " << a << " and " << b << " ... " << endl;
	rbt.enumerate(rbt.rootnode(), a, b);
	cout << endl;

	cout << "Removing keys between " << a << " and " << b << " ... " << endl;
	for(int k = a; k <= b; k++) {
		RBTreeNode *t = rbt.search(k);
		if(t != rbt.nullnode()) { 
			cout << t->key << " ";
			rbt.remove2(t);
		}
	}
	cout << endl;
	cout << "Red-black tree in-order : " << endl;
	rbt.printInOrder(); cout << endl;
	cout << "Red-black tree level-order : " << endl;
	rbt.printLevelOrder();
	cout << endl;

	//count inversion
	int c1, c2;
	c1 = countInversion1(num);
	c2 = countInversion2(num);
	cout << "Number of inversion (brute force) = " << c1 << endl;
	cout << "Number of inversion (RB     tree) = " << c2 << endl;

	c1 = countIntChords1(num);
	c2 = countIntChords2(num);
	cout << "Number of intersecting chord pairs (brute force) = " << c1 << endl;
	cout << "Number of intersecting chord pairs (RB     tree) = " << c2 << endl;
}
