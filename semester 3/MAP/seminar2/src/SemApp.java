import controller.AppController;
import repository.Box;
public class SemApp {
    public static void main(String[] args) {
        Box box = new Box();
        AppController appController = new AppController(box);
        appController.run();
    }
}
