public class Convolution {

    public static int[][] applyConvolutionSequentially(int[][] f, int[][] c) {
        int n = f.length; //rows
        int m = f[0].length; //columns
        int k = c.length; //size of the convolution matrix
        int r = k / 2; //radius of the convolution matrix
        int[][] v = new int[n][m];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int sum = 0;
                // sum for the element (i, j)
                for (int a = 0; a < k; a++) {
                    for (int b = 0; b < k; b++) {
                        int fi = i + a - r;
                        int fj = j + b - r;

                        if (fi < 0) fi = 0;
                        if (fi >= n) fi = n - 1;
                        if (fj < 0) fj = 0;
                        if (fj >= m) fj = m - 1;

                        sum += f[fi][fj] * c[a][b];
                    }
                }
                v[i][j] = sum;
            }
        }
        return v;
    }

    //apply convolution with threads ---- block of rows
    public static int[][] applyConvolutionParallelRows(int[][] f, int[][] c, int p) throws InterruptedException {
        int n = f.length;
        int[][] v = new int[n][f[0].length];

        //if there are more threads than rows, we can only use n threads
        if (p > n) {
            p = n;
        }

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
            threads[t] = new MyThreadOne(f, c, v, start, end);
            threads[t].start();
            start = end;
        }

        for (MyThreadOne th : threads) {
            th.join();
        }
        return v;
    }

    //apply convolution with threads ---- a block of columns
    public static int[][] applyConvolutionParallelCols(int[][] f, int[][] c, int p) throws InterruptedException {
        int m = f[0].length;
        int[][] v = new int[f.length][m];

        if (p > m) {
            p = m;
        }

        MyThreadTwo[] threads = new MyThreadTwo[p];
        int base = m / p;
        int rem = m % p;
        int start = 0;

        for (int t = 0; t < p; t++) {
            int end;
            if (t < rem) {
                end = start + base + 1;
            } else {
                end = start + base;
            }
            threads[t] = new MyThreadTwo(f, c, v, start, end);
            threads[t].start();
            start = end;
        }

        for (MyThreadTwo th : threads) {
            th.join();
        }
        return v;
    }
}
