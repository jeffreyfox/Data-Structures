
// class to perform topological sort on directed acyclic graph (DAG)
public class Topological {

	public static void main(String[] args) {
		In in = new In(args[0]);
		Digraph g = new Digraph(in);
		Topological topo = new Topological(g);
		if (topo.isDAG()) {
			for (int x : topo.order())
				StdOut.print(x + " ");
			StdOut.println();
		}
	}

	private boolean[] marked; //whether site is visited?
	private boolean isDAG; //is graph a DAG?
	private Stack<Integer> order; //topological order

	// preprocessing constructor
	public Topological(Digraph G) {
		DirectedCycle cyclefinder = new DirectedCycle(G);
		if (cyclefinder.hasCycle()) {
			StdOut.println("Graph has cycle!");
			isDAG = false;			
			return;			
		}

		isDAG = true;
		marked = new boolean[G.V()];
		order = new Stack<Integer>();
		for (int v = 0; v < G.V(); ++v) {
			if (!marked[v])
				dfs(G, v);
		}        
	}

	//depth-first search at vertex v
	private void dfs(Digraph G, int v) {
		marked[v] = true;
		for (int w : G.adj(v)) {
			if (!marked[w]) {				
				dfs(G, w);
			} 
		}
		//finished with v, add to stack
		order.push(v);
	}

	// preprocessing constructor
	public Topological(EdgeWeightedDigraph G) {
		marked = new boolean[G.V()];
		order = new Stack<Integer>();
		for (int v = 0; v < G.V(); ++v) {
			if (!marked[v])
				dfs(G, v);
		}        
	}

	//depth-first search at vertex v
	private void dfs(EdgeWeightedDigraph G, int v) {
		marked[v] = true;
		for (DirectedEdge e : G.adj(v)) {
			int w = e.to();
			if (!marked[w]) {				
				dfs(G, w);
			} 
		}
		//finished with v, add to stack
		order.push(v);
	}

	public boolean isDAG() { return isDAG; }
	// vertices in topological order
	public Iterable<Integer> order() { return order; }
}
