<%@ page import="domain.RecipeSteps" %>
<%@ page import="java.util.List" %>
<%@ page import="domain.Recipe" %><%--
  Created by IntelliJ IDEA.
  User: balac
  Date: 6/17/2026
  Time: 3:20 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    List<RecipeSteps> recipesteps = (List<RecipeSteps>) request.getAttribute("recipesteps");
    String title = request.getSession().getAttribute("recipeTitle").toString();
    int calories = (int) request.getAttribute("totalCalories");
    List<Recipe> recipes = (List<Recipe>) request.getAttribute("recipes");
%>
<html>
<head>
    <title>Confirmation</title>
</head>
<body>
<h2>Title <%=title%></h2>

<table border="1">
    <tr>
        <th>Id</th>
        <th>StepNumber</th>
        <th>Description</th>
        <th>Ingredients</th>
    </tr>
    <%if (!recipesteps.isEmpty()) { %>
    <tr>
            <% for (RecipeSteps i : recipesteps) { %>
    <tr>
        <td><%= i.getId() %></td>
        <td><%= i.getStepNumber() %></td>
        <td><%= i.getDescription() %></td>
        <td><%= i.getIngredientIDs() %></td>
    </tr>
    <% } %>

    </tr>
    <% } %>
</table>

<h2>Total Calories <%=calories%></h2>

<form method="post" action="${pageContext.request.contextPath}/confirm">
    <input type="hidden" name="action" value="confirm">
    <button type="submit">Confirm</button>
</form>
<form method="post" action="${pageContext.request.contextPath}/confirm">
    <input type="hidden" name="action" value="discard">
    <button type="submit">Discard</button>
</form>

<% if (request.getAttribute("foodGroupMessage") != null) { %>
<p><%= request.getAttribute("foodGroupMessage") %></p>
<% } %>

<h2>your recipes</h2>
<table border="1">
    <tr>
        <th>Id</th>
        <th>Title</th>
        <th>TotalCalories</th>
        <th>Delete?</th>
    </tr>
    <%if (!recipes.isEmpty()) { %>
    <tr>
            <% for (Recipe r : recipes) { %>
    <tr>
        <td><%= r.getId() %></td>
        <td><%= r.getTitle() %></td>
        <td><%= r.getTotalCalories() %></td>
    <td>
        <form method="post" action="${pageContext.request.contextPath}/confirm">
            <input type="hidden" name="action" value="delete">
            <input type="hidden" name="recipeID" value="<%= r.getId() %>">
            <button type="submit">Delete</button>
        </form>
    </td>
    </tr>
    <% } %>

    </tr>
    <% } %>
</table>
</body>
</html>
