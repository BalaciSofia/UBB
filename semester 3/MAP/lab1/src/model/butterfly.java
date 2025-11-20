package model;
import model.insect;

public class butterfly extends insect {
    private String colour;

    public butterfly(int age,String colour,String name) {
        super(age, name);
        this.colour = colour;
    }

    public String getColour() {
        return this.colour;
    }

    public void setColour(String colour) {
        this.colour = colour;
    }
    
    @Override
    public void print(){
        IO.println(getAge()+" "+getColour()+" "+getName());
    }
}
