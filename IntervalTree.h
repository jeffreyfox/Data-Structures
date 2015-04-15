#ifndef INTERVALTREE_H
#define INTERVALTREE_H

#include <climits>
#include <iostream>
#include <cassert>
#include <deque>
#include <string>
#include <vector>

using namespace std;

struct Interval {
	int start, end;
	Interval(int s, int e) : start(s), end(e) {}
};

struct IntervalTreeNode {
	Interval interval;
	int max; //maximum ending position of subtree rooted at this node
	IntervalTreeNode *left, *right, *parent;
	IntervalTreeNode(Interval i) : interval(i), max(i.end), left(NULL), right(NULL), parent(NULL) {}
	int key() { return interval.start;}
};

//binary search tree
class IntervalTree {
public:
	IntervalTree() { root = NULL;}
	virtual ~IntervalTree() { deleteUtil(root); }

	//check if tree is empty
	bool empty() const { return root == NULL;}
	//return the NULL node
	const IntervalTreeNode* nullnode() const { return NULL;}

	//find the node with given key value (iterative)
	IntervalTreeNode* search(int key) {
		IntervalTreeNode *node = root;
		while(node != NULL && key != node->key()) {
			if(key < node->key()) node = node->left;
			else node = node->right;
		}
		return node; //return when node == NULL (not found), or key matches (found)
	}

	//find minimum and maximum element of tree rooted at z
	IntervalTreeNode* minimum(IntervalTreeNode* z) {
		if(z == NULL) return z;
		while(z->left != NULL) z = z->left;
		return z;
	}
	IntervalTreeNode* maximum(IntervalTreeNode* z) {
		if(z == NULL) return z;
		while(z->right != NULL) z = z->right;
		return z;
	}

	//print tree in-order (recursive)
	void printInOrder() { printInOrderUtil(root); }

	//print tree level-order
	void printLevelOrder()
	{
		deque<IntervalTreeNode*> qt;
		deque<int> ql;
		int level = 0;
		if(root != NULL) { qt.push_back(root); ql.push_back(level);}
		while(!qt.empty()) {
			IntervalTreeNode *n = qt.front(); qt.pop_front();
			int l = ql.front(); ql.pop_front();
			if(l > level) { cout << endl; level ++; }
			printNode(n);
			if(n->left != NULL) { qt.push_back(n->left); ql.push_back(l+1);}
			if(n->right != NULL) { qt.push_back(n->right); ql.push_back(l+1);}
		}
		cout << endl;
	}

	//traverse upwards and decreaase the size of nodes encountered by 1
	void fixMaxUp(IntervalTreeNode *z) {
		while(z != NULL) {
			z->max = z->interval.end;
			if(z->left != NULL) z->max = max(z->max, z->left->max);
			if(z->right != NULL) z->max = max(z->max, z->right->max);
			z = z->parent;
		}
	}

	//insert a node to binary search tree (iterative)
	void insert(IntervalTreeNode *z) {
		z->left = z->right = NULL;
		IntervalTreeNode *x = root, *y = NULL;
		while(x != NULL) {
			x->max = max(x->max, z->max);
			y = x;
			x = (z->key() < x->key()) ? x->left : x->right;
		}
		z->parent = y;
		if(y == NULL) root = z; //tree was empty, update root
		else if(z->key() < y->key()) y->left = z;
		else y->right = z;
	}

	//remove a given node z from the binary search tree
	void remove(IntervalTreeNode *z) {
		IntervalTreeNode *y; //node to be fixed
		if(z->left == NULL) { 
			y = z->parent; transplant(z, z->right);
		} else if(z->right == NULL) {
			y = z->parent; transplant(z, z->left);
		} else { //z has both children, find successor (minimum of z->right)
			y = minimum(z->right); //by definition, y does not have left child
			if(y != z->right) { //y is not z's right child
				transplant(y, y->right); //no need to update left pointer of y->right
				y->right = z->right;
				z->right->parent = y;
			} 
			transplant(z, y);
			y->left = z->left; z->left->parent = y; //neither z->left nor y are NULL
		}
		if(y != NULL) fixMaxUp(y);
		delete z;
	}

protected:

	//Utility function for recursively deleting all elements in subtree rooted at z
	void deleteUtil(IntervalTreeNode *z) {
		if(z == NULL) return;
		deleteUtil(z->left);
		deleteUtil(z->right);
		delete z;
	}

	//left and right rotation of tree around x
	void rotL(IntervalTreeNode *x) {
		IntervalTreeNode *y = x->right;
		x->right = y->left;
		if(y->left != NULL) y->left->parent = x;
		y->parent = x->parent;
		if(x->parent == NULL) root = y;
		else if(x->parent->left == x) x->parent->left = y;
		else x->parent->right = y;
		y->left = x;
		x->parent = y;
		y->max = x->max;
		x->max = max(max(x->left->max, x->right->max), x->interval.end);
	}
	void rotR(IntervalTreeNode *x) {
		IntervalTreeNode *y = x->left;
		x->left = y->right;
		if(y->right != NULL) y->right->parent = x;
		y->parent = x->parent;
		if(x->parent == NULL) root = y;
		else if(x->parent->left == x) x->parent->left = y;
		else x->parent->right = y;
		y->right = x;
		x->parent = y;
		y->max = x->max;
		x->max = max(max(x->left->max, x->right->max), x->interval.end);
	}

	//function to replace subtree rooted at u with subtree rooted at v
	void transplant(IntervalTreeNode *u, IntervalTreeNode *v) {
		if(v != NULL) v->parent = u->parent; // need to check if v is NULL!
		if(u->parent == NULL) root = v; //u was root
		else if(u == u->parent->left) u->parent->left = v; //u was a left child
		else u->parent->right = v; //u was a right child
	}

	//utility function to recursively print all nodes in in-order
	void printInOrderUtil(IntervalTreeNode *z) {
		if(z == NULL) return;
		printInOrderUtil(z->left);
		printNode(z);
		printInOrderUtil(z->right);
	}

	void printNode(IntervalTreeNode *z) { 
		cout << "(" << z->interval.start << "-" << z->interval.end << ", " << z->max << ") ";
	}

	IntervalTreeNode* root; //root node
};

#endif
