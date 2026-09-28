package repository;

import domain.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MainRepository {
    private DbManager dbManager;

    public MainRepository(DbManager dbManager) {
        this.dbManager = dbManager;
    }

    public User authenticate(String username, String password) throws SQLException{
        String sql = "SELECT * FROM users WHERE username = ?";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setString(1, username);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    if(rs.getString("password").equals(password)) {
                        return new User(
                                rs.getInt("id"),
                                rs.getString("username"),
                                rs.getString("password")
                        );
                    }
                }

                return null;
            }
        }
    }
}
