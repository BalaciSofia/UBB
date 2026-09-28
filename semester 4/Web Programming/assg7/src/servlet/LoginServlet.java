package servlet;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class LoginServlet extends BaseServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession(false);
        if (session != null && session.getAttribute("username") != null) {
            resp.sendRedirect(req.getContextPath() + "/game");
            return;
        }
        req.getRequestDispatcher("/WEB-INF/jsp/login.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = trim(req.getParameter("username"));
        String password = trim(req.getParameter("password"));

        if (username.length() < 3 || !username.matches("[A-Za-z0-9_]+")) {
            showError(req, resp, "Username must have at least 3 letters, digits, or underscores.");
            return;
        }
        if (password.length() < 3) {
            showError(req, resp, "Password must have at least 3 characters.");
            return;
        }
        if (!authService().authenticate(username, password)) {
            showError(req, resp, "Invalid username or password");
            return;
        }

        req.getSession(true).setAttribute("username", username);
        resp.sendRedirect(req.getContextPath() + "/game");
    }

    private void showError(HttpServletRequest req, HttpServletResponse resp, String error)
            throws ServletException, IOException {
        req.setAttribute("error", error);
        req.getRequestDispatcher("/WEB-INF/jsp/login.jsp").forward(req, resp);
    }

    private String trim(String value) {
        return value == null ? "" : value.trim();
    }
}
