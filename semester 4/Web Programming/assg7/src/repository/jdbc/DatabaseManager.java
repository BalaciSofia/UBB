package repository.jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;

public class DatabaseManager {
    private final String url;
    private final String username;
    private final String password;

    public DatabaseManager(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    public Connection getConnection() {
        try {
            return DriverManager.getConnection(url, username, password);
        } catch (SQLException e) {
            throw new RuntimeException("Could not open database connection.", e);
        }
    }

    public void initialize() {
        try (Connection connection = getConnection(); Statement statement = connection.createStatement()) {
            statement.executeUpdate("CREATE TABLE IF NOT EXISTS users (" +
                    "id INT AUTO_INCREMENT PRIMARY KEY," +
                    "username VARCHAR(50) NOT NULL UNIQUE," +
                    "password VARCHAR(100) NOT NULL)");
            statement.executeUpdate("CREATE TABLE IF NOT EXISTS players (" +
                    "id INT AUTO_INCREMENT PRIMARY KEY," +
                    "username VARCHAR(50) NOT NULL UNIQUE," +
                    "symbol VARCHAR(1) NOT NULL UNIQUE)");
            statement.executeUpdate("CREATE TABLE IF NOT EXISTS game_state (" +
                    "id INT PRIMARY KEY," +
                    "board VARCHAR(9) NOT NULL," +
                    "current_turn VARCHAR(1) NOT NULL," +
                    "status VARCHAR(20) NOT NULL," +
                    "winner VARCHAR(1) NULL)");
            clearUsers(connection);
            seedUsers(connection);
            seedGame(connection);
            clearActiveGame(connection);
        } catch (SQLException e) {
            throw new RuntimeException("Could not initialize database.", e);
        }
    }

    private void seedUsers(Connection connection) throws SQLException {
        insertUser(connection, "ana", "ana");
        insertUser(connection, "alex", "alex");
        insertUser(connection, "mihai", "mihai");
    }

    private void clearUsers(Connection connection) throws SQLException {
        try (Statement statement = connection.createStatement()) {
            statement.executeUpdate("DELETE FROM users");
        }
    }

    private void insertUser(Connection connection, String username, String password) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(
                "INSERT INTO users(username, password) VALUES (?, ?)")) {
            statement.setString(1, username);
            statement.setString(2, password);
            statement.executeUpdate();
        }
    }

    private void seedGame(Connection connection) throws SQLException {
        try (PreparedStatement statement = connection.prepareStatement(
                "SELECT id FROM game_state WHERE id = 1")) {
            if (statement.executeQuery().next()) {
                return;
            }
        }

        try (PreparedStatement statement = connection.prepareStatement(
                "INSERT INTO game_state(id, board, current_turn, status, winner) VALUES (1, '---------', 'X', 'WAITING', NULL)")) {
            statement.executeUpdate();
        }
    }

    private void clearActiveGame(Connection connection) throws SQLException {
        try (Statement statement = connection.createStatement()) {
            statement.executeUpdate("DELETE FROM players");
            statement.executeUpdate("UPDATE game_state SET board = '---------', current_turn = 'X', status = 'WAITING', winner = NULL WHERE id = 1");
        }
    }
}
