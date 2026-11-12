import java.util.Random;

public class RandomNumberGenerator {
    private final Random engine = new Random();
    public int nextInt(int low, int high) {
        return low + engine.nextInt(high - low + 1);
    }
}
