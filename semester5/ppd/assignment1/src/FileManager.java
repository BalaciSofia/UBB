import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class FileManager {

    //read matrix from file
    public static int[][] readFile(String filename) throws IOException {
        String content = Files.readString(Path.of(filename)).trim();
        if (content.isEmpty()) {
            return new int[0][0];
        }
        String[] lines = content.split("\\R");
        int[][] result = new int[lines.length][];
        for (int i = 0; i < lines.length; i++) {
            String[] tokens = lines[i].trim().split("\\s+");
            result[i] = new int[tokens.length];
            for (int j = 0; j < tokens.length; j++) {
                result[i][j] = Integer.parseInt(tokens[j]);
            }
        }
        return result;
    }

    //write matrix to file
    public static void writeFile(String filename, int[][] numbers) throws IOException {
        try (BufferedWriter writer = Files.newBufferedWriter(Path.of(filename))) {
            StringBuilder sb = new StringBuilder();
            for (int[] row : numbers) {
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
