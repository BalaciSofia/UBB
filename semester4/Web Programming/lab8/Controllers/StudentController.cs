using lab8.Service;
using Microsoft.AspNetCore.Mvc;

namespace Lab8.Controllers;

[ApiController]
public sealed class StudentController(GradeService gradeService) : ControllerBase
{
    private const string UserIdSessionKey = "userId";
    private const string RoleSessionKey = "role";

    [HttpGet("/student/get-grades")]
    public IActionResult GetGrades()
    {
        if (HttpContext.Session.GetString(RoleSessionKey) != "student")
        {
            return StatusCode(StatusCodes.Status403Forbidden, new { success = false, message = "Unauthorized" });
        }

        var studentId = HttpContext.Session.GetInt32(UserIdSessionKey);
        if (studentId is null)
        {
            return StatusCode(StatusCodes.Status403Forbidden, new { success = false, message = "Unauthorized" });
        }

        var grades = gradeService.GetGradesForStudent(studentId.Value);
        return Ok(new { success = true, grades });
    }
}
