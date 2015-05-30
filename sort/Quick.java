/// Quicksort


public class Quick {

    public static void sort(Comparable[] a) {
        StdRandom.shuffle(a); //shuffle!
        sort(a, 0, a.length-1);
    }

    private static void sort(Comparable[] a, int lo, int hi) {
        if (lo >= hi) return;
        int j = partition(a, lo, hi);
        sort(a, lo, j-1);
        sort(a, j+1, hi);
    }

    private static int partition(Comparable[] a, int lo, int hi) {
        int i = lo, j = hi+1;
        Comparable v = a[lo];   //use a[lo] as pivot
        while (true) {
            while (less(a[++i], v)) if (i == hi) break;
            while (less(v, a[--j])) ; //if (j == lo) break;
            if (i >= j) break;
            exch(a, i, j);
        }
        exch(a, lo, j);
        return j;
    }
    //sort with sentinel
    public static void sortST(Comparable[] a) {
        StdRandom.shuffle(a); //shuffle!

        if(a.length <= 1) return;
        int max = 0;
        for(int i = 1; i < a.length; ++i) {
            if(less(a[max], a[i])) max = i;
        }
        exch(a, a.length-1, max); //put max into last entry
        sortST(a, 0, a.length-1);
    }

    private static void sortST(Comparable[] a, int lo, int hi) {
        if (lo >= hi) return;
        int j = partitionST(a, lo, hi);
        sortST(a, lo, j-1);
        sortST(a, j+1, hi);
    }
    //partition with sentinel, remove bound checks
    private static int partitionST(Comparable[] a, int lo, int hi) {
        int i = lo, j = hi+1;
        Comparable v = a[lo];   //use a[lo] as pivot
        while (true) {
            while (less(a[++i], v));
            while (less(v, a[--j]));
            if (i >= j) break;
            exch(a, i, j);
        }
        exch(a, lo, j);
        return j;
    }
    //median of three
    public static void sortMO3(Comparable[] a) {
        StdRandom.shuffle(a); //shuffle!
        sortMO3(a, 0, a.length-1);
    }

    private static void sortMO3(Comparable[] a, int lo, int hi) {
        if (lo >= hi) return;

        //partition around median, and place the larger element at hi,
        // lower element a lo
        int mid = lo + (hi-lo)/2;
        exch(a, lo+1, mid); //put med element at lo+1
        if(less(a[lo+1], a[lo])) exch(a, lo, lo+1);
        if(less(a[hi], a[lo])) exch(a, lo, hi);
        if(less(a[hi], a[lo+1])) exch(a, lo+1, hi);
        if(hi <= lo+2) return; //don't forget this line!

        int j = partitionST(a, lo+1, hi-1); //from lo+1 to hi-1
        sortMO3(a, lo, j-1);
        sortMO3(a, j+1, hi);
    }

    public static void sort3Way(Comparable[] a) {
        StdRandom.shuffle(a); //shuffle!
        sort3Way(a, 0, a.length-1);
    }

    private static void sort3Way(Comparable[] a, int lo, int hi) {
        if (lo >= hi) return;

        int lt = lo, i = lo, gt = hi;
        Comparable x = a[lo];
        while (i <= gt) {
            int comp = a[i].compareTo(x); 
            if      (comp < 0) exch(a, i++, lt++);
            else if (comp > 0) exch(a, i, gt--);
            else               i++;            
        }
        sort3Way(a, lo, lt-1);
        sort3Way(a, gt+1, hi);
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
        Quick.show(a);
        Quick.sort(a);
        assert isSorted(a);
        Quick.show(a);

        for(int i = 0; i < N; ++i)
            a[i] = StdRandom.uniform(0, 100);
        Quick.show(a);
        Quick.sortST(a);
        assert isSorted(a);
        Quick.show(a);

        for(int i = 0; i < N; ++i)
            a[i] = StdRandom.uniform(0, 100);
        Quick.show(a);
        Quick.sortMO3(a);
        assert isSorted(a);
        Quick.show(a);

        for(int i = 0; i < N; ++i)
            a[i] = StdRandom.uniform(0, 100);
        Quick.show(a);
        Quick.sort3Way(a);
        assert isSorted(a);
        Quick.show(a);
    }
}
