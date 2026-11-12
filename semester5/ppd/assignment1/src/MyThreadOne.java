public class MyThreadOne extends Thread {
    private final int[][] f;
    private final int[][] c;
    private final int[][] v;
    private final int startRow;
    private final int endRow;   // exclusive

    public MyThreadOne(int[][] f, int[][] c, int[][] v, int startRow, int endRow) {
        this.f = f;
        this.c = c;
        this.v = v;
        this.startRow = startRow;
        this.endRow = endRow;
    }

    @Override
    public void run() {
        int n = f.length;
        int m = f[0].length;
        int k = c.length;
        int r = k / 2;

        for (int i = startRow; i < endRow; i++) {
            for (int j = 0; j < m; j++) {
                int sum = 0;
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
    }
}
