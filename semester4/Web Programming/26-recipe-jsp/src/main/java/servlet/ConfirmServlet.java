package servlet;

import repository.DbManager;
import repository.MainRepository;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;

public class ConfirmServlet extends HttpServlet {
    private MainRepository mainRepository;

    @Override
    public void init() {
        DbManager dbManager = new DbManager();
        this.mainRepository = new MainRepository(dbManager);
    }

    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            req.setAttribute("totalCalories", mainRepository.computeTotalCalories((Integer) req.getSession().getAttribute("recipeID")));
            req.setAttribute("recipesteps", mainRepository.getRecipeSteps((Integer) req.getSession().getAttribute("recipeID")));
            req.setAttribute("recipes", mainRepository.getUserRecipes((Integer) req.getSession().getAttribute("userID")));
            String foodGroupMessage = mainRepository.foodGroupCheck((Integer) req.getSession().getAttribute("recipeID"));
            req.setAttribute("foodGroupMessage", foodGroupMessage);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        req.getRequestDispatcher("/confirm.jsp").forward(req, resp);
    }

    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String action = req.getParameter("action");

        if("confirm".equals(action)) {
            int recipeID = (Integer) req.getSession().getAttribute("recipeID");
            try {
                int totalCalories = mainRepository.computeTotalCalories(recipeID);
                String title = (String) req.getSession().getAttribute("recipeTitle");
                mainRepository.confirmRecipe(recipeID,totalCalories,title);
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
            resp.sendRedirect(req.getContextPath() + "/login");
        } else if ("discard".equals(action)) {
            int recipeID = (Integer) req.getSession().getAttribute("recipeID");
            try {
                mainRepository.discardRecipe(recipeID);
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
            resp.sendRedirect(req.getContextPath() + "/login");
        }if("delete".equals(action)){
            try{
                mainRepository.discardRecipe(Integer.parseInt(req.getParameter("recipeID")));
            }catch (SQLException e){
                throw new RuntimeException(e);
            }
            resp.sendRedirect(req.getContextPath() + "/confirm");
        }
    }
}
