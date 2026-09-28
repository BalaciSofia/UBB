package service;

import domain.Game;
import domain.GameState;
import domain.GameStatus;
import domain.Player;
import domain.Symbol;
import repository.GameRepository;
import repository.PlayerRepository;

import java.util.List;

public class GameService {
    private final GameRepository gameRepository;
    private final PlayerRepository playerRepository;
    private String lastMessage;

    public GameService(GameRepository gameRepository, PlayerRepository playerRepository) {
        this.gameRepository = gameRepository;
        this.playerRepository = playerRepository;
    }

    public synchronized Symbol join(String username) {
        lastMessage = null;
        Player existing = playerRepository.findActiveByUsername(username);
        if (existing != null) {
            playerRepository.removeByUsername(username);
        }

        List<Player> players = playerRepository.findAllActive();
        if (players.size() >= 2) {
            lastMessage = "The game already has two connected players. Please try again later.";
            return null;
        }

        Symbol symbol = playerRepository.existsBySymbol(Symbol.X) ? Symbol.O : Symbol.X;
        Player player = playerRepository.add(username, symbol);

        if (playerRepository.findAllActive().size() == 2) {
            Game game = gameRepository.getGame();
            if (game.getStatus() == GameStatus.WAITING) {
                gameRepository.updateState(game.getBoard(), game.getCurrentTurn(), GameStatus.IN_PROGRESS, null);
            }
        }

        return player.getSymbol();
    }

    public synchronized void leave(String username) {
        if (playerRepository.findActiveByUsername(username) == null) {
            return;
        }
        playerRepository.removeByUsername(username);
        resetRound();
    }

    public synchronized GameState getState() {
        List<Player> players = playerRepository.findAllActive();
        Game game = gameRepository.getGame();

        if (players.size() < 2 && game.getStatus() != GameStatus.WAITING) {
            gameRepository.updateState(Game.EMPTY_BOARD, Symbol.X, GameStatus.WAITING, null);
            game = gameRepository.getGame();
        }
        if (players.size() == 2 && game.getStatus() == GameStatus.WAITING) {
            gameRepository.updateState(game.getBoard(), game.getCurrentTurn(), GameStatus.IN_PROGRESS, null);
            game = gameRepository.getGame();
        }

        return new GameState(game, players);
    }

    public synchronized String makeMove(String username, int cell) {
        Player player = playerRepository.findActiveByUsername(username);
        if (player == null) {
            return "You are not connected to the current game.";
        }
        if (cell < 0 || cell > 8) {
            return "Choose a valid square.";
        }

        GameState state = getState();
        Game game = state.getGame();
        if (state.getPlayers().size() < 2) {
            return "Waiting for the second player.";
        }
        if (game.getStatus() != GameStatus.IN_PROGRESS) {
            return "The current game is finished. Start a new round.";
        }
        if (player.getSymbol() != game.getCurrentTurn()) {
            return "It is not your turn.";
        }

        char[] board = game.getBoard().toCharArray();
        if (board[cell] != '-') {
            return "That square is already occupied.";
        }

        board[cell] = player.getSymbol().name().charAt(0);
        Symbol winner = findWinner(board);
        String newBoard = new String(board);
        GameStatus status = winner == null
                ? (newBoard.indexOf('-') == -1 ? GameStatus.DRAW : GameStatus.IN_PROGRESS)
                : GameStatus.FINISHED;

        gameRepository.updateState(newBoard, player.getSymbol().other(), status, winner);
        return null;
    }

    public synchronized void resetRound() {
        GameStatus status = playerRepository.findAllActive().size() == 2 ? GameStatus.IN_PROGRESS : GameStatus.WAITING;
        gameRepository.updateState(Game.EMPTY_BOARD, Symbol.X, status, null);
    }

    public String getLastMessage() {
        return lastMessage;
    }

    private Symbol findWinner(char[] board) {
        int[][] lines = {
                {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
                {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
                {0, 4, 8}, {2, 4, 6}
        };
        for (int[] line : lines) {
            char first = board[line[0]];
            if (first != '-' && first == board[line[1]] && first == board[line[2]]) {
                return Symbol.valueOf(String.valueOf(first));
            }
        }
        return null;
    }

}
