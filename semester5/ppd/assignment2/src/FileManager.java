import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

public class FileManager {

    //read the matrices from file (they are separated by empty lines)
    public static int[][][] readFile(String filename) throws IOException {
        List<int[][]> matrices = new ArrayList<>();
        List<int[]> rows = new ArrayList<>();
        try (BufferedReader reader = Files.newBufferedReader(Path.of(filename))) {
            String line;
            while ((line = reader.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) {
                    //an empty line ends the current matrix
                    if (!rows.isEmpty()) {
                        matrices.add(rows.toArray(new int[0][]));
                        rows.clear();
                    }
                    continue;
                }
                String[] tokens = line.split("\\s+");
                int[] row = new int[tokens.length];
                for (int j = 0; j < tokens.length; j++) {
                    row[j] = Integer.parseInt(tokens[j]);
                }
                rows.add(row);
            }
        }
        if (!rows.isEmpty()) {
            matrices.add(rows.toArray(new int[0][]));
        }
        return matrices.toArray(new int[0][][]);
    }

    //write the matrices to file, separated by an empty line
    public static void writeFile(String filename, int[][]... matrices) throws IOException {
        try (BufferedWriter writer = Files.newBufferedWriter(Path.of(filename))) {
            StringBuilder sb = new StringBuilder();
            for (int t = 0; t < matrices.length; t++) {
                if (t > 0) {
                    writer.write(System.lineSeparator());
                }
                for (int[] row : matrices[t]) {
                    sb.setLength(0);
                    for (int number : row) {
                        sb.append(number).append(' ');
                    }
                    sb.append(System.lineSeparator());
                    writer.write(sb.toString());
                }
            }
        }
    }
}
