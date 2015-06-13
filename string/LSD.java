// LSD (least significant digit) string sort
public class LSD {
	public static void main(String[] args) {
		int N = 10; // number of strings
		int W = 5; // length of each string
		String[] a = new String[N];
		for (int i = 0; i < N; ++i) { 
			a[i] = new String();
			for (int j = 0; j < W; ++j)
				a[i] += (char) ('a' + StdRandom.uniform(7));
		}
		StdOut.println("Input string: ");
		for (int i = 0; i < N; ++i)
			StdOut.println(" " + a[i]);

		LSD.sort(a, W);

		StdOut.println("After sort:");
		for (int i = 0; i < N; ++i)
			StdOut.println(" " + a[i]);

	}

	public static void sort(String[] a, int W) {

		int N = a.length;
		int R = 256;
		String[] aux = new String[N];

		// starting from least significant digit 
		for (int d = W-1; d >= 0; --d) {
			int[] count = new int[R+1];

			// use char as index. each one instance of c will push the position of c+1 to the right
			// hence increment count of c+1 entry
			for (int i = 0; i < N; ++i)
				count[a[i].charAt(d) + 1] ++;

			// get accumulative count, now count[c] denotes the number of elements
			// in the array that are strictly smaller than c, or 
			// the position c should go in the sorted array
			for (int r = 1; r <= R; ++r)
				count[r] += count[r-1];

			// redistribute array to aux according to count
			// also update count field
			for (int i = 0; i < N; ++i)			
				aux[count[a[i].charAt(d)]++] = a[i]; 

			// copy aux array back to original array
			for (int i = 0; i < N; ++i)
				a[i] = aux[i];
		}
	}
}
