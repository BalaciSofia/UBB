package service;

import domain.Task;
import repository.TaskRepo;

import java.util.List;

public class TaskService {
    private TaskRepo taskRepo;

    public TaskService(TaskRepo taskRepo) {
        this.taskRepo = taskRepo;
    }

    public void updateTaskStatus(int taskId,String status) {
        taskRepo.updateTaskStatus(taskId,status);
    }

    public List<Task> getToDoTasks() {
        return taskRepo.getToDoTasks();
    }

    public List<Task> getInProgressTasks() {
        return taskRepo.getInProgressTasks();
    }

    public List<Task> getDoneTasks() {
        return taskRepo.getDoneTasks();
    }
}
