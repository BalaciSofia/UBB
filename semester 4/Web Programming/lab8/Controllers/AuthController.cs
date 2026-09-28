using lab8.Service;
using Microsoft.AspNetCore.Mvc;

namespace Lab8.Controllers;

[ApiController]
public sealed class AuthController(UserService userService) : ControllerBase
{
    private const string UserIdSessionKey = "userId";
    private const string RoleSessionKey = "role";

    [HttpPost("/auth/login")]
    public IActionResult Login([FromForm] string username, [FromForm] string password)
    {
        if (string.IsNullOrWhiteSpace(username) || string.IsNullOrWhiteSpace(password))
        {
            return BadRequest(new { success = false, message = "Username and password are required" });
        }

        var user = userService.FindByUsername(username.Trim());
        if (user is null || user.Password != password)
        {
            return Unauthorized(new { success = false, message = "Invalid login" });
        }

        HttpContext.Session.SetInt32(UserIdSessionKey, user.UserId);
        HttpContext.Session.SetString(RoleSessionKey, user.Role);

        var redirect = user.Role == "student" ? "../html/student.html" : "../html/professor.html";
        return Ok(new { success = true, role = user.Role, redirect });
    }

    [HttpPost("/auth/logout")]
    public IActionResult Logout()
    {
        HttpContext.Session.Clear();
        return Ok(new { success = true, message = "Logged out successfully" });
    }
}
