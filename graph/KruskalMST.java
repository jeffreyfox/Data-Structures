import java.util.LinkedList;

// class for Kruskal's MST algorithm. O(ElogE) time and O(E) space
public class KruskalMST {

	private LinkedList<Edge> mst; //mst
	private double weight;

	public static void main(String[] args) {
		In in = new In(args[0]);
		EdgeWeightedGraph G = new EdgeWeightedGraph(in);

		KruskalMST mst = new KruskalMST(G);
		for (Edge e : mst.edges())
			StdOut.println(e);
		StdOut.printf("%.2f\n", mst.weight());
	}

	// constructor
	public KruskalMST(EdgeWeightedGraph G) {
		mst = new LinkedList<Edge>();
		MinPQ<Edge> pq = new MinPQ<Edge>();
		for (Edge e : G.edges())
			pq.insert(e);

		UF uf = new UF(G.V());

		while (!pq.isEmpty() && mst.size() < G.V() - 1) {
			Edge e = pq.delMin(); //pop minimum edge
			int v = e.either(), w = e.other(v);
			//check if it is eligible edge
			if (!uf.connected(v, w)) {
				uf.union(v, w);
				mst.add(e);
				weight += e.weight();
			}
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
