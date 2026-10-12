import java.util.Locale;

public class Main {
    static final int MAX_N = 1000000;
    static final double MIN_VALUE = 0.0;
    static final double MAX_VALUE = 1000.0;

    static double[] addVectors(double[] vec1, double[] vec2) {
        if (vec1.length != vec2.length) {
            throw new IllegalArgumentException("Size of vectors do not match");
        }
        double[] result = new double[vec1.length];
        for (int i = 0; i < vec1.length; i++) {
            result[i] = vec1[i] + vec2[i];
        }
        return result;
    }

    static void generateFiles() {
        RandomNumberGenerator rng = new RandomNumberGenerator();
        FileManager manager = new FileManager();
        int n = rng.nextInt(1, MAX_N);

        double[] A = new double[n];
        double[] B = new double[n];
        for (int i = 0; i < n; i++) {
            A[i] = rng.nextDouble(MIN_VALUE, MAX_VALUE);
            B[i] = rng.nextDouble(MIN_VALUE, MAX_VALUE);
        }
        manager.writeFile("A.txt", A);
        manager.writeFile("B.txt", B);
        System.out.println("Generated " + n + " numbers in A.txt and B.txt");
    }

    public static void main(String[] args) {
        if (args.length > 0 && args[0].equals("gen")) {
            generateFiles();
            return;
        }
        FileManager manager = new FileManager();
        double[] A = manager.readFile("A.txt");
        double[] B = manager.readFile("B.txt");
        long t1 = System.nanoTime();
        double[] C = addVectors(A, B);
        long t2 = System.nanoTime();
        manager.writeFile("C.txt", C);
        double ms = (t2 - t1) / 1_000_000.0;
        System.out.print(String.format(Locale.US, "%.6f", ms));
    }
}
