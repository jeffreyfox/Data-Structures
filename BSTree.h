#ifndef RBTREE_H
#define RBTREE_H

#include "BSTree.h"

class RBTree : public BSTree {
public:
	RBTree() : BSTree() {};
	virtual ~RBTree() {};

	virtual void insert(TreeNode *z);
	virtual void remove(TreeNode *z);
	bool isValid() { return isValid(root); } 

private: 
	virtual void printNode(TreeNode *node);
	void insertFixUp(TreeNode *z);
	void removeFixUp(TreeNode *x);
	bool isValid(TreeNode *h);
};

bool RBTree::isValid(TreeNode *h) {
	if(h == null) {
		if(h->color == 'r') cout <<"Invalid: null is red " <<endl;
		return h->color == 'b';
	}
	if(h == root) {
		if(h->color == 'r') { 
			cout <<"Invalid: root is red " <<endl;
			return false;
		}
	}
	if(h->color == 'r') {
		if(h->left->color == 'r' || h->right->color == 'r') {
			cout <<"Invalid: double red " << endl;
			return false;
		}
	}
	if(h != root) {
		if(h->parent->left != h && h->parent->right != h) {
			cout <<"Invalid: inconsistent parent child pointers " << endl;
		}
	}
	return isValid(h->left) && isValid(h->right);
}

void RBTree::insert(TreeNode *z) {
	BSTree::insert(z);
	z->color = 'r';
	insertFixUp(z);
}

void RBTree::remove(TreeNode *z) {
	TreeNode *y = z, *x(NULL);
	char yc = y->color;
	if(z->left == null) { 
		x = z->right;
		transplant(z, z->right);
	} else if(z->right == null) {
		x = z->left;
		transplant(z, z->left);
	} else { //at this point z->left and z->right both exist
		y = minimum(z->right);//find successor of z
		yc = y->color;
		x = y->right;//the node where y's blackness will be pushed into
		if(y->parent != z) {
			transplant(y, y->right);
			y->right = z->right; //right part of z
			y->right->parent = y; //also does for x is null case
		} else {
			x->parent = y; //for x is null case
		}
		transplant(z, y);
		//left part of z
		y->left = z->left;
		y->left->parent = y; //z->left surely exist
		y->color = z->color;
	}
	if(yc == 'b') removeFixUp(x);
}

void RBTree::insertFixUp(TreeNode *z) {
	while(z->parent->color == 'r') { //z and z->p double red
		//z->p->p exists and should be a black node (because root can't be red)
		if(z->parent == z->parent->parent->left) { //case 1, z->p is left child
			TreeNode *y = z->parent->parent->right; //y is x's uncle
			if(y->color == 'r') { //case 1.1, uncle is red, recolor, and continue
				y->color = z->parent->color = 'b';
				z->parent->parent->color = 'r';
				z = z->parent->parent; //move x to x->p->p, continue loop
			} else { 
				//case 1.2, uncle is black, and z is inner child, rotate to 1.3
				if(z == z->parent->right) {
					z = z->parent; rotL(z);
				}
				//case 1.3, uncle is black, and z is outer child, rotate z->p-> and recolor
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				rotR(z->parent->parent);
			}
		} else { //case 2, z->p is right child
			TreeNode *y = z->parent->parent->left; //y is x's uncle
			if(y->color == 'r') { //case 2.1, uncle is red, recolor, and continue
				y->color = z->parent->color = 'b';
				z->parent->parent->color = 'r';
				z = z->parent->parent; //move x to x->p->p, continue loop
			} else { 
				//case 2.2, uncle is black, and z is inner child, rotate to 2.3
				if(z == z->parent->left) {
					z = z->parent; rotR(z);
				}
				//case 2.3, uncle is black, and z is outer child, rotate z->p-> and recolor
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				rotL(z->parent->parent);
			}
		}
	}
	root->color = 'b'; //set root to black
}

void RBTree::removeFixUp(TreeNode *x) {
	while(x != root && x->color == 'b') {
		if(x == x->parent->left) { //case 1: x is a left child
			TreeNode *w = x->parent->right; //w is x's sibling
			if(w->color == 'r') { //case 1.1: sibling w is red, rotate+flip to make it black, continue
				x->parent->color = 'r'; w->color = 'b'; //color flip
				rotL(x->parent);
				w = x->parent->right; //reset w
			} else { //cases 1.2-1.4: sibling w is black
				//case 1.2: both w's children are black. push x's black to parent, continue loop
				if(w->left->color == 'b' && w->right->color == 'b') {
					w->color = 'r'; //compensate
					x = x->parent;
					continue; //no need to proceed
				}
				//case 1.3: w's right child is black, then left child has to be red. rotate to go to 1.4
				if(w->right->color == 'b') { //then left is red
					w->color = 'r'; w->left->color = 'b'; //color flip
					rotR(w);
					w = x->parent->right; //reset w to right node!
				} 
				//case 1.4: w's right child is red. rotate x's parent + flip, recolor w->r as black
				w->color = x->parent->color; x->parent->color = 'b'; //color flip
				w->right->color = 'b'; //compensate
				rotL(x->parent);
				x = root; //set x as root to break
			}
		} else { //case 2: x is a right child
			TreeNode *w = x->parent->left;
			if(w->color == 'r') { //case 2.l
				x->parent->color = 'r'; w->color = 'b';
				rotR(x->parent);
				w = x->parent->right;
			} else { //cases 2.2-2.4
				if(w->left->color == 'b' && w->right->color == 'b') { //case 2.2
					w->color = 'r';
					x = x->parent;
					continue;
				}
				if(w->left->color == 'b') { //case 2.3
					w->color = 'r'; w->right->color = 'b';
					rotL(w);
					w = x->parent->left;
				}
				//case 2.4
				w->color = x->parent->color; x->parent->color = 'b';
				w->left->color = 'b';
				rotR(x->parent);
				x = root;
			}
		}
	}
	x->color = 'b';
}

void RBTree::printNode(TreeNode *z) {
	cout << z->key << ((z->color == 'r') ? "R " : " ");
}

#endif
