import java.util.LinkedList;

// Simplify multigraph (directed) and remove duplicated edges and self loops
// Final graph is conceptually undirected, but use a digraph to represent for 
// implementation convenience
public class SimplifyMultiGraph {
	public static void main(String[] args) {
		int V = 5;
		int E = 200;
		Digraph g = new Digraph(V);
		for (int e = 0; e < E; ++e) {
			int i = StdRandom.uniform(V);
			int j = StdRandom.uniform(V);
			g.addEdge(i, j);
		}			
		System.out.println(g);
		SimplifyMultiGraph simplify = new SimplifyMultiGraph(g);
		System.out.println(simplify.GS());
	}

	private Digraph GS; //simplified "undirected" digraph

	// create a V-vertex graph with no edges
	public SimplifyMultiGraph(Digraph G) {
		GS = new Digraph(G.V());
		//first iteration, flatten G into an "undirected" graph		
		for (int i = 0; i < G.V(); ++i) {
			for (int j : G.adj(i)) {
				if (j != i) G.addEdge(j, i);
			}
		}
		//second iteration, add neighbors in ascending order
		for (int i = 0; i < G.V(); ++i) {
			for (int j : G.adj(i)) {
				if (j > i) 
					if (!GS.adj(j).iterator().hasNext() ||
							GS.adj(j).iterator().next() != i)
						GS.addEdge(j, i);
			}
		}
		//third iteration, add neighbors in descending order
		for (int i = 0; i < G.V(); ++i) {
			for (int j : G.adj(i)) {
				if (j < i) 
					if (!GS.adj(j).iterator().hasNext() ||
							GS.adj(j).iterator().next() != i)
						GS.addEdge(j, i);
			}
		}		
	}

	public Digraph GS() { return GS; }
}
