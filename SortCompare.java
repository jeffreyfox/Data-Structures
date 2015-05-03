import java.util.Arrays;

public class SortCompare
{
    public static double time(String alg, Double[] a)
    {
        Stopwatch timer = new Stopwatch();
        if (alg.equals("Insertion")) Insertion.sort(a);
        if (alg.equals("Selection")) Selection.sort(a);
        if (alg.equals("Shell")) Shell.sort(a);
        if (alg.equals("Merge")) Merge.sort(a);
        if (alg.equals("MergeBU")) Merge.sortBU(a);
        if (alg.equals("Quick")) Quick.sort(a);
        if (alg.equals("QuickST")) Quick.sortST(a);
        if (alg.equals("QuickMO3")) Quick.sortMO3(a);
        if (alg.equals("Quick3Way")) Quick.sort3Way(a);
        //  if (alg.equals("Heap")) Heap.sort(a);
        return timer.elapsedTime();
    }
    public static double timeRandomInput(String alg, int N, int T)
    { 
        double total = 0.0;
        Double[] a = new Double[N];
        for (int t = 0; t < T; t++)
        { // Perform one experiment (generate and sort an array).
            for (int i = 0; i < N; i++)
                a[i] = StdRandom.uniform();
            total += time(alg, a);
        }
        return total;
    }

    public static double timeOrderedInput(String alg, int N, int T)
    { 
        double total = 0.0;
        Double[] a = new Double[N];
        for (int t = 0; t < T; t++)
        { // Perform one experiment (generate and sort an array).
            for (int i = 0; i < N; i++)
                a[i] = ((double) i) / N;          
            total += time(alg, a);
        }
        return total;
    }

    public static double timeEqualInput(String alg, int N, int T)
    { 
        double total = 0.0;
        Double[] a = new Double[N];
        for (int t = 0; t < T; t++)
        { // Perform one experiment (generate and sort an array).
            for (int i = 0; i < N; i++)
                a[i] = 0.5 * (double) StdRandom.uniform(3);          
            total += time(alg, a);
        }
        return total;
    }
    public static void main(String[] args)
    {
        //String[] str = {"Merge", "MergeBU", "Quick", "QuickST", "Shell"};
        String[] str = {"Quick", "QuickST", "QuickMO3", "Quick3Way"};
        //String[] str = {"Merge", "MergeBU", "Quick", "Shell", "Insertion", "Selection"};
        StdRandom.shuffle(str);
        int N = 200000, T = 100;
        //int N = 5000, T = 100;
        StdOut.printf("%10s\t%8s\t%8s\t%8s\n", "Method", "random", "ordered", "equal");
        for (String alg : str) {
            double t1 = timeRandomInput(alg, N, T); //total time
            double t2 = timeOrderedInput(alg, N, T); //total time
            double t3 = timeEqualInput(alg, N, T); //total time
            StdOut.printf("%10s\t%.2e\t%.2e\t%.2e\n", alg, t1, t2, t3);
        }
    }
}
