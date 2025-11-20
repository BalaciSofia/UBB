package model;


public class Books implements Item {
    private int weight;
    private String title;
    private String author;

    public Books(int weight,String title, String author) {
        this.weight = weight;
        this.title = title;
        this.author = author;
    }

    @Override
    public int getWeight() {
        return this.weight;
    }

    @Override
    public String toPrint() {
        return "Book " + this.getWeight();
    }
}
/*

public class Books extends Item{
    private String title;
    private String author;


    public Books(int weight,String title, String author) {
        super(weight);
        this.title = title;
        this.author = author;
    }

    @Override
    public void print(){
        System.out.println("Book:");
        System.out.println("Weight"+getWeight());
    }
}
*/