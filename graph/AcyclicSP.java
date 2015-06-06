import java.util.LinkedList;

// Shorted path algorithm on an directed acyclic graph which
// can have negative edges. Relax vertices in topological order
// Time O(E+V), space O(V)
public class AcyclicSP {

	public static void main(String[] args) {
		In in = new In(args[0]);
		EdgeWeightedDigraph G = new EdgeWeightedDigraph(in);
		int s = Integer.parseInt(args[1]);
		AcyclicSP sp = new AcyclicSP(G, s);

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

	public AcyclicSP(EdgeWeightedDigraph G, int s) {
		distTo = new double[G.V()];
		edgeTo = new DirectedEdge[G.V()];
		for (int v = 0; v < G.V(); ++v) {
			distTo[v] = Double.POSITIVE_INFINITY;			
		}
		distTo[s] = 0.0;
		
		Topological topo = new Topological(G);		
		for (int v : topo.order())
			relax(G, v);		
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
