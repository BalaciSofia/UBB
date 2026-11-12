void main(String[] args) throws InterruptedException {

    //to generate the input fils
    int rows, cols, k;
    if (args.length > 0 && Objects.equals(args[0], "gen")) {
        if (args.length != 4) {
            System.err.println("Usage: gen <rows> <cols> <k>");
            return;
        }
        rows = Integer.parseInt(args[1]);
        cols = Integer.parseInt(args[2]);
        k = Integer.parseInt(args[3]);
        if (rows <= 0 || cols <= 0 || k <= 0 || k % 2 == 0) {
            System.err.println("rows and cols must be positive, k must be a positive odd number");
            return;
        }
        GenerateAndWriteMatrices.generateAndWriteMatrices(rows, cols, k);
        System.out.println("Generated matrices and convolution matrix.");
        return;
    }

    //number of threads
    int p = 4;
    if (args.length > 0) {
        p = Integer.parseInt(args[0]);
        if (p <= 0) {
            System.err.println("The number of threads must be positive");
            System.exit(1);
        }
    }

    //variant of the algorithm to use: seq, rows or cols
    String variant = "";
    if (args.length > 1) {
        variant = args[1];
        if (!variant.equals("seq") && !variant.equals("rows") && !variant.equals("cols")) {
            System.err.println("The version must be seq, rows or cols");
            System.exit(1);
        }
    }

    // read the input files
    int [][] convMatrix = InputOutput.readConvolutionMatrix();
    int [][] fMatrix = InputOutput.readMatrixF();

    //time the selected variant
    long start = System.nanoTime();
    int[][] vMatrix;
    if (variant.equals("seq")) {
        vMatrix = Convolution.applyConvolutionSequentially(fMatrix, convMatrix);
    } else if (variant.equals("rows")) {
        vMatrix = Convolution.applyConvolutionParallelRows(fMatrix, convMatrix, p);
    } else if (variant.equals("cols")) {
        vMatrix = Convolution.applyConvolutionParallelCols(fMatrix, convMatrix, p);
    } else {
        //vMatrix = Convolution.applyConvolutionSequentially(fMatrix, convMatrix);
        vMatrix = Convolution.applyConvolutionParallelRows(fMatrix, convMatrix, p);
        //vMatrix = Convolution.applyConvolutionParallelCols(fMatrix, convMatrix, p);
    }
    long end = System.nanoTime();

    System.out.println((end - start) / 1_000_000.0);

    //check if the result is correct
    boolean ok = InputOutput.isResultOk(InputOutput.EXPECTED_FILE, vMatrix);

    //write the result to the output file
    boolean written = InputOutput.writeOutput(InputOutput.OUTPUT_FILE, vMatrix);

    if (!ok || !written) {
        System.exit(1);
    }
}
