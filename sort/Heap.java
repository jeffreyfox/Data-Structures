
public class Heap {

    public static void sort(Comparable[] a) {
        int N = a.length;
        //build the heap
        for(int i = N/2; i > 0; --i) 
            sink(a, i, N);

        //heap sort
        while (N > 1) { // N stop at 2
            exch(a, 1, N--);
            sink(a, 1, N);
        }
    }

    public static void show(Comparable[] a) {
        for(int i = 0; i < a.length; ++i) {
            StdOut.print(a[i] + " ");
        }
        StdOut.println();
    }
    //sink the k-th item (a[k-1]) in a heap of size N
    private static void sink(Comparable[] a, int k, int N) {
        while (2*k <= N) {
            int j = 2*k;
            if (j < N && less(a, j, j+1)) j++;
            if (!less(a, k, j)) break;
            exch(a, k, j);
            k = j;
        }
    }

    private static boolean less(Comparable u, Comparable v) {
        return u.compareTo(v) < 0;
    }
    //compare the i-th and j-th item (a[i-1], a[j-1])
    private static boolean less(Comparable[] a, int i, int j) {
        return a[i-1].compareTo(a[j-1]) < 0;
    }
    //exchange the i-th and j-th item(a[i-1], a[j-1])
    private static void exch(Comparable[] a, int i, int j) {
        Comparable t = a[i-1];
        a[i-1] = a[j-1];
        a[j-1] = t;
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
        Heap.show(a);
        Heap.sort(a);
        assert isSorted(a);
        Heap.show(a);
    }
}

