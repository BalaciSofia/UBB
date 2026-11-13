const GradeRepository = require('../repositories/GradeRepository');

class StudentService {
  constructor() {
    this.gradeRepository = new GradeRepository();
  }

  async getGrades(studentId) {
    return this.gradeRepository.findByStudentId(studentId);
  }
}

module.exports = StudentService;
