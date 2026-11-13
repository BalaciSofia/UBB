package repository;

import domain.Task;
import domain.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import static domain.TaskStatus.*;

public class TaskRepo {
    private DbManager dbManager;

    public TaskRepo(DbManager dbManager) {
        this.dbManager = dbManager;
    }

    public boolean updateTaskStatus(int taskId, String status) {
        String sql = "UPDATE task SET status = ?, lastUpdated = NOW() WHERE id = ?";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setString(1, status);
            stmt.setInt(2, taskId);

            int affectedRows = stmt.executeUpdate();
            return affectedRows > 0;
        } catch (SQLException e) {
            throw new RuntimeException("Could not update task status", e);
        }
    }

    public List<Task> getToDoTasks(){
        List<Task> tasks = new ArrayList<>();
        String sql = "SELECT * FROM task WHERE status = 'TODO'";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                Task task = new Task(
                        rs.getInt("id"),
                        rs.getString("title"),
                        rs.getInt("assignedToUserId"),
                        rs.getTimestamp("lastUpdated"),
                        TODO
                );
                tasks.add(task);
            }
            return tasks;
        } catch (SQLException e) {
            throw new RuntimeException("Could not update task status", e);
        }
    }

    public List<Task> getInProgressTasks(){
        List<Task> tasks = new ArrayList<>();
        String sql = "SELECT * FROM task WHERE status = 'IN_PROGRESS'";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                Task task = new Task(
                        rs.getInt("id"),
                        rs.getString("title"),
                        rs.getInt("assignedToUserId"),
                        rs.getTimestamp("lastUpdated"),
                        IN_PROGRESS
                );
                tasks.add(task);
            }
            return tasks;
        } catch (SQLException e) {
            throw new RuntimeException("Could not update task status", e);
        }
    }

    public List<Task> getDoneTasks(){
        List<Task> tasks = new ArrayList<>();
        String sql = "SELECT * FROM task WHERE status = 'DONE'";

        try (Connection conn = dbManager.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                Task task = new Task(
                        rs.getInt("id"),
                        rs.getString("title"),
                        rs.getInt("assignedToUserId"),
                        rs.getTimestamp("lastUpdated"),
                        DONE
                );
                tasks.add(task);
            }
            return tasks;
        } catch (SQLException e) {
            throw new RuntimeException("Could not update task status", e);
        }
    }
}
