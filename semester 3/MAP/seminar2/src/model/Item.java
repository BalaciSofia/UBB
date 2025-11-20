package model;

public interface Item {
    int getWeight();
    String toPrint();
}

/*
public class Item {
    private int weight;

    public Item(int weight) {
        this.weight = weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public int getWeight() {
        return weight;
    }

    public void print(){
        System.out.println("Item");
        System.out.println("Weight: " + weight);
    }
}
*/
