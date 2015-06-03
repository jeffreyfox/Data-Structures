import java.util.LinkedList;

// class for Prim's MST algorithm with lazy implementation. O(ElogE) time and O(E) space
public class LazyPrimMST {

	private boolean[] marked;
	private MinPQ<Edge> pq; //priority queue of edges
	private LinkedList<Edge> mst; //mst
	private double weight;

	public static void main(String[] args) {
		In in = new In(args[0]);
		EdgeWeightedGraph G = new EdgeWeightedGraph(in);

		LazyPrimMST mst = new LazyPrimMST(G);
		for (Edge e : mst.edges())
			StdOut.println(e);
		StdOut.printf("%.2f\n", mst.weight());
	}

	// constructor
	public LazyPrimMST(EdgeWeightedGraph G) {
		marked = new boolean[G.V()];
		pq = new MinPQ<Edge>();
		mst = new LinkedList<Edge>();

		visit(G, 0);
		marked[0] = true;
		while (!pq.isEmpty() && mst.size() < G.V() - 1) {
			Edge e = pq.delMin(); //pop minimum edge
			int v = e.either(), w = e.other(v);
			//check if it is eligible edge
			if (marked[v] && marked[w]) continue;
			//add to MST if eligible
			mst.add(e);
			weight += e.weight();
			if (!marked[v]) visit(G, v);
			if (!marked[w]) visit(G, w);
		}
	}

	// visit vertex v, put all edges to queue
	private void visit(EdgeWeightedGraph G, int v) {
		marked[v] = true;
		for (Edge e : G.adj(v)) {
			int w = e.other(v);
			if (!marked[w]) pq.insert(e); //insert unvisited edges
		}
	}
	//all of MST edges
	public Iterable<Edge> edges() {
		return mst;
	}

	// weight of MST
	public double weight() {
		return weight;
	}
}
