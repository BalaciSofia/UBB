import java.io.IOException;
import java.util.Arrays;

public class InputOutput {
    public static final String MATRIX_F_FILE = "MatrixF.txt";
    public static final String CONVOLUTION_FILE = "ConvolutionM.txt";
    public static final String EXPECTED_FILE = "expectedResult.txt";
    public static final String OUTPUT_FILE = "output.txt";

    public static int[][] readMatrixF() {
        try {
            return FileManager.readFile(MATRIX_F_FILE);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static int[][] readConvolutionMatrix() {
        try {
            return FileManager.readFile(CONVOLUTION_FILE);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static boolean writeOutput(String filename, int[][] v) {
        try {
            FileManager.writeFile(filename, v);
        } catch (IOException e) {
            System.err.println("Error writing " + filename + ": " + e.getMessage());
            return false;
        }
        return true;
    }

    //compares the computed matrix with the matrix from the file
    public static boolean isResultOk(String filename, int[][] v) {
        int[][] expected;
        try {
            expected = FileManager.readFile(filename);
        } catch (IOException e) {
            System.err.println("Error reading " + filename + ": " + e.getMessage());
            return false;
        }

        if (!Arrays.deepEquals(v, expected)) {
            System.err.println("Error: the computed result is different from " + filename);
            return false;
        }
        return true;
    }
}
