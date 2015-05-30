import java.util.LinkedList;

/// class to find all articulation points of a graph
/// Criteria for AP:
/// 1. vertex v is root of dfs tree and has more than 1 child. 
/// 2. ertex v is non root, not leaf, and has at least one subtree rooted at 
/// a child, and that subtree does NOT have a back edge that climbs ¡°higher¡± 
/// than v in the dfs tree.

public class ArticulationPoint {

    public static void main(String[] args) {
        String[] files = {"g1.txt", "g2.txt", "g3.txt", "g4.txt"};
        for (String s : files) {
            In in = new In(s);
            Graph g = new Graph(in);            
            ArticulationPoint apfinder = new ArticulationPoint(g);
            if(apfinder.hasAP()) {
                StdOut.print("Graph " + s + " has articulation points: ");
                for (int v : apfinder.APs()) 
                    StdOut.print(v + " ");
                StdOut.println();
            } else {
                StdOut.print("Graph " + s + " has NO articulation points\n");
            }
        }
    }

    private boolean[] marked; //whether vertex is visited?
    private boolean[] isAP; //whether vertex is articulation point?
    private int[] parent; //vertex's parent in dfs search tree
    private int[] disc; //discover times of the vertex
    private int[] low; //minimum discover times of vertices reachable from subtree rooted at v 
    private int time = 0; //time stamp of dfs
    private boolean hasAP = false; //whether graph has any APs?

    // find articulation points of an undirected graph
    public ArticulationPoint(Graph G) {
        marked = new boolean[G.V()];
        isAP = new boolean[G.V()];
        parent = new int[G.V()];
        disc = new int[G.V()];
        low = new int[G.V()];        
        for (int v = 0; v < G.V(); ++v) 
            parent[v] = -1;

        for (int v = 0; v < G.V(); ++v) {
            if (!marked[v]) dfs(G, v);
        }
    }

    //depth-first search at vertex v
    private void dfs(Graph G, int v) {
        marked[v] = true;
        disc[v] = ++time;
        low[v] = disc[v];
        int children = 0;
        for (int w : G.adj(v)) //search thru v's neighbor w
            if (!marked[w]) { //w unvisited, and becomes the descendant of v in dfs tree
                children ++;
                parent[w] = v;
                dfs(G, w);               
                low[v] = Math.min(low[v], low[w]); //after finishing w, update v's low value from w
                // check if v is AP
                if (parent[v] == -1 && children > 1) isAP[v] = true;
                if (parent[v] != -1 && low[w] >= disc[v]) isAP[v] = true;
                if(isAP[v]) hasAP = true;
            } else if (parent[v] != w) { //w visited (back edge), check if w is not v's direct parent
                low[v] = Math.min(low[v], disc[w]); //update v's low value
            }
    }
    // has articulation points?
    public boolean hasAP() { return hasAP; }

    // all articulation points, null if none
    Iterable<Integer> APs() {
        if (!hasAP()) return null;
        LinkedList<Integer> ap = new LinkedList<Integer>();        
        for (int v = 0; v < isAP.length; ++v)
            if (isAP[v]) ap.add(v);            

        return ap;
    }
}
