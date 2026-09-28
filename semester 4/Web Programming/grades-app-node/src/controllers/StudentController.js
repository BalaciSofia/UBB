const StudentService = require('../services/StudentService');

class StudentController {
  constructor() {
    this.studentService = new StudentService();
    this.getGrades = this.getGrades.bind(this);
  }

  async getGrades(req, res) {
    try {
      const grades = await this.studentService.getGrades(req.session.userId);
      res.json({ success: true, grades });
    } catch (err) {
      res.status(err.status || 500).json({ success: false, message: err.message });
    }
  }
}

module.exports = StudentController;
