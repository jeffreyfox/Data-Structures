///Insertion sort

public class Insertion {

    public static void sort(Comparable[] a) {
        for(int i = 1; i < a.length; ++i) {
            for(int j = i; j > 0 && less(a[j], a[j-1]); --j)
                exch(a, j, j-1);                
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
            a[i] = StdRandom.uniform(0, 100);
        Insertion.show(a);
        Insertion.sort(a);
        assert isSorted(a);
        Insertion.show(a);
    }
}
