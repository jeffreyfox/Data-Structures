
// class to find if the undirected graph is bipartite (two-colorable)
public class TwoColor {

    public static void main(String[] args) {
        In in = new In(args[0]);
        Graph g = new Graph(in);
        TwoColor tccheck = new TwoColor(g);
        boolean bipartitle = tccheck.bipartite();
        if (bipartitle) StdOut.println("Graph is bipartitle (two-colorable)");
        else StdOut.println("Graph is NOT bipartitle (two-colorable)");       
    }

    private boolean[] marked; //whether site is visited?
    private boolean[] color; //color of each vertex
    private boolean bipartite = true; //is graph bipartite?

    // preprocessing constructor
    public TwoColor(Graph G) {
        marked = new boolean[G.V()];
        color = new boolean[G.V()];
        
        for (int v = 0; v < G.V(); ++v) {
            if (!marked[v])
                dfs(G, v);
        }        
    }
    // does graph has a cycle?
    public boolean bipartite() { return bipartite; }

    //depth-first search at vertex v
    private void dfs(Graph G, int v) {
        marked[v] = true;
        for (int w : G.adj(v)) {
            if (!marked[w]) {
                color[w] = !color[v];
                dfs(G, w);                
            } else if (color[w] == color[v]) //w visited but color is the same
                bipartite = false;
        }
    }
}
