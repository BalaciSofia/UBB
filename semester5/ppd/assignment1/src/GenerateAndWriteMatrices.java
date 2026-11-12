public class GenerateAndWriteMatrices {

    public static void generateAndWriteMatrices(int rows, int cols, int k){
        RandomNumberGenerator rng = new RandomNumberGenerator();

        //generate and write matrix F
        int[][] fMatrix = new int[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                fMatrix[i][j] = rng.nextInt(1, 100);
            }
        }
        try {
            FileManager.writeFile(InputOutput.MATRIX_F_FILE, fMatrix);
        } catch (Exception e) {
            System.err.println("Error writing integer matrix to file: " + e.getMessage());
        }

        //generate and write convolution matrix
        int [][] convMatrix = new int[k][k];
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                convMatrix[i][j] = rng.nextInt(1, 100);
            }
        }
        try {
            FileManager.writeFile(InputOutput.CONVOLUTION_FILE, convMatrix);
        } catch (Exception e) {
            System.err.println("Error writing convolution matrix to file: " + e.getMessage());
        }

        //compute and write expected result matrix
        int[][] result = Convolution.applyConvolutionSequentially(fMatrix, convMatrix);
        try {
            FileManager.writeFile(InputOutput.EXPECTED_FILE, result);
        } catch (Exception e) {
            System.err.println("Error writing expected result matrix to file: " + e.getMessage());
        }
    }
}
