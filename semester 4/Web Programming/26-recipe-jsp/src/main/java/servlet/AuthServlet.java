package servlet;

import domain.Recipe;
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
        try{
            User user = mainRepository.authenticate(username);
            if (user != null){
                HttpSession session = req.getSession();
                session.setAttribute("username", username);
                session.setAttribute("userID", user.getId());
                Recipe recipe=mainRepository.hasUnfinishedRecipe(user.getId());
                if(recipe!=null){
                    String title = "";
                    for(char c : recipe.getTitle().toCharArray()){
                        if(c!='-'){
                            title = title.concat(String.valueOf(c));
                        }
                        else {
                            break;
                        }
                    }
                    req.getSession().setAttribute("recipeID", recipe.getId());
                    req.getSession().setAttribute("recipeTitle", title);
                    resp.sendRedirect(req.getContextPath() + "/build");
                }else{
                    resp.sendRedirect(req.getContextPath() + "/title");
                }
            }
            else{
                req.setAttribute("error", "Invalid username");
                req.getRequestDispatcher("/login.jsp").forward(req, resp);
            }
        }catch (Exception e){
            req.setAttribute("error", e.getMessage());
            req.getRequestDispatcher("/login.jsp").forward(req, resp);
        }

    }
}
