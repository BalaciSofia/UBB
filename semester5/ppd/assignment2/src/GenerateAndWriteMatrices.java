public class GenerateAndWriteMatrices {

    public static void generateAndWriteMatrices(int rows, int cols){
        int k = 3;
        RandomNumberGenerator rng = new RandomNumberGenerator();

        //generate matrix F
        int[][] fMatrix = new int[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                fMatrix[i][j] = rng.nextInt(1, 100);
            }
        }

        //generate convolution matrix
        int [][] convMatrix = new int[k][k];
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                convMatrix[i][j] = rng.nextInt(1, 100);
            }
        }

        //write both of them in the data file
        try {
            FileManager.writeFile(InputOutput.DATA_FILE, fMatrix, convMatrix);
        } catch (Exception e) {
            System.err.println("Error writing " + InputOutput.DATA_FILE + ": " + e.getMessage());
        }

        //compute and write expected result matrix (F is filtered in place)
        Convolution.applyConvolutionSequentially(fMatrix, convMatrix);
        try {
            FileManager.writeFile(InputOutput.EXPECTED_FILE, fMatrix);
        } catch (Exception e) {
            System.err.println("Error writing expected result matrix to file: " + e.getMessage());
        }
    }
}
