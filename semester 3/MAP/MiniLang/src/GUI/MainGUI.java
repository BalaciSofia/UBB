package GUI;

import controller.Controller;
import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.adts.listADT.MyListI;
import model.values.Value;

import java.io.BufferedReader;
import java.util.AbstractMap;
import java.util.List;
import java.util.Map;

import static javafx.collections.FXCollections.observableArrayList;


public class MainGUI {
    private final Controller controller;
    private TextField no_programstates;
    private TableView<Map.Entry<Integer, Value>> heapTableView;
    private ListView<Value> outListView;
    private ListView<String> fileTableListView;
    private ListView<Integer> programStatesListView;
    private TableView<Map.Entry<String, Value>> symTableView;
    private ListView<String> exeStackListView;


    public MainGUI(Controller controller) {
        this.controller = controller;
        this.no_programstates = new TextField("Number of Program States: " + controller.numberOfPrograms());;

        this.heapTableView = new TableView<>();
        TableColumn<Map.Entry<Integer, Value>, Integer> addressColumn = new TableColumn<>("Address");
        addressColumn.setCellValueFactory(cd -> new SimpleObjectProperty<>(cd.getValue().getKey()));
        TableColumn<Map.Entry<Integer, Value>, Value> valueColumn = new TableColumn<>("Value");
        valueColumn.setCellValueFactory(cd -> new SimpleObjectProperty<>(cd.getValue().getValue()));
        this.heapTableView.getColumns().setAll(addressColumn, valueColumn);

        this.outListView = new ListView<>();

        this.fileTableListView = new ListView<>();

        this.programStatesListView = new ListView<>();

        this.symTableView = new TableView<>();
        TableColumn<Map.Entry<String, Value>, String> varNameColumn = new TableColumn<>("Variable Name");
        varNameColumn.setCellValueFactory(cd -> new SimpleObjectProperty<>(cd.getValue().getKey()));
        TableColumn<Map.Entry<String, Value>, Value> varValueColumn = new TableColumn<>("Value");
        varValueColumn.setCellValueFactory(cd -> new SimpleObjectProperty<>(cd.getValue().getValue()));
        this.symTableView.getColumns().setAll(varNameColumn, varValueColumn);

        this.exeStackListView = new ListView<>();

        heapTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);
        symTableView.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);

    }

    public void show() {
        Stage stage = new Stage();

        //program states list view selection listener
        programStatesListView.getSelectionModel().selectedItemProperty().addListener((obs, oldId, newId) -> {
            if (newId != null) {
                showProgramStateDetails(newId);
            }
        });

        //initial population of program states list view
        List<ProgramState> programs = controller.getRepository().getProgramList();
        ObservableList<Integer> programIds = observableArrayList();
        for (ProgramState ps : programs) {
            programIds.add(ps.getId());
        }
        this.programStatesListView.setItems(programIds);

        //run button
        Button runButton = new Button("Run one step");
        runButton.setOnAction(e -> handleSelect(stage));

        //no of program states
        no_programstates.setEditable(false);

        //boxes for each component
        VBox heapBox = new VBox(6,new Label("Heap:"), heapTableView);
        VBox outBox  = new VBox(6,new Label("Output:"), outListView);
        VBox fileBox = new VBox(6,new Label("File Table:"), fileTableListView);
        VBox prgBox  = new VBox(6,new Label("Program States:"), programStatesListView);
        VBox symBox  = new VBox(6,new Label("Symbol Table:"), symTableView);
        VBox exeBox  = new VBox(6,new Label("Execution Stack:"), exeStackListView);

        //left column
        VBox left = new VBox(12,
                no_programstates,
                heapBox,
                outBox,
                fileBox,
                prgBox,
                runButton
        );
        left.setPrefWidth(360);

        //right column
        VBox right = new VBox(12,
                symBox,
                exeBox
        );

        // Make Execution Stack bigger than Symbol Table (looks nicer)
        symTableView.setPrefHeight(220);
        exeStackListView.setPrefHeight(340);

        //main
        HBox main = new HBox(18, left, right);
        HBox.setHgrow(right, Priority.ALWAYS);

        //root
        VBox root = new VBox(12, main);
        root.setPadding(new Insets(10));
        root.setStyle("""
        -fx-accent: pink;
        -fx-focus-color: pink;
    """);
        stage.setTitle("Program Execution");
        stage.setScene(new Scene(root, 900, 600));
        stage.show();
    }

    public void reload(){
        List<ProgramState> programs = controller.getRepository().getProgramList();

        //no of program states
        this.no_programstates.setText("Number of Program States: " + controller.numberOfPrograms());
        if (!programs.isEmpty()) {
            //heap
            MyHeapI heap = programs.get(0).getHeap();
            var heapRows = heap.getHeap().entrySet().stream()
                    .map(e -> new AbstractMap.SimpleEntry<>(e.getKey(), e.getValue()))
                    .toList();
            heapTableView.getItems().setAll(heapRows);
            heapTableView.refresh();

            //out
            MyListI<Value> out= programs.get(0).getOut();
            this.outListView.setItems(observableArrayList(out.getList()));

            //file table
            MyDictionaryI<String, BufferedReader> fileTable= programs.get(0).getFileTable();
            this.fileTableListView.setItems(observableArrayList(fileTable.keySet()));

            //programs ids
            ObservableList<Integer> programIds = observableArrayList();
            for (ProgramState ps : programs) {
                programIds.add(ps.getId());
            }
            this.programStatesListView.setItems(programIds);
        }
    }

    private void showProgramStateDetails(int id) {
        List<ProgramState> programs = controller.getRepository().getProgramList();

        ProgramState selected = null;
        for (ProgramState ps : programs) {
            if (ps.getId() == id) { selected = ps; break; }
        }

        // sym table
        var symRows = selected.getTable().getDictionary().entrySet().stream()
                .map(e -> new AbstractMap.SimpleEntry<>(e.getKey(), e.getValue()))
                .toList();
        symTableView.getItems().setAll(symRows);
        symTableView.refresh();

        // exe stack
        exeStackListView.getItems().setAll(
                selected.getStack().toString()
                        .replace("[", "")
                        .replace("]", "")
                        .split(";")
        );
        exeStackListView.refresh();
    }


    public void handleSelect(Stage stage){
        try {
            if(controller.numberOfPrograms()==0){
                showError("No more program states left!");
                return;
            }
            this.controller.oneStepAllProgramsGui(this.controller.getRepository().getProgramList());
            this.reload();
            List<ProgramState> programs = controller.removeCompletedPrograms(controller.getRepository().getProgramList());
            this.controller.getRepository().setProgramList(programs);
            if (programs.size()==0){
                this.no_programstates.setText("Number of Program States: " + controller.numberOfPrograms());
                ObservableList<Integer> programIds = observableArrayList();
                for (ProgramState ps : programs) {
                    programIds.add(ps.getId());
                }
                this.programStatesListView.setItems(programIds);
            }
            else {
                this.reload();
            }
        } catch (Exception e) {
            showError(e.getMessage());
        }
    }

    private void showError(String msg) {
        Alert alert = new Alert(Alert.AlertType.ERROR, msg, ButtonType.OK);
        alert.showAndWait();
    }
}
