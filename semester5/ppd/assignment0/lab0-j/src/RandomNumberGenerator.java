import java.util.Random;

public class RandomNumberGenerator {
    private final Random engine = new Random();
    public int nextInt(int low, int high) {
        return low + engine.nextInt(high - low + 1);
    }
    public double nextDouble(double low, double high) {
        return low + engine.nextDouble() * (high - low);
    }
}
