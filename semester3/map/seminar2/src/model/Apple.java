package model;

// by default package level
// public class Apple extends fruit for inheritance

public class Apple  implements Item {

    private int weight;

    public Apple(int weight) {
        this.weight = weight;
    }

    @Override
    public int getWeight() {
        return this.weight;
    }

    @Override
    public String toPrint() {
        return "Apple " + this.getWeight();
    }
}

/*
public class Apple extends Item {

    public Apple(int weight) {
        super(weight);
    }

    @Override
    public void print(){
        System.out.println("Apple:");
        System.out.println("Weight"+getWeight());
    }
}
*/