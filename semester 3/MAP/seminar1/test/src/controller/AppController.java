package controller;

import model.Apple;
import model.Cake;
import repository.AppleRepository;

public class AppController {
    public void run() {
        Apple apple = new Apple(150);
        Cake myCake = new Cake(500, 300); // myCake is a reference to the new cake
        Cake sameCake = myCake; // same reference
        System.out.println("Apple weight: " + apple.getWeight());
        System.out.println("Cake weight: " + myCake.getWeight());

        AppleRepository appleRepository = new AppleRepository();
        appleRepository.addApple(apple);
        appleRepository.addApple(new Apple(100));

        System.out.println("Apple: " + appleRepository.getApple(0).getWeight() + " grams");
        System.out.println("Apple: " + appleRepository.getApple(1).getWeight() + " grams");
    }
}
