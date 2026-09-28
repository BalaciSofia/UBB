package domain;

import java.sql.Timestamp;

public class Task {
    private int id;
    private String title;
    private int assignedToUserId;
    private Timestamp lastUpdated;
    private TaskStatus status;

    public Task(int id, String title, int assignedToUserId, Timestamp lastUpdated, TaskStatus status) {
        this.id = id;
        this.title = title;
        this.assignedToUserId = assignedToUserId;
        this.lastUpdated = lastUpdated;
        this.status = status;
    }

    public int getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public int getAssignedToUserId() {
        return assignedToUserId;
    }

    public Timestamp getLastUpdated() {
        return lastUpdated;
    }

    public TaskStatus getStatus() {
        return status;
    }

}
