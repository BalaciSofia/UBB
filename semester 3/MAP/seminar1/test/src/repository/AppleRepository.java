package repository;
import model.Apple;

public class AppleRepository {
    private Apple[] apples;
    private int count = 0;

    public AppleRepository() {
        this.apples = new Apple[2];
    }

    public void addApple(Apple apple) {
        if(count >= apples.length) {
            // throw an error;
            System.out.println("Repo is full");
        }
        else {
            apples[count++] = apple;
        }

        apple.setWeight(3000); // since it is passed by reference all apples will have 3000 weight
    }

    public Apple getApple(int index) {
        return apples[index];
    }
}
