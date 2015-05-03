/// merge sort

public class Merge {
    private static Comparable[] aux;

    //bottom-up merge sort
    public static void sortBU(Comparable[] a) {
        int N = a.length;
        aux = new Comparable[a.length]; //still requires aux array!s
        for(int sz = 1; sz < N; sz = sz+sz) //merge two arrays, each of size sz!
            for(int lo = 0; lo + sz < N; lo += sz+sz)
                merge(a, lo, lo+sz-1, Math.min(lo+sz+sz-1, N-1));     
    }

    public static void sort(Comparable[] a) {
        aux = new Comparable[a.length];
        sort(a, 0, a.length-1);
    }

    private static void sort(Comparable[] a, int lo, int hi) {
        if (lo >= hi) return;
        int mid = lo + (hi-lo)/2;
        sort(a, lo, mid);
        sort(a, mid+1, hi);
        merge(a, lo, mid, hi);
    }

    private static void merge(Comparable[] a, int lo, int mid, int hi) {
        for (int k = lo; k <= hi; ++k)
            aux[k] = a[k];
        int i = lo, j = mid+1;
        for (int k = lo; k <= hi; ++k) {
            if      (i > mid)              a[k] = aux[j++];
            else if (j >  hi)              a[k] = aux[i++];
            else if (less(aux[j], aux[i])) a[k] = aux[j++];
            else                           a[k] = aux[i++];
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
        Merge.show(a);
        Merge.sort(a);
        assert isSorted(a);
        Merge.show(a);
    }
}

