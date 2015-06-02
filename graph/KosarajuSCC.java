import java.util.LinkedList;

// class to find strongly connected components of a directed graph
// Follows algorithm in Sedgewick's book.
public class KosarajuSCC {

	public static void main(String[] args) {
		In in = new In(args[0]);
		Digraph g = new Digraph(in);
		KosarajuSCC sccfinder = new KosarajuSCC(g);
		int M = sccfinder.count();
		StdOut.println(M + " components");

		//print all components
		for (int m = 0; m < M; ++m) {
			StdOut.print("Component " + m + ": ");
			for (int v : sccfinder.scc(m))
				StdOut.print(v + " ");
			StdOut.println();
		}
	}

	private boolean[] marked; //whether site is visited?
	private int[] id; //component identifier of the vertex
	private int count; //number of strong components
	LinkedList<Integer>[] scc; //strong components

	// preprocessing constructor
	public KosarajuSCC(Digraph G) {
		marked = new boolean[G.V()];
		id = new int[G.V()];

		Digraph GR = G.reverse();
		DepthFirstOrder order = new DepthFirstOrder(GR);
		for (int v : order.reversePost()) {
			if (!marked[v]) {
				dfs(G, v);
				count ++;
			}
		}        
		//construct strong components
		scc = (LinkedList<Integer>[]) new LinkedList[count];
		for (int i = 0; i < count; ++i)
			scc[i] = new LinkedList<Integer>();

		for (int v = 0; v < G.V(); ++v)
			scc[id[v]].add(v);
	}

	//depth-first search at vertex v
	private void dfs(Digraph G, int v) {
		marked[v] = true;
		id[v] = count;
		for (int w : G.adj(v)) {
			if (!marked[w]) {				
				dfs(G, w);
			} 
		}
	}

	// return component i
	public Iterable<Integer> scc(int i) { return scc[i]; }

	//are v and w strongly connected?
	public boolean stronglyConnected(int v, int w) {
		return id[v] == id[w];
	}
	//number of strong components
	public int count() { return count; }
	//component identifier for v
	public int id(int v) { return id[v]; }
}

