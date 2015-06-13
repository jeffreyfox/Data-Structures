// 3-way string quicksort
public class Quick3string {
	public static void main(String[] args) {
		int N = 10; // number of strings
		int W = 5; // length of each string
		String[] a = new String[N];
		for (int i = 0; i < N; ++i) { 
			a[i] = new String();
			for (int j = 0; j < 1+StdRandom.uniform(W); ++j)
				a[i] += (char) ('a' + StdRandom.uniform(7));
		}
		StdOut.println("Input string: ");
		for (int i = 0; i < N; ++i)
			StdOut.println(" " + a[i]);

		Quick3string.sort(a);

		StdOut.println("After sort:");
		for (int i = 0; i < N; ++i)
			StdOut.println(" " + a[i]);

	}

	public static void sort(String[] a) {			
		sortUtil(a, 0, a.length-1, 0);
	}

	// recursively sort digit d of a[lo .. hi]
	private static void sortUtil(String[] a, int lo, int hi, int d) {
		if (lo >= hi) return;

		// three-color partition of character d, using a[lo] as partition pivot
		int v = charAt(a[lo], d);		
		// [lo, lt-1] < x, [lt, i-1] == x, [i, gt] ??, [gt+1, hi] > x
		int lt = lo, i = lo, gt = hi;
		while (i <= gt) {
			int t = charAt(a[i], d);
			if (t < v) exch(a, lt++, i++);
			else if (t == v) i++;
			else exch(a, i, gt--);
		}

		//after partition, now recursively sort the 3 subarrays
		sortUtil(a, lo, lt-1, d);
		if (v >= 0) sortUtil(a, lt, gt, d+1); //condition needed to avoid infinite loop
		sortUtil(a, gt+1, hi, d);
	}

	private static int charAt(String s, int d) {
		if (d < s.length()) return s.charAt(d);
		else return -1;
	}

	private static void exch(String[] a, int i, int j) {
		String t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
}
