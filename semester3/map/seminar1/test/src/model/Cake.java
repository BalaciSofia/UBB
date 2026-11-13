package model;

public class Cake {
    private int weight;
    private int calories;

    public Cake(int weight, int calories) {
        this.weight = weight;
        this.calories = calories;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public void setCalories(int calories) {
        this.calories = calories;
    }

    public int getWeight() {
        return weight;
    }

    public int getCalories() {
        return calories;
    }
}
