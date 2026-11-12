void main(String[] args) throws InterruptedException {

    //to generate the input file (the convolution matrix is always 3x3)
    int rows, cols;
    if (args.length > 0 && Objects.equals(args[0], "gen")) {
        if (args.length != 3) {
            System.err.println("Usage: gen <rows> <cols>");
            return;
        }
        rows = Integer.parseInt(args[1]);
        cols = Integer.parseInt(args[2]);
        if (rows <= 0 || cols <= 0) {
            System.err.println("rows and cols must be positive");
            return;
        }
        GenerateAndWriteMatrices.generateAndWriteMatrices(rows, cols);
        System.out.println("Generated " + InputOutput.DATA_FILE + " and " + InputOutput.EXPECTED_FILE + ".");
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

    //variant of the algorithm to use: seq or rows
    String variant = "";
    if (args.length > 1) {
        variant = args[1];
        if (!variant.equals("seq") && !variant.equals("rows")) {
            System.err.println("The version must be seq or rows");
            System.exit(1);
        }
    }

    // read the input file
    int[][][] data = InputOutput.readData();
    int[][] fMatrix = data[0];
    int[][] convMatrix = data[1];

    //time the selected variant (the result is written in fMatrix)
    long start = System.nanoTime();
    if (variant.equals("seq")) {
        Convolution.applyConvolutionSequentially(fMatrix, convMatrix);
    } else if (variant.equals("rows")) {
        Convolution.applyConvolutionParallelRows(fMatrix, convMatrix, p);
    } else {
        //Convolution.applyConvolutionSequentially(fMatrix, convMatrix);
        Convolution.applyConvolutionParallelRows(fMatrix, convMatrix, p);
    }
    long end = System.nanoTime();

    System.out.println((end - start) / 1_000_000.0);

    //check if the result is correct
    boolean ok = InputOutput.isResultOk(InputOutput.EXPECTED_FILE, fMatrix);

    //write the result to the output file
    boolean written = InputOutput.writeOutput(InputOutput.OUTPUT_FILE, fMatrix);

    if (!ok || !written) {
        System.exit(1);
    }
}
