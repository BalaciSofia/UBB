<%@ page import="domain.Ingredient" %>
<%@ page import="java.util.List" %>
<%@ page import="domain.RecipeSteps" %><%--
  Created by IntelliJ IDEA.
  User: balac
  Date: 6/17/2026
  Time: 2:24 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    List<RecipeSteps> recipesteps = (List<RecipeSteps>) request.getAttribute("recipesteps");
%>
<html>
<head>
    <title>Build</title>
</head>
<body>
<h2>Add step</h2>
<form method="post" action="${pageContext.request.contextPath}/build">
    <input type="text" name="description" placeholder="description" required><br>
    <input type="hidden" name="action" value="addStep">

    <%
    List<Ingredient> ingredients = (List<Ingredient>) request.getAttribute("ingredients");
    for (Ingredient i : ingredients ) {
       %>
    <input type="checkbox" name="ingredientIDs" value=<%= i.getId() %>><%= i.getName() %><br>
    <%
    }
%>
    <button type="submit">Add Step</button>
</form>

<h2>Steps</h2>
<table border="1">
    <tr>
        <th>Id</th>
        <th>StepNumber</th>
        <th>Description</th>
        <th>Ingredients</th>
        <th>Remove</th>
    </tr>
    <%if (!recipesteps.isEmpty()) { %>
    <tr>
        <% for (RecipeSteps i : recipesteps) { %>
        <tr>
        <td><%= i.getId() %></td>
        <td><%= i.getStepNumber() %></td>
        <td><%= i.getDescription() %></td>
        <td><%= i.getIngredientIDs() %></td>
    <td><form method="post" action="${pageContext.request.contextPath}/build">
        <input type="hidden" name="stepID" value="<%= i.getId() %>">
        <input type="hidden" name="action" value="removeStep">
        <button type="submit">Remove</button>
    </form></td>
</tr>
        <% } %>

    </tr>
    <% } %>
</table>
<form method="post" action="${pageContext.request.contextPath}/build">
    <input type="hidden" name="action" value="finish">
    <button type="submit">Finish Building</button>
</form>
</body>
</html>
