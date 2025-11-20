import Repository.TreeRepository;
import Controller.TreeController;
import View.TreeView;

public class main {
    public static void main(String[] args) {
        TreeRepository treeRepository = new TreeRepository();
        TreeController treeController = new TreeController(treeRepository);
        TreeView treeView = new TreeView(treeController);
        treeView.start();
    }
}
