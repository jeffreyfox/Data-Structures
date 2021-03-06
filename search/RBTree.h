#ifndef RBTREE_H
#define RBTREE_H

struct RBTreeNode {
	int key;
	int size; //size attribute for order statistics
	char color; //color field for red-black tree
	RBTreeNode *left, *right, *parent;
	RBTreeNode(int v) : key(v), size(0), color('b'), left(NULL), right(NULL), parent(NULL) {} //default black
};

class RBTree {
public:
	RBTree() { root = null = new RBTreeNode(INT_MAX); }
	virtual ~RBTree() {deleteUtil(root); delete(null);}

	//check if tree is empty
	bool empty() const { return root == null;}
	//return size of the tree
	int size() const { return root->size;}
	const RBTreeNode* rootnode() const { return root;}
	//return the null node
	const RBTreeNode* nullnode() const { return null;}

	//find the node with given key value (iterative)
	RBTreeNode* search(int key) {
		RBTreeNode *node = root;
		while(node != null && key != node->key) {
			if(key < node->key) node = node->left;
			else node = node->right;
		}
		return node; //return when node == null (not found), or key matches (found)
	}

	//find minimum and maximum element of tree rooted at z
	RBTreeNode* minimum(RBTreeNode* z) {
		if(z == null) return z;
		while(z->left != null) z = z->left;
		return z;
	}
	RBTreeNode* maximum(RBTreeNode* z) {
		if(z == null) return z;
		while(z->right != null) z = z->right;
		return z;
	}

	//output all keys between a and b in subtree z (z has to be an existing node)
	void enumerate(const RBTreeNode *z, int a, int b) const {
		if(z == null) return;
		enumerate(z->left, a, b);
		if(a <= z->key && z->key <= b) cout << z->key << " ";
		enumerate(z->right, a, b);
	}

	//print tree in-order (recursive)
	void printInOrder() { printInOrderUtil(root); }
	void printInOrderUtil(RBTreeNode *z) {
		if(z == null) return;
		printInOrderUtil(z->left);
		printNode(z);
		printInOrderUtil(z->right);
	}
	//print tree level-order
	void printLevelOrder()
	{
		deque<RBTreeNode*> qt;
		deque<int> ql;
		int level = 0;
		if(root != null) { qt.push_back(root); ql.push_back(level);}
		while(!qt.empty()) {
			RBTreeNode *n = qt.front(); qt.pop_front();
			int l = ql.front(); ql.pop_front();
			if(l > level) { cout << endl; level ++; }
			printNode(n);
			if(n->left != null) { qt.push_back(n->left); ql.push_back(l+1);}
			if(n->right != null) { qt.push_back(n->right); ql.push_back(l+1);}
		}
		cout << endl;
	}

	//select the node corresponding to i-th order statistic (iterative)
	RBTreeNode* select(int i) {
		if(i <= 0 || i > root->size) return null;
		RBTreeNode *z = root;
		while(1) {
			int r = z->left->size + 1;
			if(i == r) return z;
			else if(i < r) { z = z->left;}
			else { z = z->right; i -= r;}
		}
		return null; //not found
	}

	//select the node corresponding to i-th order statistic (recursive)
	RBTreeNode* select2(int i) {
		if(i <= 0 || i > root->size) return null;
		else return selectUtil(root, i);
	}
	RBTreeNode* selectUtil(RBTreeNode* z, int i) {
		int r = z->left->size + 1;
		if(i == r) return z;
		else if(i < r) return selectUtil(z->left, i);
		else return selectUtil(z->right, i-r);
	}

	//return the rank of a given node (iterative)
	int rank(RBTreeNode* z) {
		int r = z->left->size + 1;
		RBTreeNode *x = z;
		while(x != root) {
			if(x->parent->right == x) r += x->parent->left->size + 1;
			x = x->parent;
		}
		return r;
	}
	//return the rank of a given node (recursive)
	int rank2(RBTreeNode* z) { return rankUtil(root, z); }
	//return rank of node z in substree x;
	int rankUtil(RBTreeNode* x, RBTreeNode* z) {
		if(x == z) return x->left->size+1;
		else if(z->key < x->key) return rankUtil(x->left, z);
		else return x->left->size + 1 + rankUtil(x->right, z);
	}

	//insert a node to red-black tree
	void insert(RBTreeNode *z);
	//remove a node to red-black tree
	void remove(RBTreeNode *z);
	//remove a node to red-black tree (node flipping)
	void remove2(RBTreeNode *z);
	//check if tree is valid

private: 

	//Utility function for recursively deleting all elements in subtree rooted at z
	void deleteUtil(RBTreeNode *z) {
		if(z == null) return;
		deleteUtil(z->left);
		deleteUtil(z->right);
		delete z;
	}

	//left and right rotation of tree around z
	void rotL(RBTreeNode *x) {
		RBTreeNode *y = x->right;
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
		//update size attribute
		y->size = x->size;
		x->size = x->left->size + x->right->size + 1;
	}
	void rotR(RBTreeNode *x) {
		RBTreeNode *y = x->left;
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
		//update size attribute
		y->size = x->size;
		x->size = x->left->size + x->right->size + 1;
	}

	//function to replace subtree rooted at u with subtree rooted at v
	void transplant(RBTreeNode *u, RBTreeNode *v) {
		v->parent = u->parent; //with sentinel, no need to check if v is null
		if(u->parent == null) root = v; //u was root
		else if(u == u->parent->left) u->parent->left = v; //u was a left child
		else u->parent->right = v; //u was a right child
	}

