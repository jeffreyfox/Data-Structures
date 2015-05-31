import java.util.LinkedList;

// class to find strongly connected components of a directed graph
public class SCC {

	public static void main(String[] args) {
		In in = new In(args[0]);
		Digraph g = new Digraph(in);
		SCC scc = new SCC(g);
		int M = scc.count();
		StdOut.println(M + " components");

		LinkedList<Integer>[] components;
		components = (LinkedList<Integer>[]) new LinkedList[M];
		for (int m = 0; m < M; ++m)
			components[m] = new LinkedList<Integer>();

		for (int v = 0; v < g.V(); ++v) {
			int id = scc.id(v);
			components[id].add(v);
		}
		//print all components
		for (int m = 0; m < M; ++m) {
			StdOut.print("Component " + m + ": ");
			for (int v : components[m])
				StdOut.print(v + " ");
			StdOut.println();
		}
	}

	private boolean[] marked; //whether site is visited?
	private int[] id; //component identifier of the vertex
	private int count; //number of strong components

	// preprocessing constructor
	public SCC(Digraph G) {
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

	//are v and w strongly connected?
	public boolean stronglyConnected(int v, int w) {
		return id[v] == id[w];
	}
	//number of strong components
	public int count() { return count; }
	//component identifier for v
	public int id(int v) { return id[v]; }
}

