import java.util.LinkedList;

// Brute force version of Bellman-Ford shorted path algorithm on a directed graph which
// can have cycles and negative edges. 
// Time O(EV), space O(V)
public class BellmanFordSP {

	public static void main(String[] args) {
		In in = new In(args[0]);
		EdgeWeightedDigraph G = new EdgeWeightedDigraph(in);
		int s = Integer.parseInt(args[1]);
		BellmanFordSP sp = new BellmanFordSP(G, s);

		for (int v = 0; v < G.V(); ++v) {
			StdOut.printf("%d to %d (%4.2f): ", s, v, sp.distTo(v));
			if (sp.hasPathTo(v)) {
				for (DirectedEdge e : sp.pathTo(v))
					StdOut.print(e + " ");				
			}
			StdOut.println();
		}		 
	}

	private double[] distTo; //distance from s to v on SP
	private DirectedEdge[] edgeTo; //edge pointing to v on SP

	public BellmanFordSP(EdgeWeightedDigraph G, int s) {
		distTo = new double[G.V()];
		edgeTo = new DirectedEdge[G.V()];
		for (int v = 0; v < G.V(); ++v) {
			distTo[v] = Double.POSITIVE_INFINITY;			
		}
		distTo[s] = 0.0;

		for (int pass = 0; pass < G.V(); ++pass) {
			for (int v = 0; v < G.V(); ++v) 
				relax(G, v);
		}
	}
	//relax vertex v (for outging edges
	private void relax(EdgeWeightedDigraph G, int v) {
		for (DirectedEdge e : G.adj(v)) {
			int w = e.to();
			if (distTo[w] > distTo[v] + e.weight()) {
				distTo[w] = distTo[v] + e.weight();
				edgeTo[w] = e;		
			}
		}
	}
	//distance on SP from s to v
	public double distTo(int v) {
		return distTo[v];
	}
	// there is a shortest path from s to v ?
	public boolean hasPathTo(int v) {
		return distTo[v] < Double.POSITIVE_INFINITY;
	}
	// path from s to v, null if none
	public Iterable<DirectedEdge> pathTo(int v) {
		if (!hasPathTo(v)) return null;
		LinkedList<DirectedEdge> path = new LinkedList<DirectedEdge>();
		for (DirectedEdge e = edgeTo[v]; e != null; e = edgeTo[e.from()])
			path.addFirst(e); //mimic a stack
		return path;			
	}
}
