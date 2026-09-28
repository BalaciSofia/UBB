using lab8.Service;
using Microsoft.AspNetCore.Mvc;

namespace Lab8.Controllers;

[ApiController]
public sealed class ProfessorController(
    UserService userService,
    CourseService courseService,
    GradeService gradeService) : ControllerBase
{
    private const int PageSize = 4;
    private const string UserIdSessionKey = "userId";
    private const string RoleSessionKey = "role";

    [HttpGet("/professor/get-context")]
    public IActionResult GetContext()
    {
        if (!TryGetProfessorId(out var professorId))
        {
            return StatusCode(StatusCodes.Status403Forbidden, new { success = false, message = "Unauthorized" });
        }

        var course = courseService.GetProfessorCourse(professorId);
        var groups = userService.GetGroups()
            .Select(group => new { value = group, label = group })
            .ToList();
        if (course is null)
        {
            return Ok(new { success = false, message = "No course assigned to this professor.", course, groups });
        }

        return Ok(new { success = true, course, groups });
    }

    [HttpGet("/professor/get-students")]
    public IActionResult GetStudents([FromQuery] string group, [FromQuery] int page = 1)
    {
        if (!TryGetProfessorId(out var professorId))
        {
            return StatusCode(StatusCodes.Status403Forbidden, new { success = false, message = "Unauthorized" });
        }

        if (string.IsNullOrWhiteSpace(group))
        {
            return BadRequest(new { success = false, message = "Group is required" });
        }

        var course = courseService.GetProfessorCourse(professorId);
        if (course is null)
        {
            return StatusCode(StatusCodes.Status403Forbidden, new { success = false, message = "No course assigned to this professor" });
        }

        page = Math.Max(page, 1);
        var total = userService.CountStudentsInGroup(group.Trim());
        var totalPages = Math.Max(1, (int)Math.Ceiling(total / (double)PageSize));
        page = Math.Min(page, totalPages);

        var students = userService.GetStudentsFromGroup(group.Trim(), course.CourseId, PageSize, (page - 1) * PageSize);
        return Ok(new { success = true, students, page, totalPages });
    }

    [HttpPost("/professor/save-grade")]
    public IActionResult SaveGrade([FromForm] int studentId, [FromForm] decimal grade)
    {
        if (!TryGetProfessorId(out var professorId))
        {
            return StatusCode(StatusCodes.Status403Forbidden, new { success = false, message = "Unauthorized" });
        }

        if (studentId <= 0 || grade is < 1 or > 10)
        {
            return BadRequest(new { success = false, message = "Invalid grade payload" });
        }

        var course = courseService.GetProfessorCourse(professorId);
        if (course is null)
        {
            return StatusCode(StatusCodes.Status403Forbidden, new { success = false, message = "No course assigned to this professor" });
        }

        if (!userService.StudentExists(studentId))
        {
            return BadRequest(new { success = false, message = "Student not found" });
        }

        var existed = gradeService.GradeExists(studentId, course.CourseId);
        gradeService.SaveGrade(studentId, course.CourseId, grade);

        return Ok(new
        {
            success = true,
            message = existed ? "Grade updated successfully" : "Grade saved successfully"
        });
    }

    private bool TryGetProfessorId(out int professorId)
    {
        professorId = HttpContext.Session.GetInt32(UserIdSessionKey) ?? 0;
        return professorId > 0 && HttpContext.Session.GetString(RoleSessionKey) == "professor";
    }
}
