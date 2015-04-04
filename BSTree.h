#ifndef BSTREE_H
#define BSTREE_H

#include <climits>
#include <iostream>
#include <cassert>
#include <deque>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
	int key;
	char color; //color field for red-black tree
	TreeNode *left, *right, *parent;
	TreeNode(int v) : key(v), color('b'), left(0), right(0), parent(0) {} //default black
};

//binary search tree with sentinel null node, and each node has a parent node (not necessary)
class BSTree {
public:
	BSTree() { root = null = new TreeNode(INT_MAX);}
	virtual ~BSTree() { deleteUtil(root); delete(null); }

	//check if tree is empty
	bool empty() const { return root == null;}
	//return the null node
	const TreeNode* nullnode() const { return null;}

	//find the node with given key value (iterative)
	TreeNode* search(int key) {
		TreeNode *node = root;
		while(node != null && key != node->key) {
			if(key < node->key) node = node->left;
			else node = node->right;
		}
		return node; //return when node == null (not found), or key matches (found)
	}
	//find the node with given key value (recursive)
	TreeNode* search2(int key) { return searchUtil(root, key);}

	//find minimum and maximum element of tree rooted at z
	TreeNode* minimum(TreeNode* z) {
		if(z == null) return z;
		while(z->left != null) z = z->left;
		return z;
	}
	TreeNode* maximum(TreeNode* z) {
		if(z == null) return z;
		while(z->right != null) z = z->right;
		return z;
	}

	//find successor and predecessor of a given node z
	TreeNode* successor(TreeNode *z) {
		if(z == null) return z;
		if(z->right != null) return minimum(z->right); //z has right child
		while(z->parent != null && z->parent->right == z)  //z has no right child
			z = z->parent; //find the first left child
		return z->parent;
	}
	TreeNode* predecessor(TreeNode *z) {
		if(z == null) return z;
		if(z->left != null) return maximum(z->left); //z has left child
		while(z->parent != null && z->parent->left == z) // z has no left child
			z = z->parent; //find the first right child
		return z->parent;
	}

	//print tree in-order (recursive)
	void printInOrder() { printInOrderUtil(root); }
	//print tree in-order (using minimum and successor)
	void printInOrder2() {
		TreeNode* node = minimum(root);
		while(node != null) {
			printNode(node);
			node = successor(node);
		}
	}
	//print tree level-order
	void printLevelOrder();

	//insert a node to binary search tree (iterative)
	virtual void insert(TreeNode *z) {
		z->left = z->right = null;
		TreeNode *x = root, *y = null;
		while(x != null) {
			y = x;
			x = (z->key < x->key) ? x->left : x->right;
		}
		z->parent = y;
		if(y == null) root = z; //tree was empty, update root
		else if(z->key < y->key) y->left = z;
		else y->right = z;
	}

	//insert a node to a binary search tree (recursive)
	void insert2(TreeNode *z) { 
		z->left = z->right = null; 
		insertUtil(root, z);
	}

	//remove a given snode z from the binary search tree
	virtual void remove(TreeNode *z) {
		if(z->left == null) transplant(z, z->right); //z has no left child
		else if(z->right == null) transplant(z, z->left); // z has no right child
		else { //z has both children, find successor (minimum of z->right)
			TreeNode *y = minimum(z->right); //by definition, sy does not have left child
			if(y != z->right) { //y is not z's right child
				transplant(y, y->right); //y does not have left child, so no need to update left pointer of y->right
				y->right = z->right;
				z->right->parent = y;
			} 
			transplant(z, y);
			y->left = z->left; z->left->parent = y;
		}
		delete z;
	}

protected:

	//Utility function for recursively searching an element with given key value in subtree rooted at z
	TreeNode* searchUtil(TreeNode *z, int key) {
		if(z == null || key == z->key) return z;
		else if(key < z->key) return searchUtil(z->left, key); //search left
		else return searchUtil(z->right, key); //search right
	}

	//Utility function for recursively inserting an element z into a tree rooted at u, update u if necessary
	void insertUtil(TreeNode *&u, TreeNode *z) { //z's left and right has already been set to null earlier
		if(u == null) { u = z; z->parent = u;}
		else if(z->key < u->key) {
			if(u->left != null) insertUtil(u->left, z);
			else { u->left = z; z->parent = u;}
		} else {
			if(u->right != null) insertUtil(u->right, z);
			else { u->right = z; z->parent = u;}
		}
	}

	//Utility function for recursively deleting all elements in subtree rooted at z
	void deleteUtil(TreeNode *z) {
		if(z == null) return;
		deleteUtil(z->left);
		deleteUtil(z->right);
		delete z;
	}

	//left and right rotation of tree around z
	void rotL(TreeNode *z);
	void rotR(TreeNode *z);

	//function to replace subtree rooted at u with subtree rooted at v
	void transplant(TreeNode *u, TreeNode *v) {
		v->parent = u->parent; //with sentinel, no need to check if v is NULL
		if(u->parent == null) root = v; //u was root
		else if(u == u->parent->left) u->parent->left = v; //u was a left child
		else u->parent->right = v; //u was a right child
	}

	//utility function to recursively print all nodes in in-order
	void printInOrderUtil(TreeNode *node); 
	virtual void printNode(TreeNode *node) { cout << node->key << " ";	}

	TreeNode* root; //root node
	TreeNode* null; //sentinel node
};

void BSTree::printLevelOrder()
{
	deque<TreeNode*> qt;
	deque<int> ql;
	int level = 0;
	if(root != null) { qt.push_back(root); ql.push_back(level);}
	while(!qt.empty()) {
		TreeNode *n = qt.front(); qt.pop_front();
		int l = ql.front(); ql.pop_front();
		if(l > level) { cout << endl; level ++; }
		printNode(n);
		if(n->left != null) { qt.push_back(n->left); ql.push_back(l+1);}
		if(n->right != null) { qt.push_back(n->right); ql.push_back(l+1);}
	}
	cout << endl;
}

void BSTree::rotL(TreeNode *x) {
	TreeNode *y = x->right;
	//move y's left to x's right
	x->right = y->left;
	if(y->left != null) y->left->parent = x;
	//fix pointers between x and x's parent (if exist)
	y->parent = x->parent;
	if(x->parent == null) root = y;
	else if(x->parent->left == x) x->parent->left = y;
	else x->parent->right = y;
	//pointers betwen x and y
	y->left = x;
	x->parent = y;
}

void BSTree::rotR(TreeNode *x) {
	TreeNode *y = x->left;
	//move y's right to x's left
	x->left = y->right;
	if(y->right != null) y->right->parent = x;
	//fix pointers between x and x's parent (if exist)
	y->parent = x->parent;
	if(x->parent == null) root = y;
	else if(x->parent->left == x) x->parent->left = y;
	else x->parent->right = y;
	//pointers betwen x and y
	y->right = x;
	x->parent = y;
}

void BSTree::printInOrderUtil(TreeNode *z) {
	if(z == null) return;
	printInOrderUtil(z->left);
	printNode(z);
	printInOrderUtil(z->right);
}

#endif
