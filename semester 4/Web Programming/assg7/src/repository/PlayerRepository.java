package repository;

import domain.Player;
import domain.Symbol;
import repository.jdbc.DatabaseManager;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class PlayerRepository {
    private final DatabaseManager databaseManager;

    public PlayerRepository(DatabaseManager databaseManager) {
        this.databaseManager = databaseManager;
    }

    public List<Player> findAllActive() {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement statement = connection.prepareStatement(
                     "SELECT id, username, symbol FROM players ORDER BY id")) {
            try (ResultSet resultSet = statement.executeQuery()) {
                List<Player> players = new ArrayList<>();
                while (resultSet.next()) {
                    players.add(mapPlayer(resultSet));
                }
                return players;
            }
        } catch (SQLException e) {
            throw new RuntimeException("Could not load active players.", e);
        }
    }

    public Player findActiveByUsername(String username) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement statement = connection.prepareStatement(
                     "SELECT id, username, symbol FROM players WHERE username = ?")) {
            statement.setString(1, username);
            try (ResultSet resultSet = statement.executeQuery()) {
                return resultSet.next() ? mapPlayer(resultSet) : null;
            }
        } catch (SQLException e) {
            throw new RuntimeException("Could not find active player.", e);
        }
    }

    public boolean existsBySymbol(Symbol symbol) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement statement = connection.prepareStatement(
                     "SELECT COUNT(*) FROM players WHERE symbol = ?")) {
            statement.setString(1, symbol.name());
            try (ResultSet resultSet = statement.executeQuery()) {
                resultSet.next();
                return resultSet.getInt(1) > 0;
            }
        } catch (SQLException e) {
            throw new RuntimeException("Could not check player symbol.", e);
        }
    }

    public Player add(String username, Symbol symbol) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement statement = connection.prepareStatement(
                     "INSERT INTO players(username, symbol) VALUES (?, ?)",
                     Statement.RETURN_GENERATED_KEYS)) {
            statement.setString(1, username);
            statement.setString(2, symbol.name());
            statement.executeUpdate();
            try (ResultSet keys = statement.getGeneratedKeys()) {
                keys.next();
                return new Player(keys.getInt(1), username, symbol);
            }
        } catch (SQLException e) {
            throw new RuntimeException("Could not add player.", e);
        }
    }

    public void removeByUsername(String username) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement statement = connection.prepareStatement(
                     "DELETE FROM players WHERE username = ?")) {
            statement.setString(1, username);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Could not remove player.", e);
        }
    }

    private Player mapPlayer(ResultSet resultSet) throws SQLException {
        return new Player(
                resultSet.getInt("id"),
                resultSet.getString("username"),
                Symbol.valueOf(resultSet.getString("symbol")));
    }
}
