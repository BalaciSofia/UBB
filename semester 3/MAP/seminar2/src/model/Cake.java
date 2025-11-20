package model;

public class Cake implements Item{
    private int weight;
    private int calories;

    public Cake(int weight, int calories) {
        this.weight = weight;
        this.calories = calories;
    }

    @Override
    public int getWeight() {
        return this.weight;
    }

    @Override
    public String toPrint()
    {
        return "Cake " + this.getWeight();
    }
}

/*
public class Cake extends Item {

    private int calories;

    public Cake(int weight, int calories) {
        super(weight);
        this.calories = calories;
    }

    public void setCalories(int calories) {
        this.calories = calories;
    }

    public int getCalories() {
        return calories;
    }

    @Override
    public void print(){
        System.out.println("Cake:");
        System.out.println("Weight"+getWeight());
    }
}
*/