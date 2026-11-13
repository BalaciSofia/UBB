package GUI;

import controller.Controller;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionary;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeap;
import model.adts.heapADT.MyHeapI;
import model.adts.listADT.MyList;
import model.adts.listADT.MyListI;
import model.adts.stackADT.MyStack;
import model.adts.stackADT.MyStackI;
import model.statements.Statement;
import model.types.Type;
import model.values.Value;
import repository.HardcodedRepo;
import repository.Repo;
import repository.RepoI;

import java.io.BufferedReader;
import java.util.List;

public class SelectProgramGUI extends Application {
    private ListView<String> programListView;
    private List<Statement> programs;

    @Override
    public void start(Stage stage) {
        HardcodedRepo hardcodedRepo = new HardcodedRepo();
        programs = hardcodedRepo.getStatementsList();

        programListView = new ListView<>();
        for (Statement stmt : programs) {
            programListView.getItems().add(stmt.toString());
        }

        Button selectButton = new Button("Select program");
        selectButton.setOnAction(e -> handleSelect(stage));

        VBox root = new VBox(10,
                programListView,
                selectButton
        );
        root.setPadding(new Insets(10));

        root.setStyle("""
-fx-accent: pink;
-fx-focus-color: pink;
""");

        root.setPrefSize(600, 400);
        stage.setTitle("Program Selection");
        stage.setScene(new Scene(root));
        stage.show();
    }

    private void handleSelect(Stage currentStage) {
        int index = programListView.getSelectionModel().getSelectedIndex();

        if (index < 0) {
            showError("Please select a program!");
            return;
        }

        Statement selectedStmt = programs.get(index);
        Controller controller = createProgram(selectedStmt, "log" + (index + 1) + ".txt");

        MainGUI mainGUI = new MainGUI(controller);
        mainGUI.show();
    }

    private Controller createProgram(Statement s, String filename) {
        MyDictionaryI<String, Type> typeEnv = new MyDictionary<>();
        try {
            s.typeCheck(typeEnv);
        } catch (Exception e) {
            showError("Typecheck error: " + e.getMessage());
            return null;
        }
        MyStackI<Statement> exeStack = new MyStack<>();
        exeStack.push(s);
        ProgramState prgState = new ProgramState(
                exeStack,
                new MyDictionary<>(),
                new MyList<>(),
                new MyDictionary<>(),
                new MyHeap()
        );
        RepoI repo = new Repo(prgState, filename);
        return new Controller(repo);
    }

    private void showError(String msg) {
        Alert alert = new Alert(Alert.AlertType.ERROR, msg, ButtonType.OK);
        alert.showAndWait();
    }
}
