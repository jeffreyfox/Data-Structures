import java.util.LinkedList;

// class to find the connected components of an undirected graph
public class CC {

    public static void main(String[] args) {
        In in = new In(args[0]);
        Graph g = new Graph(in);
        CC ccfinder = new CC(g);
        int M = ccfinder.count();
        StdOut.println(M + " components");

        LinkedList<Integer>[] components;
        components = (LinkedList<Integer>[]) new LinkedList[M];
        for (int m = 0; m < M; ++m)
            components[m] = new LinkedList<Integer>();

        for (int v = 0; v < g.V(); ++v) {
            int id = ccfinder.id(v);
            components[id].add(v);
        }
        //print all components
        for (int m = 0; m < M; ++m) {
            StdOut.print("Component " + m + ": ");
            for (int v : components[m])
                StdOut.print(v + " ");
            StdOut.println();
        }
    }

    private boolean[] marked; //whether site is visited?
    private int[] id; //the component identifier for a vertex
    private int count; //number of components

    // preprocessing constructor (find CCs)
    public CC(Graph G) {
        marked = new boolean[G.V()];
        id = new int[G.V()];

        for (int v = 0; v < G.V(); ++v) {
            if (!marked[v]) {
                dfs(G, v);
                count++;
            }
        }        
    }
    // are v and w connected?
    public boolean connected(int v, int w) { return id[v] == id[w]; }
    // number of connected components
    public int count() { return count;}
    // component identifier for v [0 .. count)
    public int id(int v) { return id[v]; }

    //depth-first search at vertex v
    private void dfs(Graph G, int v) {
        marked[v] = true;
        id[v] = count;
        for (int w : G.adj(v))
            if (!marked[w])
                dfs(G, w);           
    }
}
