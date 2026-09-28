package servlet;

import domain.User;
import repository.TaskLogRepo;
import repository.TaskRepo;
import service.AuthService;
import repository.UserRepo;
import repository.DbManager;
import service.TaskLogService;
import service.TaskService;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class HomeServlet extends HttpServlet {
    private TaskService taskService;
    private TaskLogService taskLogService;

    @Override
    public void init() {
        DbManager dbManager = new DbManager();
        TaskRepo taskRepo = new TaskRepo(dbManager);
        this.taskService = new TaskService(taskRepo);
        TaskLogRepo taskLogRepo = new TaskLogRepo(dbManager);
        this.taskLogService = new TaskLogService(taskLogRepo);
    }

    @Override
    public void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession(false);
        if (session == null || session.getAttribute("username") == null) {
            resp.sendRedirect(req.getContextPath() + "/login");
            return;
        }
        req.setAttribute("todoTasks", taskService.getToDoTasks());
        req.setAttribute("inProgressTasks", taskService.getInProgressTasks());
        req.setAttribute("doneTasks", taskService.getDoneTasks());
        req.setAttribute("lastUpdatedBy", taskLogService.getLastUpdatedBy());

        req.getRequestDispatcher("/home.jsp").forward(req, resp);
    }

    @Override
    public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        HttpSession session = req.getSession(false);
        if (session == null || session.getAttribute("username") == null) {
            resp.sendRedirect(req.getContextPath() + "/login");
            return;
        }

        int userId = (Integer) session.getAttribute("userId");
        int taskId = Integer.parseInt(req.getParameter("taskId"));
        String oldStatus = (String)req.getParameter("oldStatus");
        String newStatus = (String)req.getParameter("status");
        if (!oldStatus.equals(newStatus)) {
            taskService.updateTaskStatus(taskId, newStatus);
            taskLogService.logRecord(taskId, userId, oldStatus, newStatus);

            int moveCount = (Integer) session.getAttribute("moveCount");
            session.setAttribute("moveCount", moveCount + 1);
        }
        resp.sendRedirect(req.getContextPath() + "/home");
    }
}
