import java.util.LinkedList;

// Class for undirected edge-weighted graph
public class EdgeWeightedGraph {
	public static void main(String[] args) {
		In in = new In(args[0]);        
		EdgeWeightedGraph g = new EdgeWeightedGraph(in);
		System.out.println(g);
	}

	private final int V; //number of vertices
	private int E; //number of edges
	private LinkedList<Edge>[] adj; //adjacency list

	// create a V-vertex graph with no edges
	public EdgeWeightedGraph(int V) {
		this.V = V;
		this.E = 0;
		adj = (LinkedList<Edge>[]) new LinkedList[V];
		for (int v = 0; v < V; ++v) adj[v] = new LinkedList<Edge>();
	}
	// read a graph from input stream
	public EdgeWeightedGraph(In in) {
		this(in.readInt());
		int E = in.readInt();
		for (int e = 0; e < E; ++e) {
			int v = in.readInt();
			int w = in.readInt();
			double weight = in.readDouble();
			addEdge(new Edge(v, w, weight));
		}
	}

	//number of vertices and edges
	public int V() { return V; }
	public int E() { return E; }

	//add an edge v-w to this graph
	public void addEdge(Edge e) {
		int v = e.either(), w = e.other(v);
		adj[v].addFirst(e); //consistent with Bag API in book
		adj[w].addFirst(e);
		E++;
	}

	// vertices adjacent to v
	public Iterable<Edge> adj(int v) { return adj[v];}
	//string representation
	public String toString() {
		String s = V + " vertices, " + E + " edges\n";
		for (int v = 0; v < V; ++v) {
			s += v + ": ";
			for (Edge e : adj[v]) 
				s += e + " ";
			s += "\n";
		}
		return s;
	}
}
