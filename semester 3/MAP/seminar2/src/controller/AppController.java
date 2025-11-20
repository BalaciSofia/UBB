package controller;

import model.Apple;
import model.Books;
import model.Cake;
import repository.Box;

public class AppController {
    private Box  box;

    public AppController(Box box) {
        this.box = box;
    }

    private void populate(){
        Apple a =new Apple(150);
        Apple b =new Apple(250);
        Apple c =new Apple(130);
        Cake d = new Cake(500,1700);
        Cake e =new Cake(199,1700);
        Cake f =new Cake(300,1700);
        Books g =new Books(80,"ana","pavel");
        Books h =new Books(201,"iupi","ura");
        Books k =new Books(140,"karan","ursu");
        this.box.addItem(a);
        this.box.addItem(b);
        this.box.addItem(c);
        this.box.addItem(d);
        this.box.addItem(e);
        this.box.addItem(f);
        this.box.addItem(g);
        this.box.addItem(h);
        this.box.addItem(k);
    }

    private void displayBox(){
        int i;
        for (i=0;i<this.box.getCount();i++ ){
            if(this.box.getItem(i).getWeight()>=200) System.out.println(this.box.getItem(i).toPrint());
        }
    }

    public void run() {
        populate();
        displayBox();
    }
}
