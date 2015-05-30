
// class to find if the undirected graph has a cycle
// trick: need to remember the vertex's parent when doing dfs
public class Cycle {

    public static void main(String[] args) {
        In in = new In(args[0]);
        Graph g = new Graph(in);
        Cycle cyclefinder = new Cycle(g);
        boolean hasCycle = cyclefinder.hasCycle();
        if (hasCycle) StdOut.println("Graph has cycle");
        else StdOut.println("Graph has NOT cycle");       
    }

    private boolean[] marked; //whether site is visited?
    private boolean hasCycle; //does it have cycle?

    // preprocessing constructor
    public Cycle(Graph G) {
        marked = new boolean[G.V()];

        for (int v = 0; v < G.V(); ++v) {
            if (!marked[v])
                dfs(G, v, -1);
        }        
    }
    // does graph has a cycle?
    public boolean hasCycle() { return hasCycle; }

    //depth-first search at vertex v, whose parent is u
    private void dfs(Graph G, int v, int u) {
        marked[v] = true;
        for (int w : G.adj(v)) {
            if (!marked[w])
                dfs(G, w, v);    
            else if (w != u) //w visited but not v's parent u
                hasCycle = true;
        }
    }
}
