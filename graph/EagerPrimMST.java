import java.util.LinkedList;

// class for Prim's MST algorithm with eager implementation. O(ElogV) time and O(V) space
// slight difference from textbook. Here we pre-insert all distance entries to priority queue
// whose values are infinity. later we just call changeKey to update values, and avoid checking 
// key exists or not
public class EagerPrimMST {

	private boolean[] marked; //whether vertex is in the tree?
	private IndexMinPQ<Double> pq; //indexed priority queue of vertices (key = distance from tree)
	private Edge[] edgeTo; //edge to vertex v in the tree
	private double[] distTo; //distance of vertex v to the tree
	private double weight;

	public static void main(String[] args) {
		In in = new In(args[0]);
		EdgeWeightedGraph G = new EdgeWeightedGraph(in);

		EagerPrimMST mst = new EagerPrimMST(G);
		for (Edge e : mst.edges())
			StdOut.println(e);
		StdOut.printf("%.2f\n", mst.weight());
	}

	// constructor
	public EagerPrimMST(EdgeWeightedGraph G) {
		pq = new IndexMinPQ<Double>(G.V());

		marked = new boolean[G.V()];
		edgeTo = new Edge[G.V()];
		distTo = new double[G.V()];
		for (int v = 0; v < G.V(); ++v) {
			distTo[v] = Double.POSITIVE_INFINITY;
			pq.insert(v, distTo[v]);
		}		
		//change vertex 0's distance to 0
		distTo[0] = 0.0;
		pq.changeKey(0, 0.0);

		while (!pq.isEmpty()) {			
			int v = pq.delMin();
			visit(G, v);
		}
	}

	// relax all neighbors of v
	private void visit(EdgeWeightedGraph G, int v) {
		marked[v] = true;
		for (Edge e : G.adj(v)) {
			int w = e.other(v);
			if (marked[w]) continue; // w already in the tree
			if (distTo[w] > e.weight()) { // if e is a closer way to get to the tree
				distTo[w] = e.weight();
				edgeTo[w] = e;				
				pq.changeKey(w, e.weight()); //update entry in pq
			}			
		}
	}
	//all of MST edges
	public Iterable<Edge> edges() {
		LinkedList<Edge> mst = new LinkedList<Edge>();
		for (int v = 0; v < edgeTo.length; ++v) 
			if (edgeTo[v] != null ) {
				mst.add(edgeTo[v]);
				weight += edgeTo[v].weight();
			}
		return mst;
	}

	// weight of MST
	public double weight() {
		return weight;
	}
}
