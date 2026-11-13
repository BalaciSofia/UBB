package repository;

import domain.Ingredient;
import domain.Recipe;
import domain.RecipeSteps;
import domain.User;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class MainRepository {
    private DbManager dbManager;

    public MainRepository(DbManager dbManager) {
        this.dbManager = dbManager;
    }

    public User authenticate(String username) throws SQLException{
        String sql = "SELECT * FROM users WHERE username = ?";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setString(1, username);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {

                        return new User(
                                rs.getInt("id"),
                                rs.getString("username")
                        );
                }
                return null;
            }
        }
    }

    public Recipe saveRecipe(int userID,String title) throws SQLException {
        String sql = "INSERT INTO recipes (userID, title, totalCalories) VALUES (?, ?, 0)";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            title = title+"-ND";
            stmt.setInt(1, userID);
            stmt.setString(2, title);
            stmt.executeUpdate();
            ResultSet rs = stmt.getGeneratedKeys();
            if (rs.next()) {
                Recipe r = new Recipe(rs.getInt(1),title,userID, 0);
                return r;
            } else {
                throw new SQLException("Creating recipe failed, no ID obtained.");
            }
        }
    }

    public List<Ingredient> getIngredients() throws SQLException {
        String sql = "SELECT * FROM ingredient";
        List<Ingredient> ingredients = new ArrayList<>();

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                Ingredient ingredient = new Ingredient(
                        rs.getInt("id"),
                        rs.getString("name"),
                        rs.getString("unit"),
                        rs.getInt("caloriesPer100g")
                );
                ingredients.add(ingredient);
            }
        }
        return ingredients;
    }

    public List<RecipeSteps> getRecipeSteps(int recipeId) throws SQLException {
        String sql = "SELECT * FROM recipesteps WHERE recipeID = ? order by stepNumber";
        List<RecipeSteps> steps = new ArrayList<>();

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, recipeId);
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                RecipeSteps step = new RecipeSteps(
                        rs.getInt("id"),
                        rs.getInt("recipeID"),
                        rs.getInt("stepNumber"),
                        rs.getString("description"),
                        rs.getString("ingredientIDs")
                );
                steps.add(step);
            }
        }
        return steps;
    }

    public int getLastStepNumber(int recipeId) throws SQLException {
        String sql = "SELECT MAX(stepNumber) AS maxStep FROM recipesteps WHERE recipeID = ?";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, recipeId);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt("maxStep");
            } else {
                return 0;
            }
        }
    }

    public void saveRecipeStep(int recipeId, String description, String ingredientIds) throws SQLException {
        String sql = "INSERT INTO recipesteps (recipeID, stepNumber, description, ingredientIDs) VALUES (?, ?, ?, ?)";
        int stepNumber = getLastStepNumber(recipeId) + 1;
        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, recipeId);
            stmt.setInt(2, stepNumber);
            stmt.setString(3, description);
            stmt.setString(4, ingredientIds);
            stmt.executeUpdate();
        }
    }

    public void removeRecipeStep(int stepID) throws SQLException {
        String sql1 = "SELECT * FROM recipesteps WHERE id = ?";
        String sql2 = "DELETE FROM recipesteps WHERE id = ?";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt1 = conn.prepareStatement(sql1)) {
                stmt1.setInt(1, stepID);

                ResultSet rs = stmt1.executeQuery();
                rs.next();
                RecipeSteps step = new RecipeSteps(
                    rs.getInt("id"),
                    rs.getInt("recipeID"),
                    rs.getInt("stepNumber"),
                    rs.getString("description"),
                    rs.getString("ingredientIDs")
                );
            PreparedStatement stmt2 = conn.prepareStatement(sql2);
            stmt2.setInt(1, stepID);
            stmt2.executeUpdate();

            String sql3 = "UPDATE recipesteps SET stepNumber = stepNumber - 1 WHERE recipeID = ? AND stepNumber > ?";
            PreparedStatement stmt3 = conn.prepareStatement(sql3);
            stmt3.setInt(1, step.getRecipeID());
            stmt3.setInt(2, step.getStepNumber());
            stmt3.executeUpdate();
        }
    }

    public int computeTotalCalories(int recipeId) throws SQLException {
        String sql = "SELECT SUM(i.caloriesPer100g) AS totalCalories " +
                     "FROM recipesteps rs " +
                     "JOIN ingredient i ON FIND_IN_SET(i.id, rs.ingredientIDs) > 0 " +
                     "WHERE rs.recipeID = ?";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, recipeId);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt("totalCalories");
            } else {
                return 0;
            }
        }
    }

    public void confirmRecipe(int recipeId,int totalCalories, String title) throws SQLException {
        String sql1 = "UPDATE recipes SET totalCalories = ? WHERE id = ?";
        String sql2 = "UPDATE recipes SET title = ? WHERE id = ?";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt1 = conn.prepareStatement(sql1)) {

            stmt1.setInt(1, totalCalories);
            stmt1.setInt(2, recipeId);
            stmt1.executeUpdate();
            PreparedStatement stmt2 = conn.prepareStatement(sql2);{
                stmt2.setString(1, title);
                stmt2.setInt(2, recipeId);
                stmt2.executeUpdate();
            }
        }
    }

    public void discardRecipe(int recipeId) throws SQLException {
        String sql1 = "DELETE FROM recipes WHERE id = ?";
        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt1 = conn.prepareStatement(sql1)) {
            stmt1.setInt(1, recipeId);
            stmt1.executeUpdate();
        }
    }

    public Recipe hasUnfinishedRecipe(int userId) throws SQLException {
        String sql = "SELECT * FROM recipes WHERE userID = ? AND title LIKE '%-ND'";
        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, userId);
            ResultSet rs = stmt.executeQuery();
            if(rs.next()){
                return new Recipe(
                        rs.getInt("id"),
                        rs.getString("title"),
                        rs.getInt("userID"),
                        rs.getInt("totalCalories")
                );
            }
            else{
                return null;
            }
        }
    }

    public List<Recipe> getUserRecipes(int userId) throws SQLException {
        String sql = "SELECT * FROM recipes WHERE userID = ? AND title NOT LIKE '%-ND'";
        List<Recipe> recipes = new ArrayList<>();
        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, userId);
            ResultSet rs = stmt.executeQuery();
            while(rs.next()){
                Recipe recipe = new Recipe(
                        rs.getInt("id"),
                        rs.getString("title"),
                        rs.getInt("userID"),
                        rs.getInt("totalCalories")
                );
                recipes.add(recipe);
            }
            return recipes;
        }
    }

    public String foodGroupCheck(int recipeId) throws SQLException {
        String sql =
                "SELECT SUBSTRING_INDEX(i.name, '-', 1) AS foodGroup, " +
                        "COUNT(*) AS groupCount, " +
                        "(SELECT COUNT(*) " +
                        " FROM recipesteps rs2 " +
                        " JOIN ingredient i2 ON FIND_IN_SET(i2.id, rs2.ingredientIDs) > 0 " +
                        " WHERE rs2.recipeID = ?) AS totalCount " +
                        "FROM recipesteps rs " +
                        "JOIN ingredient i ON FIND_IN_SET(i.id, rs.ingredientIDs) > 0 " +
                        "WHERE rs.recipeID = ? " +
                        "GROUP BY SUBSTRING_INDEX(i.name, '-', 1) " +
                        "HAVING groupCount > totalCount * 0.6";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, recipeId);
            stmt.setInt(2, recipeId);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return "This recipe is heavily " + rs.getString("foodGroup") + "-based";
                }
            }
        }

        return null;
    }
}
