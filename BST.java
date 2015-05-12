
public class BST<Key extends Comparable<Key>, Value> {

    public static void main(String[] args) {
        BST<Integer, Integer> bst = new BST<Integer, Integer>();
        int N = 20;
        int[] a = new int[N];
        for (int i = 0; i < N; ++i) a[i] = i;
        StdRandom.shuffle(a);
        for (int i = 0; i < N; ++i) {
            int key = a[i];
            bst.put(key, 10*key);
        }
        StdOut.println("Tree Inorder: ");
        bst.print();
        StdOut.println();
        StdOut.println("Size = " + bst.size());
        StdOut.println("Height = " + bst.height());
        StdOut.println("Path length = " + bst.pathLen());
        StdOut.println("min, max = " + bst.min() + ", " + bst.max());
        StdOut.println("Deleting nodes ...");
        for (int i = 0; i < N; ++i) {
            int key = StdRandom.uniform(N);
            if (bst.contains(key)) {
                StdOut.print(key + " ");
                bst.delete(key);
            }
        }
        StdOut.println();
        StdOut.println("Tree Inorder: ");
        bst.print();
        StdOut.println();
        StdOut.println("Size = " + bst.size());
        StdOut.println("Height = " + bst.height());
        StdOut.println("Path length = " + bst.pathLen());
        StdOut.println("min = " + bst.min() + ", rank = " + bst.rank(bst.min()));
        StdOut.println("max = " + bst.max() + ", rank = " + bst.rank(bst.max()));

    }

    private Node root;

    private class Node {
        private Key key;
        private Value val;
        private Node left, right;
        private int N; // number of nodes at subtree rooted at node
        private int h; // height of subtree rooted at node
        private int pl; // path length of subtree rooted at node
        private Node(Key key, Value val, int N) {
            this.key = key;
            this.val = val;
            this.N = N;
            h = 0;
            pl = 0;                   
        }
    }

    public int size() { return size(root);}
    private int size(Node x) {
        if (x == null) return 0;
        else return x.N; 
    }

    public int height() { return height(root);}
    private int height(Node x) {
        if (x == null) return -1;
        else return x.h;
    }

    public int pathLen() { return pathLen(root);}
    private int pathLen(Node x) {
        if (x == null) return 0;
        else return x.pl;
    }

    public boolean isEmpty() { return root != null; }

    private void updateField(Node x) {
        if (x == null) return;
        x.N = size(x.left) + size(x.right) + 1;
        x.h = Math.max(height(x.left), height(x.right)) + 1;
        x.pl = pathLen(x.left) + size(x.left) + pathLen(x.right) + size(x.right); 
    }

    // insert a key-value pair into tree
    public void put(Key key, Value val) { root = put(root, key, val); }
    // insert a key-value pair at subtree x
    private Node put(Node x, Key key, Value val) {
        if (x == null) return new Node(key, val, 1);
        int cmp = key.compareTo(x.key);
        if      (cmp < 0) x.left  = put(x.left,  key, val);
        else if (cmp > 0) x.right = put(x.right, key, val);
        else              x.val = val; // update existing value
        updateField(x);
        return x;
    }

    // find value associated with given key
    public Value get(Key key) {
        Node t = get(root, key);
        if ( t == null) return null;
        else return t.val;
    }
    // find node with key value from subtree x
    private Node get(Node x, Key key) {
        if (x == null) return null;
        int cmp = key.compareTo(x.key);
        if      (cmp < 0) return get(x.left,  key);
        else if (cmp > 0) return get(x.right, key);
        else              return x;
    }

    // delete a node with given key (do nothing if not found)
    public void delete(Key key) { root = delete(root, key); }
    // delete a node with given key from subtree x
    private Node delete(Node x, Key key) {
        if (x == null) return null;
        int cmp = key.compareTo(x.key);
        if      (cmp < 0) x.left  = delete(x.left, key);
        else if (cmp > 0) x.right = delete(x.right, key);
        else { // found key, start deletion
            if (x.left == null) return x.right;
            if (x.right == null) return x.left;
            // now x has two children that are not null
            Node t = x;
            x = min(t.right); // this node will be the new x
            x.right = deleteMin(t.right);
            x.left = t.left;
        }
        updateField(x);
        return x;
    }

    // delete minimum node at subtree x and return new root
    private Node deleteMin(Node x) {
        // x is guaranteed not null
        if (x.left == null) return x.right; //delete x
        else x.left = deleteMin(x.left);
        updateField(x);
        return x;
    }

    public boolean contains(Key key) {  return get(key) != null;  }

    // find minimum key in the tree
    public Key min() {
        Node t = min(root);
        if (t == null) return null;
        else return t.key;
    }
    // find node with minimum key in the subtree x
    private Node min(Node x) {
        if (x == null) return null;
        if (x.left == null) return x;
        else return min(x.left);
    }

    // find maximum key in the tree
    public Key max() {
        Node t = max(root);
        if (t == null) return null;
        else return t.key;
    }
    // find node with maximum key in the subtree x
    private Node max(Node x) {
        if (x == null) return null;
        if (x.right == null) return x;
        else return max(x.right);
    }

    // find k-th order-statistics (key having k smaller keys)
    public Key select(int k) {
        Node x = select(root, k);
        if (x == null) return null;
        else return x.key;
    }
    // find node having a key of k-th order-statistics at subtree x
    private Node select(Node x, int k) {
        if(x == null) return null;
        int t = size(x.left);
        if      (k < t) return select(x.left, k);
        else if (k > t) return select(x.right, k-t-1);
        else            return x;
    }

    // get the rank of given key
    public int rank(Key key) { return rank(root, key);}
    // get the rank of given key at subtree x
    private int rank(Node x, Key key) {
        if (x == null) return 0;
        int cmp = key.compareTo(x.key);
        if      (cmp < 0) return rank(x.left, key);
        else if (cmp > 0) return rank(x.right, key) + 1 + size(x.left);
        else              return size(x.left);
    }

    public void print() { print(root);}
    private void print(Node x) {
        if (x == null) return;
        print(x.left);
        StdOut.print(x.key + " ");
        print(x.right);
    }
}
