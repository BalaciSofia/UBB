package View;
import Controller.TreeController;
import Model.*;

import java.util.Scanner;

public class TreeView {
    private  TreeController controller;

    public TreeView(TreeController controller) {
        this.controller = controller;
    }

    private int readInt(String prompt){
        Scanner input = new Scanner(System.in);
        while(true){
            System.out.print(prompt);
            String line= input.nextLine().trim();
            try{
                int value = Integer.parseInt(line);
                return value;
            }catch(NumberFormatException e){
                System.out.println("Please enter a number");
            }
        }
    }
    public void displayOld(){
        Tree[] trees=this.controller.OldTrees();
        for(Tree t:trees){
            System.out.println(t.toString());
        }
    }

    public void display(){
        Tree[] trees=this.controller.getTrees();
        for(Tree t:trees){
            System.out.println(t.toString());
        }
    }
    public void start(){
        int choice;
        System.out.println("Welcome!");
        System.out.println("Type 1 for hardcode");
        System.out.println("Type 2 to use application");
        choice = readInt(">>>");
        switch(choice){
            case 1:
                this.hardcode();
                break;
                case 2:
                    this.app();
                    break;
                    default:
                        System.out.println("Invalid choice");

        }
    }

    public void hardcode(){
        this.controller.populate();
        System.out.println("=========All trees=========");
        this.display();

        System.out.println("=====Trees older than 2=====");
        this.displayOld();
    }

    public void printMenu(){
        System.out.println("MENU");
        System.out.println("-------------------------");
        System.out.println("|1. Add New Tree        |");
        System.out.println("|2. Display All Trees   |");
        System.out.println("|3. Delete Tree         |");
        System.out.println("|4. Display Old Trees   |");
        System.out.println("|5. Exit                |");
        System.out.println("-------------------------");
    }

    public void addTreeUi(){
        //type of tree
        //age
        Scanner input = new Scanner(System.in);
        int age=readInt("Enter tree age>>>");
        System.out.print("Select tree:a-apple tree,c-cherry tree,p-pear tree>>>");
        String choice = input.nextLine();
        switch(choice){
            case "a":
                this.controller.addAppleTree(age);
                break;
                case "c":
                    this.controller.addCherryTree(age);
                    break;
                    case "p":
                        this.controller.addPearTree(age);
                        break;
                        default:
                            System.out.println("there is no such tree(a/c/p)");
        }
    }

    public void deleteTreeUi(){
        Scanner input = new Scanner(System.in);
        int age=readInt("Enter tree age>>>");
        System.out.print("Select tree:a-apple tree,c-cherry tree,p-pear tree>>>");
        String choice = input.nextLine();
        try {
            switch(choice){
                case "a": this.controller.deleteTree(new AppleTree(age)); break;
                case "c": this.controller.deleteTree(new CherryTree(age)); break;
                case "p": this.controller.deleteTree(new PearTree(age)); break;
                default:System.out.println("there is no such tree(a/c/p)");

            }
            System.out.println("Deleted successfully.");
        } catch (TreeNotFoundEx e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public void app(){
        this.controller.populate();
        int choice;
        Scanner input = new Scanner(System.in);
        while (true){
            this.printMenu();
            choice = readInt(">>>");
            switch(choice){
                case 1:
                    this.addTreeUi();
                    break;
                case 2:
                    this.display();
                    break;
                case 3:
                    this.deleteTreeUi();
                    break;
                    case 4:
                        this.displayOld();
                        break;
                case 5:
                    System.exit(0);
                    default:
                        System.out.println("Invalid choice");
            }
        }
    }
}
