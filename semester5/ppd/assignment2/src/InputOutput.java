import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class InputOutput {
    public static final String DATA_FILE = "date.txt";
    public static final String EXPECTED_FILE = "expectedResult.txt";
    public static final String OUTPUT_FILE = "output.txt";

    //reads matrix F and the convolution matrix from the data file: {F, C}
    public static int[][][] readData() {
        int[][][] matrices;
        try {
            matrices = FileManager.readFile(DATA_FILE);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        if (matrices.length != 2) {
            throw new RuntimeException(DATA_FILE + " must contain matrix F, an empty line and the convolution matrix");
        }
        int[][] c = matrices[1];
        if (c.length != 3 || c[0].length != 3 || c[1].length != 3 || c[2].length != 3) {
            throw new RuntimeException("The convolution matrix from " + DATA_FILE + " must be 3x3");
        }
        return matrices;
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
    //the numbers are compared line by line while reading, so no other matrix is allocated
    public static boolean isResultOk(String filename, int[][] v) {
        try (BufferedReader reader = Files.newBufferedReader(Path.of(filename))) {
            for (int[] row : v) {
                String line = reader.readLine();
                if (line == null || !rowEquals(line, row)) {
                    System.err.println("Error: the computed result is different from " + filename);
                    return false;
                }
            }
            String line;
            while ((line = reader.readLine()) != null) {
                if (!line.isBlank()) {
                    System.err.println("Error: " + filename + " has more rows than the computed result");
                    return false;
                }
            }
        } catch (IOException e) {
            System.err.println("Error reading " + filename + ": " + e.getMessage());
            return false;
        }
        return true;
    }

    private static boolean rowEquals(String line, int[] row) {
        String[] tokens = line.trim().split("\\s+");
        if (tokens.length != row.length) {
            return false;
        }
        for (int j = 0; j < row.length; j++) {
            if (Integer.parseInt(tokens[j]) != row[j]) {
                return false;
            }
        }
        return true;
    }
}
