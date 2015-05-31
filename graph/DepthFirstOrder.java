import java.util.LinkedList;

// class to build preorder, postorder, and reversepost order
// for a directed graph (could be cyclic)
public class DepthFirstOrder {

	public static void main(String[] args) {
		In in = new In(args[0]);
		Digraph g = new Digraph(in);
		DepthFirstOrder order = new DepthFirstOrder(g);

		StdOut.print("Preorder: ");
		for (int x : order.pre())
			StdOut.print(x + " ");
		StdOut.println();

		StdOut.print("Postorder: ");
		for (int x : order.post())
			StdOut.print(x + " ");
		StdOut.println();

		StdOut.print("Reverse Postorder: ");
		for (int x : order.reversePost())
			StdOut.print(x + " ");
		StdOut.println();

	}

	private boolean[] marked; //whether site is visited?
	private LinkedList<Integer> pre;  //preorder
	private LinkedList<Integer> post; //postorder
	private LinkedList<Integer> reversePost; //reverse postorder

	// preprocessing constructor
	public DepthFirstOrder(Digraph G) {
		marked = new boolean[G.V()];
		pre = new LinkedList<Integer>();
		post = new LinkedList<Integer>();
		reversePost = new LinkedList<Integer>();
		for (int v = 0; v < G.V(); ++v) {
			if (!marked[v])
				dfs(G, v);
		}        
	}

	//depth-first search at vertex v
	private void dfs(Digraph G, int v) {
		marked[v] = true;
		pre.add(v); //preorder, add at discover time
		for (int w : G.adj(v)) {
			if (!marked[w]) {				
				dfs(G, w);
			} 
		}
		post.add(v); //postorder, add at finish time
		reversePost.addFirst(v); //reverse post order, add to front
	}

	// vertices in various orders
	public Iterable<Integer> pre() { return pre; }
	public Iterable<Integer> post() { return post; }
	public Iterable<Integer> reversePost() { return reversePost; }
}
