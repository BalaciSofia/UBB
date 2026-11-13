package domain;

import java.sql.Timestamp;


public class TaskLog {
    private int id;
    private int taskId;
    private int userId;
    private TaskStatus oldStatus;
    private TaskStatus newStatus;
    private Timestamp timestamp;

    public TaskLog(int id, int taskId, int userId, TaskStatus oldStatus, TaskStatus newStatus, Timestamp timestamp) {
        this.id = id;
        this.taskId = taskId;
        this.userId = userId;
        this.oldStatus = oldStatus;
        this.newStatus = newStatus;
        this.timestamp = timestamp;
    }

    public int getId() {
        return id;
    }

    public int getTaskId() {
        return taskId;
    }

    public int getUserId() {
        return userId;
    }

    public TaskStatus getOldStatus() {
        return oldStatus;
    }

    public TaskStatus getNewStatus() {
        return newStatus;
    }

    public Timestamp getTimestamp() {
        return timestamp;
    }
}
