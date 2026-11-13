package domain;

public class Ingredient {
    private int id;
    private String name;
    private String unit;
    private int caloriesPer100g;

    public Ingredient(int id, String name, String unit, int caloriesPer100g) {
        this.id = id;
        this.name = name;
        this.unit = unit;
        this.caloriesPer100g = caloriesPer100g;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getUnit() {
        return unit;
    }

    public int getCaloriesPer100g() {
        return caloriesPer100g;
    }
}
