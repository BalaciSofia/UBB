<%@ page import="domain.Task" %>
<%@ page import="java.util.List" %>
<%@ page import="java.util.Map" %><%--
  Created by IntelliJ IDEA.
  User: balac
  Date: 6/12/2026
  Time: 4:25 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    List<Task> todoTasks = (List<Task>) request.getAttribute("todoTasks");
    List<Task> inProgressTasks = (List<Task>) request.getAttribute("inProgressTasks");
    List<Task> doneTasks = (List<Task>) request.getAttribute("doneTasks");
    Map<Integer, String> lastUpdateUsernames = (Map<Integer, String>) request.getAttribute("lastUpdatedBy");
    int moveCount = (int) session.getAttribute("moveCount");
%>
<html>
<head>
    <title>Home</title>
</head>
<body>
<p>Move count<%=moveCount%></p>
<table border="1">
    <tr>
        <th>TODO</th>
        <th>IN_PROGRESS</th>
        <th>DONE</th>
    </tr>
    <tr>
        <td>
            <% for(Task t : todoTasks){ %>
            <div>
                <%=t.getTitle() %>
                <br>
                Last update: <%=t.getLastUpdated() %>
                <br>
                Last update by: <%=lastUpdateUsernames.get(t.getId()) %>
                <form method="post" action="${pageContext.request.contextPath}/home">
                    <input type="hidden" name="taskId" value="<%= t.getId() %>">
                    <input type="hidden" name="oldStatus" value="<%= t.getStatus() %>">

                    <select name="status">
                        <option value="TODO" selected>TODO</option>
                        <option value="IN_PROGRESS">IN_PROGRESS</option>
                        <option value="DONE">DONE</option>
                    </select>

                    <button type="submit">Move</button>
                </form>
            </div>
            <% }%>

        </td>
        <td>
            <% for(Task t : inProgressTasks){ %>
            <div>
                <%=t.getTitle() %>
                <br>
                Last update: <%=t.getLastUpdated() %>
                <br>
                Last update by: <%=lastUpdateUsernames.get(t.getId()) %>
                <form method="post" action="${pageContext.request.contextPath}/home">
                    <input type="hidden" name="taskId" value="<%= t.getId() %>">
                    <input type="hidden" name="oldStatus" value="<%= t.getStatus() %>">

                    <select name="status">
                        <option value="TODO">TODO</option>
                        <option value="IN_PROGRESS" selected>IN_PROGRESS</option>
                        <option value="DONE">DONE</option>
                    </select>

                    <button type="submit">Move</button>
                </form>
            </div>
            <% }%>

        </td>
        <td>
            <% for(Task t : doneTasks){ %>
            <div>
                <%=t.getTitle() %>
                <br>
                Last update: <%=t.getLastUpdated() %>
                <br>
                Last update by: <%=lastUpdateUsernames.get(t.getId()) %>
                <form method="post" action="${pageContext.request.contextPath}/home">
                    <input type="hidden" name="taskId" value="<%= t.getId() %>">
                    <input type="hidden" name="oldStatus" value="<%= t.getStatus() %>">

                    <select name="status">
                        <option value="TODO">TODO</option>
                        <option value="IN_PROGRESS">IN_PROGRESS</option>
                        <option value="DONE" selected>DONE</option>
                    </select>

                    <button type="submit">Move</button>
                </form>
            </div>
            <% }%>

        </td>
    </tr>
</table>

</body>
</html>
<script>
    setInterval(function () {
        window.location.reload();
    }, 5000);
</script>
