package controller;

import model.butterfly;
import model.insect;
import java.util.Scanner;

public class controller {
    public void run() {

        //----------average
        IO.println(String.format("Hello and welcome!"));
        int n ,number;
        int sum=0;
        IO.println("Please enter a number:");
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        for (int i = 1; i <= n; i++) {
            number = sc.nextInt();
            sum = sum + number;
        }
        double average = (double) sum /n;
        IO.println("The average is: " + average);
        //-----------

        insect i = new insect(2,"ana");
        i.print();
        butterfly b= new butterfly(1,"blue","Bluey");
        b.print();

        i.setAge(5);
        i.print();

        i.setName("none");
        i.print();

        b.setAge(5);
        b.print();

        b.setName("none");
        b.print();

        b.setColour("red");
        b.print();

   }
}
