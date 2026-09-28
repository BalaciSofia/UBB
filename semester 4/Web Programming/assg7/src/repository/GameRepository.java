package repository;

import domain.Game;
import domain.GameStatus;
import domain.Symbol;
import repository.jdbc.DatabaseManager;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class GameRepository {
    private final DatabaseManager databaseManager;

    public GameRepository(DatabaseManager databaseManager) {
        this.databaseManager = databaseManager;
    }

    public Game getGame() {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement statement = connection.prepareStatement(
                     "SELECT id, board, current_turn, status, winner FROM game_state WHERE id = 1")) {
            try (ResultSet resultSet = statement.executeQuery()) {
                if (!resultSet.next()) {
                    return Game.initial();
                }
                String winner = resultSet.getString("winner");
                return new Game(
                        resultSet.getInt("id"),
                        resultSet.getString("board"),
                        Symbol.valueOf(resultSet.getString("current_turn")),
                        GameStatus.valueOf(resultSet.getString("status")),
                        winner == null ? null : Symbol.valueOf(winner));
            }
        } catch (SQLException e) {
            throw new RuntimeException("Could not load game.", e);
        }
    }

    public void updateState(String board, Symbol currentTurn, GameStatus status, Symbol winner) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement statement = connection.prepareStatement(
                     "UPDATE game_state SET board = ?, current_turn = ?, status = ?, winner = ? WHERE id = 1")) {
            statement.setString(1, board);
            statement.setString(2, currentTurn.name());
            statement.setString(3, status.name());
            statement.setString(4, winner == null ? null : winner.name());
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Could not update game.", e);
        }
    }
}
