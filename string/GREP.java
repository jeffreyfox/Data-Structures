
public class GREP {
    public static void main(String[] args) {
      //  String regexp = "(.*" + args[0] + ".*)";
        String regexp = "(" + args[0] + ")";
        NFA nfa = new NFA(regexp);
        while (StdIn.hasNextLine()) {
            String txt = StdIn.readLine();
            if (nfa.recognizes(txt))
               StdOut.println(txt);
        }
    }
}
