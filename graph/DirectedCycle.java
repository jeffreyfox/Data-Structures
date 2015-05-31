
// class to find if the directed graph has a cycle.
// If cycle exists, dump it out. 
// Use an array grey to tag the "grey" vertices not yet finished
// during dfs search, if encountered a grey vertices, that is
// a back-edge which belongs to a cycle
public class DirectedCycle {

	public static void main(String[] args) {
		In in = new In(args[0]);
		Digraph g = new Digraph(in);
		DirectedCycle cyclefinder = new DirectedCycle(g);
		boolean hasCycle = cyclefinder.hasCycle();
		if (hasCycle) {
			StdOut.println("Digraph has cycle");
			for (int x : cyclefinder.cycle())
				StdOut.print(x + " ");
			StdOut.println();
		}
		else StdOut.println("Digraph has NOT cycle");       
	}

	private boolean[] marked; //whether site is visited?
	private int[] parent; //parent of vertex in dfs
	private boolean[] grey; // grey vertices not yet finished
	private boolean hasCycle; //does it have cycle?
	private Stack<Integer> cycle; //cycle

	// preprocessing constructor
	public DirectedCycle(Digraph G) {
		marked = new boolean[G.V()];
		parent = new int[G.V()];
		grey = new boolean[G.V()];
		for (int v = 0; v < G.V(); ++v) {        	
			parent[v] = -1;
		}

		for (int v = 0; v < G.V(); ++v) {
			if (!marked[v])
				dfs(G, v);
		}        
	}

	//depth-first search at vertex v
	private void dfs(Digraph G, int v) {
		marked[v] = true;
		grey[v] = true; //just discovered v, tag as grey
		for (int w : G.adj(v)) {
			if (hasCycle) return; //no need to proceed
			if (!marked[w]) {
				parent[w] = v; 
				dfs(G, w);
			} else if (grey[w]) { //found a back edge (cycle)
				hasCycle = true;
				//construct cycle using parent[]: v -> ... -> w -> v
				// actual cycle is opposite, thus the stack
				cycle = new Stack<Integer>();
				for (int s = v; s != w; s = parent[s])
					cycle.push(s);
				cycle.push(w);
				cycle.push(v);
			}
		}
		grey[v] = false; //finished with v, un-tag grey
	}

	// does graph have a cycle?
	public boolean hasCycle() { return hasCycle; }
	public Iterable<Integer> cycle() { return cycle; }
}
