const pool = require('../config/database');
const Course = require('../domain/Course');

class CourseRepository {
  async findByProfessorId(professorId) {
    const [rows] = await pool.execute(
      'SELECT courseId, name, professorId FROM courses WHERE professorId = ? ORDER BY name LIMIT 1',
      [professorId]
    );
    if (rows.length === 0) return null;
    return new Course(rows[0]);
  }
}

module.exports = CourseRepository;
