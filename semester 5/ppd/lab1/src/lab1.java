class MyThread extends Thread{
    private int id;
    private int start;
    private int end;
    private double[] A;
    private double [] B;
    private double[] C;

    MyThread(int id, int start, int end, double[] A, double[] B, double[] C) {
        this.id = id;
        this.start = start;
        this.end = end;
        this.A = A;
        this.B = B;
        this.C = C;
    }

    public void run() {
        //String str = "Thread Started Running..." + " ID: " + id + " Start: " + start + " End: " + end;
        //System.out.println(str);
        for( int i = start; i < end; i++) {
            //C[i] = A[i] + B[i];
            C[i] = sum(A[i], B[i]);
        }
    }
}

class MyThreadCyclic extends Thread{
    private int id;
    private int start;
    int pass;
    int n;
    private double[] A;
    private double [] B;
    private double[] C;

    MyThreadCyclic(int id, int start, int pass, int n, double[] A, double[] B, double[] C) {
        this.id = id;
        this.start = start;
        this.pass = pass;
        this.n = n;
        this.A = A;
        this.B = B;
        this.C = C;
    }

    public void run() {
        //String str = "Thread Started Running..." + " ID: " + id + " Start: " + start + " Pass: " + pass;
        //System.out.println(str);
        for( int i = start; i < n; i=i+pass) {
            //C[i] = A[i] + B[i];
            C[i] = sum(A[i], B[i]);
        }
    }
}

void initialize(double[] A, int n) {
    for( int i = 0; i < n; i++) {
        A[i] = i;
    }
}
void addVectorsSequential(double[] A, double[] B, double[] C, int n) {
    for( int i = 0; i < n; i++) {
        //C[i] = A[i] + B[i];
        C[i] = sum(A[i], B[i]);
    }
}

double sum (double a, double b){
    double c = Math.sqrt(Math.sqrt(a*a + b*b)+ Math.sqrt(a*a - b*b));
    return c;
}

void addVectorsParallel(double[] A, double[] B, double[] C, int n, int p) {
    MyThread[] threads = new MyThread[p];
    int chunkSize = n / p;
    for( int i = 0; i < p; i++) {
        int start = i * chunkSize;
        int end;
        if (i == p - 1) {
            end = n;
        } else {
            end = start + chunkSize;
        }
        threads[i] = new MyThread(i, start, end, A, B, C);
        threads[i].start();
    }
    for( int i = 0; i < p; i++) {
        try {
            threads[i].join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}

void addVectorParallelCyclic(double[] A, double[] B, double[] C, int n, int p) {
    MyThreadCyclic[] threads = new MyThreadCyclic[p];
    for( int i = 0; i < p; i++) {
        threads[i] = new MyThreadCyclic(i, i, p, n, A, B, C);
        threads[i].start();
    }
    for( int i = 0; i < p; i++) {
        try {
            threads[i].join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}

void areEqual(double[] A, double[] B, int n) {
    for( int i = 0; i < n; i++) {
        if (A[i] != B[i]) {
            System.out.println("Not equal at index " + i);
            return;
        }
    }
    System.out.println("Results are equal");
}
void main() {
    int n = 10000;  // paralel>secvential 1000000 & 3 cu suma simpla si 100000 & 3 cu suma complexa
    int p = 16;
    double[] A = new double[n];
    double[] B = new double[n];
    double[] C = new double[n];
    double[] D = new double[n];
    double[] E = new double[n];
    initialize(A, n);
    initialize(B, n);

    long t1 = System.nanoTime();
    addVectorsSequential(A, B, C, n);
    long t2 = System.nanoTime();
    long ns = (t2 - t1);
    System.out.print("sequential time: ");
    System.out.print(ns);
    System.out.println();

    long t3 = System.nanoTime();
    addVectorsParallel(A, B, D, n,p);
    long t4 = System.nanoTime();
    long ns2 = (t4 - t3);
    System.out.print("parallel time: ");
    System.out.print(ns2);
    System.out.println();
    areEqual(C, D, n);

    long t5 = System.nanoTime();
    addVectorParallelCyclic(A, B, E, n,p);
    long t6 = System.nanoTime();
    long ns3 = (t6 - t5);
    System.out.print("cyclic parallel time: ");
    System.out.print(ns3);
    System.out.println();
    areEqual(C, E, n);
}
