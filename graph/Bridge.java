import java.util.LinkedList;

/// class to find all bridges of a graph
/// Criteria for bridge: 
/// tree edge (v, w), where v's child is w, and subtree w does NOT 
/// have a back edge that climbs to or higher than v in the dfs tree.

public class Bridge {

    public static void main(String[] args) {
        String[] files = {"g1", "g2", "g3", "g4"};
        for (String s : files) {
            In in = new In(s + ".txt");
            Graph g = new Graph(in);            
            Bridge bridgefinder = new Bridge(g);
            if(bridgefinder.hasBrdige()) {
                StdOut.print("Graph " + s + " has bridges points: ");
                bridgefinder.printBridges();                
                StdOut.println();
            } else {
                StdOut.print("Graph " + s + " has NO articulation points\n");
            }
        }
    }

    private boolean[] marked; //whether vertex is visited?
    private int[] parent; //vertex's parent in dfs search tree
    private int[] disc; //discover times of the vertex
    private int[] low; //minimum discover times of vertices reachable from subtree rooted at v 
    private int time = 0; //time stamp of dfs
    private LinkedList<Edge> bridges;

    private class Edge {
        private int v, w;
        Edge(int v, int w) {
            this.v = v;
            this.w = w;
        }
    }
    // find articulation points of an undirected graph
    public Bridge(Graph G) {
        marked = new boolean[G.V()];
        parent = new int[G.V()];
        disc = new int[G.V()];
        low = new int[G.V()];        
        for (int v = 0; v < G.V(); ++v) 
            parent[v] = -1;
        
        bridges = new LinkedList<Edge>();
        
        for (int v = 0; v < G.V(); ++v) {
            if (!marked[v]) dfs(G, v);
        }
    }

    //depth-first search at vertex v
    private void dfs(Graph G, int v) {
        marked[v] = true;
        disc[v] = ++time;
        low[v] = disc[v];        
        for (int w : G.adj(v)) //search thru v's neighbor w
            if (!marked[w]) { //w unvisited, and becomes the descendant of v in dfs tree
                parent[w] = v;
                dfs(G, w);               
                low[v] = Math.min(low[v], low[w]); //after finishing w, update v's low value from w
                // check if v-w is bridge
                if (low[w] > disc[v]) bridges.add(new Edge(v, w));               
            } else if (parent[v] != w) { //w visited (back edge), check if w is not v's direct parent
                low[v] = Math.min(low[v], disc[w]); //update v's low value
            }
    }
    // has articulation points?
    public boolean hasBrdige() { return !bridges.isEmpty(); }

    // all articulation points, null if none
    public void printBridges() {
        for (Edge e : bridges)
            StdOut.print(e.v + "-" + e.w + " ");       
    }
}
