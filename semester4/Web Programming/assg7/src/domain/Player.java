package domain;

public class Player extends User {
    private final Symbol symbol;

    public Player(int id, String username, Symbol symbol) {
        super(id, username, "");
        this.symbol = symbol;
    }

    public Symbol getSymbol() {
        return symbol;
    }
}
