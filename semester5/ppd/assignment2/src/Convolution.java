import java.util.concurrent.CyclicBarrier;

public class Convolution {

    //computes the new values of one row
    public static void computeRow(int[] up, int[] mid, int[] down, int[][] c, int[] out) {
        int m = out.length;
        for (int j = 0; j < m; j++) {

            int left = j > 0 ? j - 1 : 0;
            int right = j < m - 1 ? j + 1 : m - 1;

            out[j] = up[left] * c[0][0] + up[j] * c[0][1] + up[right] * c[0][2]
                   + mid[left] * c[1][0] + mid[j] * c[1][1] + mid[right] * c[1][2]
                   + down[left] * c[2][0] + down[j] * c[2][1] + down[right] * c[2][2];
        }
    }

    //the result is written in f, only 2 temporary vectors of size m are used
    public static void applyConvolutionSequentially(int[][] f, int[][] c) {
        int n = f.length; //rows
        int m = f[0].length; //columns
        int[] prev = new int[m]; //original values of prev row
        int[] cur = new int[m];  //original values of row i

        //row -1 is equal to row 0
        System.arraycopy(f[0], 0, prev, 0, m);

        for (int i = 0; i < n; i++) {
            System.arraycopy(f[i], 0, cur, 0, m);
            //row i + 1 is not modified yet
            int[] next;
            if (i + 1 < n) {
                next = f[i + 1];
            } else {
                next = cur; //row n is equal to row n - 1
            }

            computeRow(prev, cur, next, c, f[i]);

            int[] aux = prev;
            prev = cur;
            cur = aux;
        }
    }

    //apply convolution with threads ---- block of rows (variant 1b)
    public static void applyConvolutionParallelRows(int[][] f, int[][] c, int p) throws InterruptedException {
        int n = f.length;

        //if there are more threads than rows, we can only use n threads
        if (p > n) {
            p = n;
        }

        CyclicBarrier barrier = new CyclicBarrier(p);
        MyThreadOne[] threads = new MyThreadOne[p];
        int base = n / p; //base number of rows per thread
        int rem = n % p; //remaining rows to distribute among the first 'rem' threads
        int start = 0;

        for (int t = 0; t < p; t++) {
            int end;
            if (t < rem) {
                end = start + base + 1;
            } else {
                end = start + base;
            }
            threads[t] = new MyThreadOne(f, c, start, end, barrier);
            threads[t].start();
            start = end;
        }

        for (MyThreadOne th : threads) {
            th.join();
        }
    }
}
