package model;

// by default package level
// public class Apple extends fruit for inheritance

public class Apple {
    private int weight;

    public Apple(int weight) {
        this.weight = weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public int getWeight() {
        return weight;
    }
}
