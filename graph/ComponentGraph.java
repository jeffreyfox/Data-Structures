
// class to find component graph of a directed graph
// use a trick similar to 22.1-4 (special ordering scheme to make sure
// the adjacency list elements are added in ascending order
public class ComponentGraph {

	public static void main(String[] args) {
		In in = new In(args[0]);
		Digraph g = new Digraph(in);
		StdOut.println("Original graph:\n" + g);
		ComponentGraph cgfinder = new ComponentGraph(g);
		CLRSSCC sccfinder = new CLRSSCC(g);
		int M = sccfinder.count();
		StdOut.println(M + " components");

		//print all components
		for (int m = 0; m < M; ++m) {
			StdOut.print("Component " + m + ": ");
			for (int v : sccfinder.scc(m))
				StdOut.print(v + " ");
			StdOut.println();
		}

		Digraph gscc = cgfinder.GSCC();
		StdOut.println("Component Graph:\n" + gscc);
	}

	private Digraph GSCC; //component graph of Gs

	// preprocessing constructor
	public ComponentGraph(Digraph G) {
		//get number of scc
		CLRSSCC sccfinder = new CLRSSCC(G);
		int m = sccfinder.count();

		GSCC = new Digraph(m);

		Digraph GR = G.reverse();
		//iterating over vertices in GR in order of increasing component id
		for (int i = 0; i < m; ++i) { //component i
			for (int v : sccfinder.scc(i)) { //all vertices in component i
				for (int w : GR.adj(v)) { //check v's neighbors in GR
					int iw = sccfinder.id(w); //component id of w
					if (iw == i) continue; //in the same component
					if (!GSCC.adj(iw).iterator().hasNext() || //empty 
							GSCC.adj(iw).iterator().next() != i	) //in increasing order
						GSCC.addEdge(iw, i);
				}
			}
		}		
	}

	//return the component graph
	public Digraph GSCC() { return GSCC; }
}

