namespace lab8.Domain;

public sealed class Course
{
    public int CourseId { get; set; }
    public string Name { get; set; } = string.Empty;
    public int ProfessorId { get; set; }
}
