package repository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;

public class TaskLogRepo {
    private DbManager dbManager;

    public TaskLogRepo(DbManager dbManager) {
        this.dbManager = dbManager;
    }

    public void logRecord(int taskId, int userId, String oldStatus, String newStatus) {
        String sql = "INSERT INTO taskLog " +
                "(taskID, userID,oldStatus,newStatus, timestamp) VALUES (?, ?, ?, ?, NOW())";
        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, taskId);
            stmt.setInt(2, userId);
            stmt.setString(3, oldStatus);
            stmt.setString(4, newStatus);
            stmt.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException("Could not update task status", e);
        }
    }
    public Map<Integer,String> getLastUpdatedBy(){
        String sql =
                "SELECT tl.taskID, u.username " +
                        "FROM taskLog tl " +
                        "JOIN user u ON tl.userID = u.id " +
                        "JOIN ( " +
                        "    SELECT taskID, MAX(timestamp) AS maxTimestamp " +
                        "    FROM taskLog " +
                        "    GROUP BY taskID " +
                        ") latest " +
                        "ON tl.taskID = latest.taskID " +
                        "AND tl.timestamp = latest.maxTimestamp";
        Map<Integer,String> lastUpdatedBy = new HashMap<>();
        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                int taskId = rs.getInt("taskID");
                String username = rs.getString("username");
                lastUpdatedBy.put(taskId, username);
            }
            return lastUpdatedBy;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
