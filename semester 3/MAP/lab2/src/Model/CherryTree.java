package Model;

public class CherryTree implements Tree {
    private int age;

    public CherryTree(int age) {
        this.age = age;
    }

    @Override
    public int getAge()
    {
        return age;
    }

    @Override
    public String toString(){
        return "Cherry tree w/ age: "+ this.age ;
    }
}
