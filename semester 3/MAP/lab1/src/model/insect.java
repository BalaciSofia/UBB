package model;

public class insect {
    protected int age;
    protected String name;

    public insect(int age, String name) {
        this.age = age;
        this.name = name;
    }

    public int getAge() {
        return this.age;
    }

    public String getName() {
        return this.name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void print(){
        IO.println(this.age+" "+this.name);
    }
}
