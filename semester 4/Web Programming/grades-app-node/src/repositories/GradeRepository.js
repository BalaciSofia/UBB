const pool = require('../config/database');
const Grade = require('../domain/Grade');

class GradeRepository {
  async findByStudentAndCourse(studentId, courseId) {
    const [rows] = await pool.execute(
      'SELECT gradeId, studentId, courseId, grade FROM grades WHERE studentId = ? AND courseId = ?',
      [studentId, courseId]
    );
    if (rows.length === 0) return null;
    return new Grade(rows[0]);
  }

  async upsert(studentId, courseId, grade) {
    const existing = await this.findByStudentAndCourse(studentId, courseId);
    if (existing) {
      await pool.execute(
        'UPDATE grades SET grade = ? WHERE studentId = ? AND courseId = ?',
        [grade, studentId, courseId]
      );
    } else {
      await pool.execute(
        'INSERT INTO grades (studentId, courseId, grade) VALUES (?, ?, ?)',
        [studentId, courseId, grade]
      );
    }
  }

  async findByStudentId(studentId) {
    const [rows] = await pool.execute(
      `SELECT courses.name AS courseName, grades.grade
       FROM grades
       JOIN courses ON grades.courseId = courses.courseId
       WHERE studentId = ?
       ORDER BY courses.name ASC`,
      [studentId]
    );
    return rows;
  }

  async findByStudentsAndCourse(studentIds, courseId) {
    if (studentIds.length === 0) return [];
    const placeholders = studentIds.map(() => '?').join(',');
    const [rows] = await pool.execute(
      `SELECT studentId, grade FROM grades WHERE studentId IN (${placeholders}) AND courseId = ?`,
      [...studentIds, courseId]
    );
    return rows;
  }
}

module.exports = GradeRepository;
