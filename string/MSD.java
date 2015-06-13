// MSD (most significant digit) string sort
public class MSD {
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

		MSD.sort(a);

		StdOut.println("After sort:");
		for (int i = 0; i < N; ++i)
			StdOut.println(" " + a[i]);

	}

	private static int R = 256;
	private static String[] aux;

	public static void sort(String[] a) {
		int N = a.length;
		aux = new String[N];		
		sortUtil(a, 0, N-1, 0);
	}

	// recursively sort digit d of a[lo .. hi]
	private static void sortUtil(String[] a, int lo, int hi, int d) {
		if (lo >= hi) return;

		int[] count = new int[R+2]; //one extra entry for empty string

		// use char as index. each one instance of c will push the position of c+1 to the right
		// hence increment count of c+1 entry. 
		// index for char c is now at c+1, hence extra +1 when converting char to indices
		for (int i = lo; i <= hi; ++i)
			count[charAt(a[i], d) + 2] ++;

		// get accumulative count, now count[c] denotes the number of elements
		// in the array that are strictly smaller than c, or 
		// the position c should go in the sorted array
		for (int r = 1; r <= R+1; ++r)
			count[r] += count[r-1];

		// redistribute array to aux according to count
		// also update count field. Remember the extra +1 offset
		for (int i = lo; i <= hi; ++i)			
			aux[count[charAt(a[i], d) + 1]++] = a[i]; 

		// copy aux array back to original array
		for (int i = lo; i <= hi; ++i)
			a[i] = aux[i-lo];

		// after distribution, now strings whose d's digit is c 
		// are grouped between count[c] and count[c+1]-1 (inclusive)
		// recursively sort sub-arrays whose d's digit is r
		// arrays of size less than d no longer needed to be sorted		// 
		for (int r = 0; r < R; ++r)
			sortUtil(a, lo + count[r], lo + count[r+1]-1, d+1);
	}

	private static int charAt(String s, int d) {
		if (d < s.length()) return s.charAt(d);
		else return -1;
	}
}
