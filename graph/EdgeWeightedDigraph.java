import java.util.LinkedList;

// Class for directed edge-weighted graph
public class EdgeWeightedDigraph {
	public static void main(String[] args) {
		In in = new In(args[0]);        
		EdgeWeightedDigraph g = new EdgeWeightedDigraph(in);
		System.out.println(g);
	}

	private final int V; //number of vertices
	private int E; //number of edges
	private LinkedList<DirectedEdge>[] adj; //adjacency list

	// create a V-vertex graph with no edges
	public EdgeWeightedDigraph(int V) {
		this.V = V;
		this.E = 0;
		adj = (LinkedList<DirectedEdge>[]) new LinkedList[V];
		for (int v = 0; v < V; ++v) adj[v] = new LinkedList<DirectedEdge>();
	}
	// read a graph from input stream
	public EdgeWeightedDigraph(In in) {
		this(in.readInt());
		int E = in.readInt();
		for (int e = 0; e < E; ++e) {
			int v = in.readInt();
			int w = in.readInt();
			double weight = in.readDouble();
			addEdge(new DirectedEdge(v, w, weight));
		}
	}

	//number of vertices and edges
	public int V() { return V; }
	public int E() { return E; }

	//add an edge v-w to this graph
	public void addEdge(DirectedEdge e) {
		int v = e.from();
		adj[v].addFirst(e); //consistent with Bag API in book		
		E++;
	}

	// vertices adjacent to v
	public Iterable<DirectedEdge> adj(int v) { return adj[v];}

	// return all edges
	public Iterable<DirectedEdge> edges() {
		LinkedList<DirectedEdge> edges = new LinkedList<DirectedEdge>();
		for (int v = 0; v < V; ++v) 
			for (DirectedEdge e : adj[v]) 
				edges.add(e);
		return edges;
	}

	//string representation
	public String toString() {
		String s = V + " vertices, " + E + " edges\n";
		for (int v = 0; v < V; ++v) {
			s += v + ": ";
			for (DirectedEdge e : adj[v]) 
				s += e + " ";
			s += "\n";
		}
		return s;
	}
}
