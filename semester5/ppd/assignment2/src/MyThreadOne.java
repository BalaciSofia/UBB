import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

//variant 1b: copy the neighbour rows, barrier, then update the rows of the thread
public class MyThreadOne extends Thread {
    private final int[][] f;
    private final int[][] c;
    private final int startRow;
    private final int endRow;
    private final CyclicBarrier barrier;

    public MyThreadOne(int[][] f, int[][] c, int startRow, int endRow, CyclicBarrier barrier) {
        this.f = f;
        this.c = c;
        this.startRow = startRow;
        this.endRow = endRow;
        this.barrier = barrier;
    }

    @Override
    public void run() {
        int n = f.length;  // rows
        int m = f[0].length; // cols
        int[] prev = new int[m];   //original row above
        int[] cur = new int[m];    //original current row
        int[] bottom = new int[m]; //original row below

        //1. copy the boundaries (they belong to the neighbour threads)
        int above; // if there is no above row, we will use the first row of the matrix
        if ( startRow > 0 ){
            above = startRow - 1;
        }
        else {
            above = 0;
        }
        int below; // if there is no below row, we will use the last row of the matrix
        if ( endRow < n ){
            below = endRow;
        }
        else {
            below = n - 1;
        }

        //copy them into the arrays
        System.arraycopy(f[above], 0, prev, 0, m);
        System.arraycopy(f[below], 0, bottom, 0, m);

        //wait until all threads copied their boundaries, nobody modifies the matrix before that
        try {
            barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            throw new RuntimeException(e);
        }

        //update the rows, using the copied boundaries where needed
        for (int i = startRow; i < endRow; i++) {
            System.arraycopy(f[i], 0, cur, 0, m);

            int[] next; // the original row below, or the copied bottom row if we are at the last row of the thread
            if (i + 1 < endRow) {
                next = f[i + 1];
            } else {
                next = bottom;
            }

            Convolution.computeRow(prev, cur, next, c, f[i]);

            int[] aux = prev;
            prev = cur;
            cur = aux;
        }
    }
}
