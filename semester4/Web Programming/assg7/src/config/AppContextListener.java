package config;

import repository.GameRepository;
import repository.PlayerRepository;
import repository.UserRepository;
import repository.jdbc.DatabaseManager;
import service.AuthService;
import service.GameService;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;

public class AppContextListener implements ServletContextListener {
    @Override
    public void contextInitialized(ServletContextEvent event) {
        ServletContext context = event.getServletContext();

        String url = getInitParameter(context, "dbUrl", "jdbc:h2:file:./database/assg7;MODE=MySQL;DATABASE_TO_UPPER=false");
        String username = getInitParameter(context, "dbUser", "sa");
        String password = getInitParameter(context, "dbPassword", "");

        DatabaseManager databaseManager = new DatabaseManager(url, username, password);
        databaseManager.initialize();

        UserRepository userRepository = new UserRepository(databaseManager);
        PlayerRepository playerRepository = new PlayerRepository(databaseManager);
        GameRepository gameRepository = new GameRepository(databaseManager);

        context.setAttribute("authService", new AuthService(userRepository));
        context.setAttribute("gameService", new GameService(gameRepository, playerRepository));
    }

    @Override
    public void contextDestroyed(ServletContextEvent event) {
    }

    private String getInitParameter(ServletContext context, String name, String fallback) {
        String value = context.getInitParameter(name);
        return value == null || value.trim().isEmpty() ? fallback : value.trim();
    }
}
