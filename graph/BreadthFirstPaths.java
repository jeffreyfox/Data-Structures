
// class to solve single-source paths problem in undirected graph
// using breadth first search
public class BreadthFirstPaths {

	public static void main(String[] args) {
		In in = new In(args[0]);
		Graph g = new Graph(in);
		int s = Integer.parseInt(args[1]);
		BreadthFirstPaths dfs = new BreadthFirstPaths(g, s);
		for (int v = 0; v < g.V(); ++v) {
			if (dfs.hasPathTo(v)) {
				StdOut.print(s + " to " + v + ": ");
				for (int w : dfs.pathTo(v)) 
					StdOut.print(w + " ");
				StdOut.println();
			}
		}        
	}

	private boolean[] marked; //whether site is visited?
	private int[] parent; //vertex's parent in dfs search tree

	// find path in G form source s
	public BreadthFirstPaths(Graph G, int s) {
		marked = new boolean[G.V()];
		parent = new int[G.V()];
		for (int v = 0; v < G.V(); ++v) 
			parent[v] = -1;

		bfs(G, s);
	}

	//breadth-first search at vertex s
	private void bfs(Graph G, int s) {
		Queue<Integer> q = new Queue<Integer>();
		q.enqueue(s);
		marked[s] = true;
		while (!q.isEmpty()) {
			int v = q.dequeue(); 
			for (int w : G.adj(v)) {
				if (!marked[w]) {
					marked[w] = true;
					q.enqueue(w);
					parent[w] = v;
				}
			}
		}       
	}

	// is there a path from s to v?
	public boolean hasPathTo(int v) { return marked[v];   }

	// path from s to v, null if no such path
	Iterable<Integer> pathTo(int v) {
		Stack<Integer> path;
		if (!hasPathTo(v)) return null;
		path = new Stack<Integer>();
		for (int s = v; s != -1; s = parent[s])
			path.push(s);            

		return path;
	}
}
