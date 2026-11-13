package domain;

import java.util.List;

public class GameState {
    private final Game game;
    private final List<Player> players;

    public GameState(Game game, List<Player> players) {
        this.game = game;
        this.players = players;
    }

    public Game getGame() {
        return game;
    }

    public List<Player> getPlayers() {
        return players;
    }
}
