import java.util.LinkedList;

//non-deterministic finite automata for regex matching
public class NFA {

    private Digraph G;
    private String pat; //reg-ex pattern
    //for it to work pattern has to be embraced by "()"! (due to dfs = new DirectedDFS(G, 0)), dfs from 0
    public NFA(String pattern) {
        pat = pattern;
        int m = pattern.length();
        G = new Digraph(m+1); //contains m+1 states, last is accepted state
        LinkedList<Integer> stack = new LinkedList<Integer>();
        for (int i = 0; i < m; ++i) { //scan pattern
            char c = pat.charAt(i);
            int lp = i; 
            if (c == '(' || c == '|') stack.addFirst(i);
            else if (c == ')') {
                int j = stack.removeFirst();
                if (pat.charAt(j) == '|') {  // j : '|' index
                    lp = stack.removeFirst(); // lp '(' index
                    G.addEdge(lp, j+1); 
                    G.addEdge(j, i);
                } else {  // j : '(' index
                    lp = j; // lp '(' index
                }
            }
            if (i < m-1 && pat.charAt(i+1) == '*') { // look ahead
                G.addEdge(lp, i+1);  //lp is the index of last '('
                G.addEdge(i+1, lp); 
            }
            if (c == '(' || c == '*' || c == ')')  // match empty string
                G.addEdge(i, i+1);
        }
    }

    public boolean recognizes(String txt) {
        LinkedList<Integer> pc = new LinkedList<Integer>();
        DirectedDFS dfs = new DirectedDFS(G, 0);
        int m = pat.length();
        for (int v = 0; v < G.V(); ++v)
            if (dfs.marked(v)) pc.add(v);

      //  System.out.print("Before start: ");
      //  for (int j : pc) System.out.print(j + " ");
      //  System.out.println();

        for (int i = 0; i < txt.length(); ++i) {
            // Compuate possible NFA states for txt[i+1], after seeing txt[i]
            LinkedList<Integer> match = new LinkedList<Integer>();
            for (int j : pc)
                if (j < m && (pat.charAt(j) == txt.charAt(i) || pat.charAt(j) == '.'))
                    match.add(j+1);

            pc = new LinkedList<Integer>();
            dfs = new DirectedDFS(G, match);
            for (int v = 0; v < G.V(); ++v)
                if (dfs.marked(v)) pc.add(v);

        //    System.out.print("At step " + i + ": ");
        //    for (int j : pc) System.out.print(j + " ");
        //    System.out.println();
        }

        for (int j : pc)
            if (j == m) return true;
        return false;
    }

    public static void main(String[] args) {
        String pat = args[0];
        String txt = args[1];
        NFA nfa = new NFA(pat);
        boolean tag = nfa.recognizes(txt); 
        System.out.println("Text    = " + txt);
        System.out.println("Pattern = " + pat);
        System.out.print  ("          ");
        for (int i = 0; i < pat.length(); ++i) System.out.print(i);
        System.out.println();
        if (tag) System.out.println("Text matches pattern.");
        else System.out.println("Text does NOT match pattern!");
    }
}
