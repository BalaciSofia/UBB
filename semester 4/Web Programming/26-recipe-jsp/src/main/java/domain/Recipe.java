package domain;

public class Recipe {
    private int id;
    private String title;
    private int userID;
    private int totalCalories;

    public Recipe(int id, String title, int userID, int totalCalories) {
        this.id = id;
        this.title = title;
        this.userID = userID;
        this.totalCalories = totalCalories;
    }

    public int getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public int getUserID() {
        return userID;
    }

    public int getTotalCalories() {
        return totalCalories;
    }
}
