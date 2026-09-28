package servlet;

import service.AuthService;
import service.GameService;

import javax.servlet.http.HttpServlet;

public abstract class   BaseServlet extends HttpServlet {
    protected AuthService authService() {
        return (AuthService) getServletContext().getAttribute("authService");
    }

    protected GameService gameService() {
        return (GameService) getServletContext().getAttribute("gameService");
    }
}
