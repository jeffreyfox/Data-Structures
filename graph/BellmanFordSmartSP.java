import java.util.LinkedList;

// Queue-based Bellman-Ford shorted path algorithm on a directed graph which
// can have cycles and negative edges. 
// Use a queue structure, only put vertices whose distTo has changed
// to queue. When popped out of queue, process its neighbors
// Time O(EV), space O(V) in worst case. Average case much better
public class BellmanFordSmartSP {

	public static void main(String[] args) {
		In in = new In(args[0]);
		EdgeWeightedDigraph G = new EdgeWeightedDigraph(in);
		int s = Integer.parseInt(args[1]);
		BellmanFordSmartSP sp = new BellmanFordSmartSP(G, s);

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
	private Queue<Integer> q;
	private boolean[] onQ;

	public BellmanFordSmartSP(EdgeWeightedDigraph G, int s) {
		distTo = new double[G.V()];
		edgeTo = new DirectedEdge[G.V()];
		onQ = new boolean[G.V()];
		q = new Queue<Integer>();
		for (int v = 0; v < G.V(); ++v) {
			distTo[v] = Double.POSITIVE_INFINITY;			
		}
		distTo[s] = 0.0;

		q.enqueue(s);
		onQ[s] = true;
		while (!q.isEmpty()) {
			int v = q.dequeue();
			onQ[v] = false;
			relax(G, v);
		}
	}
	//relax vertex v (for outging edges)
	private void relax(EdgeWeightedDigraph G, int v) {
		for (DirectedEdge e : G.adj(v)) {
			int w = e.to();
			if (distTo[w] > distTo[v] + e.weight()) {
				distTo[w] = distTo[v] + e.weight();
				edgeTo[w] = e;
				if (!onQ[w]) { //only if not on queue (avoid duplicates)
					q.enqueue(w);
					onQ[w] = true;
				}				
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
