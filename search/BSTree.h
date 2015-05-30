#ifndef BSTREE_H
#define BSTREE_H

#include <climits>
#include <iostream>
#include <cassert>
#include <deque>
#include <string>
#include <vector>

using namespace std;

struct BSTreeNode {
	int key;
	BSTreeNode *left, *right, *parent;
	BSTreeNode(int v) : key(v), left(NULL), right(NULL), parent(NULL) {}
};

//binary search tree
class BSTree {
public:
	BSTree() { root = NULL;}
	virtual ~BSTree() { deleteUtil(root); }

	//check if tree is empty
	bool empty() const { return root == NULL;}
	//return the NULL node
	const BSTreeNode* nullnode() const { return NULL;}

	//find the node with given key value (iterative)
	BSTreeNode* search(int key) {
		BSTreeNode *node = root;
		while(node != NULL && key != node->key) {
			if(key < node->key) node = node->left;
			else node = node->right;
		}
		return node; //return when node == NULL (not found), or key matches (found)
	}
	//find the node with given key value (recursive)
	BSTreeNode* search2(int key) { return searchUtil(root, key);}

	//find minimum and maximum element of tree rooted at z
	BSTreeNode* minimum(BSTreeNode* z) {
		if(z == NULL) return z;
		while(z->left != NULL) z = z->left;
		return z;
	}
	BSTreeNode* maximum(BSTreeNode* z) {
		if(z == NULL) return z;
		while(z->right != NULL) z = z->right;
		return z;
	}

	//find successor and predecessor of a given node z
	BSTreeNode* successor(BSTreeNode *z) {
		if(z == NULL) return z;
		if(z->right != NULL) return minimum(z->right); //z has right child
		while(z->parent != NULL && z->parent->right == z)  //z has no right child
			z = z->parent; //find the first left child
		return z->parent;
	}
	BSTreeNode* predecessor(BSTreeNode *z) {
		if(z == NULL) return z;
		if(z->left != NULL) return maximum(z->left); //z has left child
		while(z->parent != NULL && z->parent->left == z) // z has no left child
			z = z->parent; //find the first right child
		return z->parent;
	}

	//print tree in-order (recursive)
	void printInOrder() { printInOrderUtil(root); }
	//print tree in-order (using minimum and successor)
	void printInOrder2() {
		BSTreeNode* node = minimum(root);
		while(node != NULL) {
			printNode(node);
			node = successor(node);
		}
	}
	//print tree level-order
	void printLevelOrder() {
		deque<BSTreeNode*> qt;
		deque<int> ql;
		int level = 0;
		if(root != NULL) { qt.push_back(root); ql.push_back(level);}
		while(!qt.empty()) {
			BSTreeNode *n = qt.front(); qt.pop_front();
			int l = ql.front(); ql.pop_front();
			if(l > level) { cout << endl; level ++; }
			printNode(n);
			if(n->left != NULL) { qt.push_back(n->left); ql.push_back(l+1);}
			if(n->right != NULL) { qt.push_back(n->right); ql.push_back(l+1);}
		}
		cout << endl;
	}

	//insert a node to binary search tree (iterative)
	void insert(BSTreeNode *z) {
		z->left = z->right = NULL;
		BSTreeNode *x = root, *y = NULL;
		while(x != NULL) {
			y = x;
			x = (z->key < x->key) ? x->left : x->right;
		}
		z->parent = y;
		if(y == NULL) root = z; //tree was empty, update root
		else if(z->key < y->key) y->left = z;
		else y->right = z;
	}

	//insert a node to a binary search tree (recursive)
	void insert2(BSTreeNode *z) { 
		z->parent = z->left = z->right = NULL;
		if(root == NULL) root = z;
		else insertUtil(root, z);
	}

	//remove a given node z from the binary search tree
	void remove(BSTreeNode *z) {
		if(z->left == NULL) transplant(z, z->right); //z has no left child
		else if(z->right == NULL) transplant(z, z->left); // z has no right child
		else { //z has both children, find successor (minimum of z->right)
			BSTreeNode *y = minimum(z->right); //by definition, y does not have left child
			if(y != z->right) { //y is not z's right child
				transplant(y, y->right); //no need to update left pointer of y->right
				y->right = z->right;
				z->right->parent = y;
			} 
			transplant(z, y);
			y->left = z->left; z->left->parent = y; //neither z->left nor y are NULL
		}
		delete z;
	}

	//remove a given node z from the binary search tree (flipping)
	void remove2(BSTreeNode *z) {
		if(z->left == NULL) { transplant(z, z->right); delete z; }//z has no left child
		else if(z->right == NULL) { transplant(z, z->left); delete z; } // z has no right child
		else { //z has both children, find successor (minimum of z->right)
			BSTreeNode *y = minimum(z->right); //by definition, y does not have left child
			z->key = y->key; //replace z with y
			transplant(y, y->right);
			delete y;
		}
	}

protected:

	//Utility function for recursively searching an element with given key value in subtree rooted at z
	BSTreeNode* searchUtil(BSTreeNode *z, int key) {
		if(z == NULL || key == z->key) return z;
		else if(key < z->key) return searchUtil(z->left, key); //search left
		else return searchUtil(z->right, key); //search right
	}

	//Utility function for inserting z to tree rooted at u, update u when needed
	void insertUtil(BSTreeNode *u, BSTreeNode *z) { //u is not NULL
		if(z->key < u->key) {
			if(u->left != NULL) insertUtil(u->left, z);
			else { u->left = z; z->parent = u; }
		} else {
			if(u->right != NULL) insertUtil(u->right, z);
			else { u->right = z; z->parent = u; }
		}
	}

	//Utility function for recursively deleting all elements in subtree rooted at z
	void deleteUtil(BSTreeNode *z) {
		if(z == NULL) return;
		deleteUtil(z->left);
		deleteUtil(z->right);
		delete z;
	}

	//left and right rotation of tree around x
	void rotL(BSTreeNode *x) {
		BSTreeNode *y = x->right;
		//move y's left to x's right
		x->right = y->left;
		if(y->left != NULL) y->left->parent = x;
		//fix pointers between x and x's parent (if exist)
		y->parent = x->parent;
		if(x->parent == NULL) root = y;
		else if(x->parent->left == x) x->parent->left = y;
		else x->parent->right = y;
		//pointers betwen x and y
		y->left = x;
		x->parent = y;
	}
	void rotR(BSTreeNode *x) {
		BSTreeNode *y = x->left;
		//move y's right to x's left
		x->left = y->right;
		if(y->right != NULL) y->right->parent = x;
		//fix pointers between x and x's parent (if exist)
		y->parent = x->parent;
		if(x->parent == NULL) root = y;
		else if(x->parent->left == x) x->parent->left = y;
		else x->parent->right = y;
		//pointers betwen x and y
		y->right = x;
		x->parent = y;
	}

	//function to replace subtree rooted at u with subtree rooted at v
	void transplant(BSTreeNode *u, BSTreeNode *v) {
		if(v != NULL) v->parent = u->parent; // need to check if v is NULL!
		if(u->parent == NULL) root = v; //u was root
		else if(u == u->parent->left) u->parent->left = v; //u was a left child
		else u->parent->right = v; //u was a right child
	}

	//utility function to recursively print all nodes in in-order
	void printInOrderUtil(BSTreeNode *z) {
		if(z == NULL) return;
		printInOrderUtil(z->left);
		printNode(z);
		printInOrderUtil(z->right);
	}
	void printNode(BSTreeNode *z) { cout << z->key << " ";	}

	BSTreeNode* root; //root node
};

#endif
