/// Brute-force pattern search algorithm
public class StringSearchBF {
    // two pointers in two loops
    public static int search(String txt, String pat) {
        int n = txt.length(), m = pat.length();
        int i, j;
        for (i = 0; i <= n-m; ++i) { //i only needs to run till n-m
            for (j = 0; j < m; ++j) 
                if (txt.charAt(i+j) != pat.charAt(j)) break;
           
            if (j == m) return i; //found i
        }
        return n; //not found
    }
    // two pointers in one loop version
    public static int search2(String txt, String pat) {
        int n = txt.length(), m = pat.length();
        int i, j;
        for (i = 0, j = 0; i < n && j < m; ) { //check both i and j
            if (txt.charAt(i) == pat.charAt(j)) { i++; j++; }
            else { i = i-j+1; j = 0; } //back-up (i goes to next char in txt to be compared, j goes to pat[0])
        }
        if (j == m) return i-m; //found
        else        return   n; //not found
    }
    // two pointers in one loop version (variation of search2)
    public static int search3(String txt, String pat) {
        int n = txt.length(), m = pat.length();
        int i, j;
        for (i = 0, j = 0; i < n && j < m; i++) { //check both i and j, increment i here
            if (txt.charAt(i) == pat.charAt(j)) j++; //only increment j
            else { i -= j; j = 0; } //back-up (i goes to left of next char in txt to be compared, j goes to pat[0])
        }
        if (j == m) return i-m; //found
        else        return   n; //not found
    }

    public static void main(String[] args) {
        String txt = args[0];
        String pat = args[1];
        int offset = StringSearchBF.search(txt, pat);
        int offset2 = StringSearchBF.search2(txt, pat);
        int offset3 = StringSearchBF.search3(txt, pat);
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
