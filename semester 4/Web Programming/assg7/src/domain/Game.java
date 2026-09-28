package domain;

public class Game {
    public static final String EMPTY_BOARD = "---------";

    private final int id;
    private final String board;
    private final Symbol currentTurn;
    private final GameStatus status;
    private final Symbol winner;

    public Game(int id, String board, Symbol currentTurn, GameStatus status, Symbol winner) {
        this.id = id;
        this.board = board;
        this.currentTurn = currentTurn;
        this.status = status;
        this.winner = winner;
    }

    public static Game initial() {
        return new Game(1, EMPTY_BOARD, Symbol.X, GameStatus.WAITING, null);
    }

    public String getBoard() {
        return board;
    }

    public Symbol getCurrentTurn() {
        return currentTurn;
    }

    public GameStatus getStatus() {
        return status;
    }

    public Symbol getWinner() {
        return winner;
    }
}
