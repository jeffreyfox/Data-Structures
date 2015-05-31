import java.util.LinkedList;

// Class for undirected graph
public class Digraph {
	public static void main(String[] args) {
		In in = new In(args[0]);        
		Digraph g = new Digraph(in);
		System.out.println(g);
	}

	private final int V; //number of vertices
	private int E; //number of edges
	private LinkedList<Integer>[] adj; //adjacency list

	// create a V-vertex graph with no edges
	public Digraph(int V) {
		this.V = V;
		this.E = 0;
		adj = (LinkedList<Integer>[]) new LinkedList[V];
		for (int v = 0; v < V; ++v) adj[v] = new LinkedList<Integer>();
	}
	// read a graph from input stream
	public Digraph(In in) {
		this(in.readInt());
		int E = in.readInt();
		for (int e = 0; e < E; ++e) {
			int v = in.readInt();
			int w = in.readInt();
			addEdge(v, w);
		}
	}

	//number of vertices and edges
	public int V() { return V;}
	public int E() { return E;}

	//add an edge v-w to this graph
	public void addEdge(int v, int w) {
		adj[v].addFirst(w); //consistent with Bag API in book
		E++;
	}
	// vertices adjacent to v
	public Iterable<Integer> adj(int v) { return adj[v];}

	public Digraph reverse() {
		Digraph gr = new Digraph(V);
		for (int v = 0; v < V; ++v) {
			for (int w : adj[v])
				gr.addEdge(w, v);
		}
		return gr;
	}
	//string representation
	public String toString() {
		String s = V + " vertices, " + E + " edges\n";
		for (int v = 0; v < V; ++v) {
			s += v + ": ";
			for (int w : adj[v]) 
				s += w + " ";
			s += "\n";
		}
		return s;
	}
}
