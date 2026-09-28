package domain;

public class RecipeSteps {
    private int id;
    private int recipeID;
    private int stepNumber;
    private String description;
    private String ingredientIDs;

    public RecipeSteps(int id, int recipeID, int stepNumber, String description, String ingredientIDs) {
        this.id = id;
        this.recipeID = recipeID;
        this.stepNumber = stepNumber;
        this.description = description;
        this.ingredientIDs = ingredientIDs;
    }

    public int getId() {
        return id;
    }

    public int getRecipeID() {
        return recipeID;
    }

    public int getStepNumber() {
        return stepNumber;
    }

    public String getDescription() {
        return description;
    }

    public String getIngredientIDs() {
        return ingredientIDs;
    }

}
