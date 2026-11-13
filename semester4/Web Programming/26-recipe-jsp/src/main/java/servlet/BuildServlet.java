package servlet;

import repository.DbManager;
import repository.MainRepository;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;

public class BuildServlet extends HttpServlet {
    private MainRepository mainRepository;

    @Override
    public void init() {
        DbManager dbManager = new DbManager();
        this.mainRepository = new MainRepository(dbManager);
    }

    @Override
    public void doGet(HttpServletRequest req, HttpServletResponse resp) throws
            ServletException, IOException {
        try {
            req.setAttribute("ingredients", mainRepository.getIngredients());
            req.setAttribute("recipesteps", mainRepository.getRecipeSteps((Integer) req.getSession().getAttribute("recipeID")));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        req.getRequestDispatcher("/build.jsp").forward(req, resp);
    }

    @Override
    public void doPost(HttpServletRequest req, HttpServletResponse resp) throws
            ServletException, IOException {
        String action = req.getParameter("action");

        if ("addStep".equals(action)) {
            String description = req.getParameter("description");
            String[] selectedIngredientIds = req.getParameterValues("ingredientIDs");
            String ingredientIds = "";
            if (selectedIngredientIds != null) {
                ingredientIds = String.join(",", selectedIngredientIds);
            }
            int recipeID = (Integer) req.getSession().getAttribute("recipeID");
            try {
                this.mainRepository.saveRecipeStep(recipeID, description, ingredientIds);
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
            resp.sendRedirect(req.getContextPath() + "/build");
        } else if ("removeStep".equals(action)) {
            // remove step
            int stepID = Integer.parseInt(req.getParameter("stepID"));
            try {
                this.mainRepository.removeRecipeStep(stepID);
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
            resp.sendRedirect(req.getContextPath() + "/build");
        }else if ("finish".equals(action)) {
            resp.sendRedirect(req.getContextPath() + "/confirm");
        }
    }
}
