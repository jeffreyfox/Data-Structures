import java.util.LinkedList;

public class TST<Value> {
    
    private class Node {
        private char c;
        private Value val;
        private Node left, mid, right;
        public Node(char c) { this.c = c; }
    }
    
    private Node root;

    // put key-value pair into the table
    public void put(String key, Value val) {
        root = put(root, key, 0, val);
    }

    // update the node associated with Key, searching from subtree x and starting at Key[d ..], return updated node x
    private Node put(Node x, String key, int d, Value val) {
        char c = key.charAt(d);
        if (x == null) x = new Node(c);  //no node exist, create
        if      (c < x.c) x.left  = put(x.left,  key, d, val); //put into left subtree
        else if (c > x.c) x.right = put(x.right, key, d, val); //put into right subtree
        else if (d < key.length()-1) x.mid = put(x.mid, key, d+1, val); //put into middle subtree (if c is not the last character of key)
        else x.val = val; //c is the last character of key, update node value
        return x; //return updated node
    }

    // get value associated with key
    public Value get(String key) {
        Node x = get(root, key, 0);
        if (x == null) return null; //node does not exist
        else return x.val; //found node, but key could be null
    }

    // return the node associated with Key, searching from subtree x and starting at Key[d ..] 
    private Node get(Node x, String key, int d) {
        if (x == null) return null;
        char c = key.charAt(d);
        if      (c < x.c) return get(x.left,  key, d); //go to left subtree
        else if (c > x.c) return get(x.right, key, d); //go to right subtree
        else if (d < key.length()-1) return get(x.mid, key, d+1); //go to middle subtree (if c is not last character of key)
        else return x; //c is last character of key, return the node
    }

    // return all the keys in the table
    public Iterable<String> keys() { return keysWithPrefix(""); }

    // return all the keys having pre as prefix
    public Iterable<String> keysWithPrefix(String pre) {
        LinkedList<String> q = new LinkedList<String>();
        if (pre.equals("")) collect(root, "", q);
        else {
            Node x = get(root, pre, 0);
            if (x.val != null) q.add(pre);
            collect(x.mid, pre, q);       
        }
        return q;
    }

    // collect all keys from subtree x with common prefix pre
    private void collect(Node x, String pre, LinkedList<String> q) {
        if (x == null) return;
        if (x.val != null) q.add(pre+x.c);
        collect(x.left, pre, q);
        collect(x.mid, pre+x.c, q);
        collect(x.right, pre, q);
    } 

    // return all keys that match pat
    public Iterable<String> keysThatMatch(String pat) {
        LinkedList<String> q = new LinkedList<String>();
        collect(root, pat, "", 0, q);
        return q;
    }
    private void collect(Node x, String pat, String pre, int d, LinkedList<String> q) {
        if (x == null) return;
        char c = pat.charAt(d);
        if (c < x.c || c == '.') collect(x.left, pat, pre, d, q);
        if (c > x.c || c == '.') collect(x.right, pat, pre, d, q);
        if (c == x.c || c == '.') {
            if (d < pat.length() - 1) collect(x.mid, pat, pre+x.c, d+1, q);
            else if (x.val != null) q.add(pre+x.c);
        }
    }

    public static void main(String[] args) {
        String[] tokens = {"she", "sells", "sea", "shells", "on", "the", "sea", "shore"};
        TST<Integer> st = new TST<Integer>();
        for (String s : tokens) 
            st.put(s, s.length());
        
        String pre = args[0], pat = args[1];
        System.out.println("Print all keys with prefix '" + pre + "':");
        for (String s : st.keysWithPrefix(pre)) 
            System.out.println("  " + s); 
        System.out.println("Print all keys that match '" + pat + "':");
        for (String s : st.keysThatMatch(pat)) 
            System.out.println("  " + s); 
    }
}
