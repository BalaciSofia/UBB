package service;

import repository.TaskLogRepo;

import java.util.Map;

public class TaskLogService {
    private TaskLogRepo taskLogRepo;

    public TaskLogService(TaskLogRepo taskLogRepo) {
        this.taskLogRepo = taskLogRepo;
    }

    public void logRecord(int taskId, int userId,  String oldStatus, String newStatus) {
        taskLogRepo.logRecord(taskId, userId, oldStatus, newStatus);
    }

    public Map<Integer,String> getLastUpdatedBy() {
        return taskLogRepo.getLastUpdatedBy();
    }
}