	//traverse upwards and decreaase the size of nodes encountered by 1
	void decSizeUp(RBTreeNode *z) {
		while(z != null) {
			z->size--;
			z = z->parent;
		}
	}

	void printNode(const RBTreeNode *z) const {
		cout << z->key << ((z->color == 'r') ? "R-" : "-") << z->size << " ";
	}

	void insertFixUp(RBTreeNode *z);
	void removeFixUp(RBTreeNode *x);

	RBTreeNode* root; //root node
	RBTreeNode* null; //sentinel node
};

void RBTree::insert(RBTreeNode *z) {
	z->left = z->right = null;
	z->size = 1; //initialize size attribute
	RBTreeNode *x = root, *y = null;
	while(x != null) {
		x->size ++; //increment size attribute
		y = x;
		x = (z->key < x->key) ? x->left : x->right;
	}
	z->parent = y;
	if(y == null) root = z; //tree was empty, update root
	else if(z->key < y->key) y->left = z;
	else y->right = z;
	z->color = 'r'; //color it as red
	insertFixUp(z);
}

void RBTree::insertFixUp(RBTreeNode *z) {
	while(z->parent->color == 'r') { //z and z->p double red
		//z->p->p exists and should be a black node (because root can't be red)
		if(z->parent == z->parent->parent->left) { //case 1, z->p is left child
			RBTreeNode *y = z->parent->parent->right; //y is x's uncle
			if(y->color == 'r') { //case 1.1, uncle is red, recolor, and continue
				y->color = z->parent->color = 'b';
				z->parent->parent->color = 'r';
				z = z->parent->parent; //move x to x->p->p, continue loop
			} else { 
				//case 1.2, uncle is black, and z is inner child, rotate to 1.3
				if(z == z->parent->right) { z = z->parent; rotL(z); }
				//case 1.3, uncle is black, and z is outer child, rotate z->p-> and recolor
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				rotR(z->parent->parent);
			}
		} else { //case 2, z->p is right child
			RBTreeNode *y = z->parent->parent->left; //y is x's uncle
			if(y->color == 'r') { //case 2.1, uncle is red, recolor, and continue
				y->color = z->parent->color = 'b';
				z->parent->parent->color = 'r';
				z = z->parent->parent; //move x to x->p->p, continue loop
			} else { 
				//case 2.2, uncle is black, and z is inner child, rotate to 2.3
				if(z == z->parent->left) { z = z->parent; rotR(z);}
				//case 2.3, uncle is black, and z is outer child, rotate z->p-> and recolor
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				rotL(z->parent->parent);
			}
		}
	}
	root->color = 'b'; //set root to black
}

void RBTree::remove(RBTreeNode *z) {
	char yc = z->color;
	RBTreeNode *x;
	if(z->left == null) {
		x = z->right; transplant(z, x); //x's parent implicitly set
	} else if(z->right == null) {
		x = z->left; transplant(z, x); //x's parent implicitly set
	} else {
		RBTreeNode *y = minimum(z->right); //z's successor
		yc = y->color; //save y's original color
		x = y->right; //x can be null
		if(y == z->right) {
			x->parent = y; //x's parent explicity set (only effective when x is null)
		} else {
			transplant(y, x); //x's parent implicitly set
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
		y->size = z->size; //copy z's size attribute
	}
	delete z;
	decSizeUp(x->parent); //update size attributes
	if(yc == 'b') removeFixUp(x);//only fix when y's original color is black
}

void RBTree::remove2(RBTreeNode *z) {
	char yc = z->color;
	RBTreeNode *x;
	if(z->left == null) {
		x = z->right; transplant(z, x); //x's parent implicitly set
		delete z;
	} else if(z->right == null) {
		x = z->left; transplant(z, x); //x's parent implicitly set
		delete z;
	} else {
		RBTreeNode *y = minimum(z->right); //z's successor
		yc = y->color; //save y's original color
		x = y->right; //x can be null
		z->key = y->key; //color node value
		transplant(y, x); //x's parent implicitly set
		delete y;
	}
	decSizeUp(x->parent); //update size attributes
	if(yc == 'b') removeFixUp(x);//only fix when y's original color is black
}

void RBTree::removeFixUp(RBTreeNode *x) {
	while(x != root && x->color == 'b') {
		if(x == x->parent->left) { //case 1: x is a left child
			RBTreeNode *w = x->parent->right; //w is x's sibling
			if(w->color == 'r') { //case 1.1: sibling w is red
				x->parent->color = 'r'; w->color = 'b'; //color flip
				rotL(x->parent);
				w = x->parent->right; //reset w
			} else if(w->left->color == 'b' && w->right->color == 'b') { //case 1.2: w black, both children are black
				w->color = 'r'; //compensate
				x = x->parent;
			} else { // case 1.3 1.4: at least one of w's children is red
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
			RBTreeNode *w = x->parent->left;
			if(w->color == 'r') { //case 2.l
				x->parent->color = 'r'; w->color = 'b';
				rotR(x->parent);
				w = x->parent->right;
			} else if(w->left->color == 'b' && w->right->color == 'b') { //case 2.2
				w->color = 'r';
				x = x->parent;
			} else {
				if(w->left->color == 'b') { //case 2.3, go to 2.4
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

#endif
