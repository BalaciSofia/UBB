package servlet;

import domain.User;
import repository.DbManager;
import repository.MainRepository;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class AuthServlet extends HttpServlet {
    private MainRepository mainRepository;

    @Override
    public void init() {
        DbManager dbManager = new DbManager();
        this.mainRepository = new MainRepository(dbManager);
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
        String password = req.getParameter("password");
        try{
            User user = mainRepository.authenticate(username,password);
            if (user != null){
                HttpSession session = req.getSession();
                session.setAttribute("username", username);
                session.setAttribute("userId", user.getId());
                resp.sendRedirect(req.getContextPath() + "/home");
            }
            else{
                req.setAttribute("error", "Invalid username");
                req.getRequestDispatcher("/login").forward(req, resp);
            }
        }catch (Exception e){
            req.setAttribute("error", e.getMessage());
            req.getRequestDispatcher("/login").forward(req, resp);
        }

    }
}
