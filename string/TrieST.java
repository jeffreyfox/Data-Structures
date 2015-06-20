import java.util.LinkedList;

public class TrieST<Value> {
    
    private static class Node { //has to add "static", otherwise runtime error. Don't know why
        private Object val;
        private Node[] links = new Node[R];
    }
    
    private static int R = 256;
    private Node root = new Node();

    // put key-value pair into the table
    public void put(String key, Value val) {
        root = put(root, key, 0, val);
    }

    // update the node associated with Key, searching from subtree x and starting at Key[d ..], return updated node x
    private Node put(Node x, String key, int d, Value val) {
        if (x == null) x = new Node();  //no node exist, create
        if (d == key.length()) x.val = val; //update node value
        else {
            char c = key.charAt(d);
            x.links[c] = put(x.links[c], key, d+1, val);
        }
        return x; //return updated node
    }

    // get value associated with key
    public Value get(String key) {
        Node x = get(root, key, 0);
        if (x == null) return null; //node does not exist
        else return (Value) x.val; //found node, but key could be null
    }

    // return the node associated with Key, searching from subtree x and starting at Key[d ..] 
    private Node get(Node x, String key, int d) {
        if (x == null) return null;
        if (d == key.length()) return x; //examined all characters in key, return node
        char c = key.charAt(d);
        return get(x.links[c], key, d+1);
    }

    // return all the keys in the table
    public Iterable<String> keys() { return keysWithPrefix(""); }

    // return all the keys having pre as prefix
    public Iterable<String> keysWithPrefix(String pre) {
        LinkedList<String> q = new LinkedList<String>();
        Node x = get(root, pre, 0);
        collect(x, pre, q);
        return q;
    }

    // collect all keys from subtree x with common prefix pre
    private void collect(Node x, String pre, LinkedList<String> q) {
        if (x == null) return;
        if (x.val != null) q.add(pre);
        for (char c = 0; c < R; ++c) 
            collect(x.links[c], pre+c, q);
    } 

    // return all keys that match pat
    public Iterable<String> keysThatMatch(String pat) {
        LinkedList<String> q = new LinkedList<String>();
        collect(root, pat, "", q);
        return q;
    }
    private void collect(Node x, String pat, String pre, LinkedList<String> q) {
        if (x == null) return;
        int d = pre.length();
        if (d == pat.length()) { //examined all characters, collect and return
            if (x.val != null) q.add(pre); //only collect when x has value
            return;
        }
        char p = pat.charAt(d);
        if (p != '.') collect(x.links[p], pat, pre+p, q);
        else { // p is wildcard .
            for (char c = 0; c < R; ++c)
                collect(x.links[c], pat, pre+c, q);
        }
    }

    public static void main(String[] args) {
        String[] tokens = {"she", "sells", "sea", "shells", "on", "the", "sea", "shore"};
        TrieST<Integer> st = new TrieST<Integer>();
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
