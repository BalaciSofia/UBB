package servlet;

import domain.Game;
import domain.GameState;
import domain.Player;
import domain.Symbol;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class GameServlet extends BaseServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getSession().getAttribute("username").toString();
        Symbol symbol = gameService().join(username);

        if (symbol == null) {
            req.setAttribute("error", gameService().getLastMessage());
            req.getRequestDispatcher("/WEB-INF/jsp/rejected.jsp").forward(req, resp);
            return;
        }

        req.getSession().setAttribute("symbol", symbol.name());
        req.setAttribute("symbol", symbol.name());
        req.getRequestDispatcher("/WEB-INF/jsp/game.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        HttpSession session = req.getSession(false);
        String username = session.getAttribute("username").toString();
        String action = req.getParameter("action");

        resp.setContentType("application/json");
        resp.setCharacterEncoding("UTF-8");

        if ("state".equals(action)) {
            writeState(resp, username, null);
            return;
        }
        if ("move".equals(action)) {
            int cell = parseCell(req.getParameter("cell"));
            String error = gameService().makeMove(username, cell);
            writeState(resp, username, error);
            return;
        }
        if ("reset".equals(action)) {
            gameService().resetRound();
            writeState(resp, username, null);
            return;
        }

        resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
        resp.getWriter().write("{\"error\":\"Unknown action.\"}");
    }

    private int parseCell(String value) {
        try {
            return Integer.parseInt(value);
        } catch (NumberFormatException e) {
            return -1;
        }
    }

    private void writeState(HttpServletResponse resp, String username, String error) throws IOException {
        GameState state = gameService().getState();
        Game game = state.getGame();
        Player currentPlayer = null;
        for (Player player : state.getPlayers()) {
            if (player.getUsername().equals(username)) {
                currentPlayer = player;
                break;
            }
        }

        StringBuilder json = new StringBuilder();
        json.append("{");
        json.append("\"board\":\"").append(game.getBoard()).append("\",");
        json.append("\"currentTurn\":\"").append(game.getCurrentTurn().name()).append("\",");
        json.append("\"status\":\"").append(game.getStatus().name()).append("\",");
        json.append("\"winner\":").append(game.getWinner() == null ? "null" : "\"" + game.getWinner().name() + "\"").append(",");
        json.append("\"currentUser\":\"").append(escape(username)).append("\",");
        json.append("\"mySymbol\":").append(currentPlayer == null ? "null" : "\"" + currentPlayer.getSymbol().name() + "\"").append(",");
        json.append("\"players\":[");
        for (int i = 0; i < state.getPlayers().size(); i++) {
            Player player = state.getPlayers().get(i);
            if (i > 0) {
                json.append(",");
            }
            json.append("{\"username\":\"").append(escape(player.getUsername())).append("\",");
            json.append("\"symbol\":\"").append(player.getSymbol().name()).append("\"}");
        }
        json.append("],");
        json.append("\"error\":").append(error == null ? "null" : "\"" + escape(error) + "\"");
        json.append("}");
        resp.getWriter().write(json.toString());
    }

    private String escape(String value) {
        return value.replace("\\", "\\\\").replace("\"", "\\\"");
    }
}
