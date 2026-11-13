package servlet;

import domain.User;
import service.AuthService;
import repository.UserRepo;
import repository.DbManager;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class LoginServlet extends HttpServlet {
    protected AuthService authService;

    @Override
    public void init() {
        DbManager dbManager = new DbManager();
        UserRepo userRepo = new UserRepo(dbManager);
        this.authService = new AuthService(userRepo);
    }

    @Override
    public void doGet(HttpServletRequest req, HttpServletResponse resp) throws
            ServletException, IOException {
        req.getRequestDispatcher("/login.jsp").forward(req, resp);
    }

    @Override
    public void doPost(HttpServletRequest req, HttpServletResponse resp) throws
            ServletException, IOException {
        String username = req.getParameter("username");
        try{
            User user = authService.authenticate(username);
            if (user != null){
                HttpSession session = req.getSession();
                session.setAttribute("username", username);
                session.setAttribute("userId", user.getId());
                session.setAttribute("moveCount", 0);

                resp.sendRedirect(req.getContextPath() + "/home");
            }
            else{
                req.setAttribute("error", "Invalid username");
                req.getRequestDispatcher("/login.jsp").forward(req, resp);
                return;
            }

        }catch (Exception e){
            req.setAttribute("error", e.getMessage());
            req.getRequestDispatcher("/login.jsp").forward(req, resp);
            return;
        }

    }

}
