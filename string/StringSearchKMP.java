/// KMP pattern search algorithm
/// The idea is to analyze the pattern first, and prestore the jump position of j after matching txt with pat[j]
/// Method 1 finds the position by finding incrementally the jump position of matching pat[1..j] and store it.
/// Method 2 finds the position by finding iteratively the longest prefix of pat[0..j-1] that is also a suffix.

public class StringSearchKMP {
    // method 1: using dfa[][] array and X[]
    public static int search(String txt, String pat) {
        int n = txt.length(), m = pat.length();
        int i, j;
        int R = 256;
        int[][] dfa = new int[R][m]; // dfa[c][j]: index position in pattern to jump to after comparing a 'c' with pat[j]
        int[] X = new int[m]; //X[j]: the final pattern index position when running pat[1..j] as txt on dfa corresponding to pat

        //how to constrcut dfa[c][j], in other words, how to find jump position when comparing a 'c' with pat[j]?
        //we know that at this stage, the first j character in txt is exactly pat[0..j-1]
        //if the next character also matches, i.e. c == pat[j], then increment j, thus dfa[pat.charAt(j)][j] = j+1
        //otherwise, we have to shift pattern to right and start comparing pat with txt, which is exactly pat[1..j-1]. This is same as
        //running pat[1..j-1] on dfa. After we know the final position, indicated as X, we then compare c with pat[X], thus 
        //dfa[c][j] = dfa[c][pat.charAt[X]], which is calculated earlier (DP).

        //If we store the final position of pat[1..j] for all 0<=j<m before hand (as X[j]), we don't need to explicitly simulate that.
        //X[j] can be calculated in a DP fasion:
        //to run pat[1..j], we first run pat[1..j-1] on dfa, and obtain the final position in pattern as X[j-1] (by the definition of X[j]),
        //and next we should compare pat[j] (as txt char) with pat[X[j-1]] (as pat char), thus X[j] = dfa[pat.charAt(j)]][X[j-1]].
        //We start from 1, once we construct the dfa[c][j], we can calculate X[j]

        //construct dfa
        dfa[pat.charAt(0)][0] = 1;
        for (j = 1; j < m; ++j) { //start from j = 1 (2-char prefix)
            //if not match, then comparing c with pat[j] is same as comparing c with pat[X[j-1]]
            for (int c = 0; c < R; ++c)
                dfa[c][j] = dfa[c][X[j-1]];
            dfa[pat.charAt(j)][j] = j+1;

            X[j] = dfa[pat.charAt(j)][X[j-1]];
        }

        //running txt on dfa
        for (i = 0, j = 0; i < n && j < m; ++i)
            j = dfa[txt.charAt(i)][j];

        if (j == m) return i-m; //found
        else        return   n; //not found
    }
    // method 1 simplified version: we only need X of the last step, so just use one variable X instead of an array, and update X accordingly
    public static int search2(String txt, String pat) {
        int n = txt.length(), m = pat.length();
        int i, j;
        int R = 256;
        int[][] dfa = new int[R][m]; 
        int X = 0; //initally for j = 0

        //construct dfa
        dfa[pat.charAt(0)][0] = 1;
        for (j = 1; j < m; ++j) { //start from j = 1 (2-char prefix)
            //if not match, then comparing c with pat[j] is same as comparing c with pat[X[j-1]]
            for (int c = 0; c < R; ++c)
                dfa[c][j] = dfa[c][X]; //use X for j-1 to construct dfa[c][j]
            dfa[pat.charAt(j)][j] = j+1;

            X = dfa[pat.charAt(j)][X]; //update X for j from X for j-1
        }

        //running txt on dfa
        for (i = 0, j = 0; i < n && j < m; ++i)
            j = dfa[txt.charAt(i)][j];

        if (j == m) return i-m; //found
        else        return   n; //not found
    }

    // method 2: find length of longest (non-trivial) prefix of pat[0..j-1] (length j) that is also a suffix.
    public static int search3(String txt, String pat) {
        int n = txt.length(), m = pat.length();
        int i, j;
        int[] f = new int[m+1]; //f[j]: length of longest (non-trivial) prefix of pat[0..j-1] (length j) that is also a suffix.

        //construct f iteratively
        f[0] = -1; //define as -1 for later convenience
        for (j = 1; j <= m; ++j) {
            int k = f[j-1];
            while (k >= 0 && pat.charAt(k) != pat.charAt(j-1)) k = f[k];
            f[j] = k+1; //either k == -1 or pat[k] is end of the longest prefix
        }

        for (j = 0; j <= m; ++j) System.out.print("f[" + j + "]=" + f[j] + " ");
        System.out.println();

        //start matching using f to jump in pat
        for (i = 0, j = 0; i < n && j < m; ) {
            if (txt.charAt(i) == pat.charAt(j)) { i++; j++; } //matched
            else if (j == 0)  i++; //match pat[0] with next char in txt
            else j = f[j]; //i stay still, j moves to the char immediately after the longest prefix of pat[0..j-1]
        }

        if (j == m) return i-m; //found
        else        return   n; //not found
    }

    public static void main(String[] args) {
        String txt = args[0];
        String pat = args[1];
        int offset = StringSearchKMP.search(txt, pat);
        int offset2 = StringSearchKMP.search2(txt, pat);
        int offset3 = StringSearchKMP.search3(txt, pat);
        if (offset != offset2) System.out.println("Warning: offset2 and offset are not equal!");
        if (offset != offset3) System.out.println("Warning: offset3 and offset are not equal!");
        if (offset == txt.length()) System.out.println("Pattern \"" + pat + "\" not found in \"" + txt + "\"!");
        else {
            System.out.println("Pattern \"" + pat + "\" found in \"" + txt + "\".");
            System.out.println(txt);
            for (int i = 0; i < offset; ++i) System.out.print(" ");
            System.out.println(pat);
        }
    }
}
