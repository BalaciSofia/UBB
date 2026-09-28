package config;

import service.GameService;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpSessionEvent;
import javax.servlet.http.HttpSessionListener;

public class SessionListener implements HttpSessionListener {
    @Override
    public void sessionCreated(HttpSessionEvent event) {
    }

    @Override
    public void sessionDestroyed(HttpSessionEvent event) {
        Object username = event.getSession().getAttribute("username");
        if (username == null) {
            return;
        }

        ServletContext context = event.getSession().getServletContext();
        GameService gameService = (GameService) context.getAttribute("gameService");
        if (gameService != null) {
            gameService.leave(username.toString());
        }
    }
}
