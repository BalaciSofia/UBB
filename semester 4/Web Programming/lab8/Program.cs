using Microsoft.AspNetCore.DataProtection;
using lab8.Repositories;
using lab8.Service;

var builder = WebApplication.CreateBuilder(args);

builder.Logging.ClearProviders();
builder.Logging.AddConsole();

builder.Services.AddControllers();
builder.Services.AddDistributedMemoryCache();
builder.Services.AddDataProtection()
    .PersistKeysToFileSystem(new DirectoryInfo(Path.Combine(builder.Environment.ContentRootPath, "App_Data", "Keys")));
builder.Services.AddSession(options =>
{
    options.Cookie.Name = ".Lab8.Session";
    options.Cookie.HttpOnly = true;
    options.Cookie.SameSite = SameSiteMode.Lax;
    options.IdleTimeout = TimeSpan.FromMinutes(45);
});
builder.Services.AddCors(options =>
{
    options.AddDefaultPolicy(policy =>
        policy.SetIsOriginAllowed(origin => new Uri(origin).Host is "localhost" or "127.0.0.1")
            .AllowAnyHeader()
            .AllowAnyMethod()
            .AllowCredentials());
});
string connectionString = builder.Configuration.GetConnectionString("GradesDatabase")!;
builder.Services.AddScoped<UserRepository>(provider =>new UserRepository(connectionString));
builder.Services.AddScoped<CourseRepository>(provider =>new CourseRepository(connectionString));
builder.Services.AddScoped<GradeRepository>(provider =>new GradeRepository(connectionString));
builder.Services.AddScoped<UserService>();
builder.Services.AddScoped<CourseService>();
builder.Services.AddScoped<GradeService>();

var app = builder.Build();

app.UseRouting();
app.UseCors();
app.UseSession();
app.UseAuthorization();
app.MapControllers();

app.Run();
