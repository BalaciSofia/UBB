import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class FileManager {

    public double[] readFile(String filename) {
        try {
            String content = Files.readString(Path.of(filename)).trim();
            if (content.isEmpty()) {
                return new double[0];
            }
            String[] tokens = content.split("\\s+");
            double[] result = new double[tokens.length];
            for (int i = 0; i < tokens.length; i++) {
                result[i] = Double.parseDouble(tokens[i]);
            }
            return result;
        } catch (IOException e) {
            return new double[0];
        }
    }

    public void writeFile(String filename, double[] numbers) {
        try (BufferedWriter writer = Files.newBufferedWriter(Path.of(filename))) {
            StringBuilder sb = new StringBuilder();
            for (double number : numbers) {
                sb.append(number).append(' ');
            }
            writer.write(sb.toString());
        } catch (IOException e) {
        }
    }
}
