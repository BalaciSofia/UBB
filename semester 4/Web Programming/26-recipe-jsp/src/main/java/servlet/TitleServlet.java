package servlet;

import domain.Recipe;
import repository.DbManager;
import repository.MainRepository;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;

public class TitleServlet extends HttpServlet {

    private MainRepository mainRepository;

    @Override
    public void init() {
        DbManager dbManager = new DbManager();
        this.mainRepository = new MainRepository(dbManager);
    }

    @Override
    public void doGet(HttpServletRequest req, HttpServletResponse resp) throws
            ServletException, IOException {
        req.getRequestDispatcher("/title.jsp").forward(req, resp);
    }

    @Override
    public void doPost(HttpServletRequest req, HttpServletResponse resp) throws
            ServletException, IOException {
        String title = req.getParameter("title");
        int id = (Integer) req.getSession().getAttribute("userID");
        try {
            Recipe recipe=this.mainRepository.saveRecipe(id, title);
            req.getSession().setAttribute("recipeID", recipe.getId());
            req.getSession().setAttribute("recipeTitle", title);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        resp.sendRedirect(req.getContextPath() + "/build");
    }
}

