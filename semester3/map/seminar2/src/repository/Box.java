package repository;
import model.Item;
public class Box {
    private Item[] box;
    private int count = 0;

    public Box(){this.box = new Item[10];}

    public void addItem(Item item){
        if (count>=box.length){
            System.out.println("Repo is full");
        }
        else{
            box[count++] = item;
        }
    }

    public Item getItem(int index){
        return box[index];
    }

    public int getCount(){
        return count;
    }
}
