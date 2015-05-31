import java.util.LinkedList;

// class to perform dfs to a directed graph
public class DirectedDFS {

	public static void main(String[] args) {
		In in = new In(args[0]);
		Digraph g = new Digraph(in);
		LinkedList<Integer> sources = new LinkedList<Integer>();
		for (int i = 1; i < args.length; ++i)
			sources.add(Integer.parseInt(args[i]));

		DirectedDFS dfs = new DirectedDFS(g, sources);
		for (int v = 0; v < g.V(); ++v) {
			if (dfs.marked(v)) 
				StdOut.print(v + " ");
		}        
		StdOut.println();
	}

	private boolean[] marked; //whether site is visited?

	// find path in G form source s
	public DirectedDFS(Digraph G, int s) {
		marked = new boolean[G.V()];    
		dfs(G, s);
	}

	public DirectedDFS(Digraph G, Iterable<Integer> sources) {
		marked = new boolean[G.V()];
		for (int s : sources)
			if (!marked[s]) dfs(G, s);
	}

	// is vertex v marked?
	public boolean marked(int v) { return marked[v];   }

	//depth-first search at vertex v
	private void dfs(Digraph G, int v) {
		marked[v] = true;
		for (int w : G.adj(v))
			if (!marked[w])
				dfs(G, w);
	}
}
