package view;
import controller.Controller;

public class RunExampleCommand extends Command {
    private Controller controller;

    public RunExampleCommand(String key, String description, Controller ctr) {
        super(key, description);
        this.controller= ctr;
    }

    @Override
    public void execute() {
        try {
            controller.allSteps();
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
