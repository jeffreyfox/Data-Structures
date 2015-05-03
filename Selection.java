/// Selection sort


public class Selection {

    public static void sort(Comparable[] a) {
        for(int i = 0; i < a.length; ++i) {
            int min = i;
            for(int j = i+1; j < a.length; ++j) {
                if(less(a[j], a[min])) min = j;
            }
            exch(a, i, min);
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
        int N = 100;
        Integer[] a = new Integer[N];
        for(int i = 0; i < N; ++i)
            a[i] = StdRandom.uniform(0, 100);
        Selection.show(a);
        Selection.sort(a);
        assert isSorted(a);
        Selection.show(a);
    }
}
