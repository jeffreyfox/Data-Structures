/// Shell sort


public class Shell {

    public static void sort(Comparable[] a) {
        int h = 1;
        while(3*h+1 < a.length) 
            h = 3*h+1;

        while(h > 0) {
            for(int i = h; i < a.length; i += 1) {
                for(int j = i; j >= h && less(a[j], a[j-h]); j -= h)
                    exch(a, j, j-h);                
            }
            h = h/3;
        }
    }

    public static void show(Comparable[] a) {
        for(int i = 0; i < a.length; ++i) {
            StdOut.print(a[i] + " ");
        }
        StdOut.println();
    }

    private static boolean less(Comparable u, Comparable v) {
        return u.compareTo(v) < 0;
    }

    private static void exch(Comparable[] a, int i, int j) {
        Comparable t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    private static boolean isSorted(Comparable[] a) {
        for(int i = 1; i < a.length; ++i) {
            if(less(a[i-1], a[i])) return false;
        }
        return true;
    }

    public static void main(String[] args) {
        int N = 20;
        Integer[] a = new Integer[N];
        for(int i = 0; i < N; ++i)
            a[i] = StdRandom.uniform(0, 1000);
        Shell.show(a);
        Shell.sort(a);
        assert isSorted(a);
        Shell.show(a);
    }
}

