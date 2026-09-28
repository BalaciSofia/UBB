package repository;

import domain.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserRepo {
    private DbManager dbManager;

    public UserRepo(DbManager dbManager) {
        this.dbManager = dbManager;
    }

    public User findByUsername(String username) throws SQLException {
        String sql = "SELECT id, username FROM user WHERE username = ?";

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
}
