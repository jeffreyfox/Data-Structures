
public class GREPbin {
    public static void main(String[] args) {
        String regexp = "(" + args[0] + ")";
        NFA nfa = new NFA(regexp);
        int N = 16;
        for (int i = 0; i < N; ++i) {
            String txt = num2Bin(i);
            if (nfa.recognizes(txt))
               StdOut.println(txt);
        }
    }

    private static String num2Bin(int n) {
        if (n == 0) return "0";
        String s = new String();
        while(n > 0) {
            int v = n % 2;
            s = (char)(v + '0') + s;
            n /= 2;
        }
        return s;
    }
}
