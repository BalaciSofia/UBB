const ProfessorService = require('../services/ProfessorService');

class ProfessorController {
  constructor() {
    this.professorService = new ProfessorService();
    this.getContext = this.getContext.bind(this);
    this.getStudents = this.getStudents.bind(this);
    this.saveGrade = this.saveGrade.bind(this);
  }

  async getContext(req, res) {
    try {
      const { course, groups } = await this.professorService.getContext(req.session.userId);

      if (!course) {
        return res.json({
          success: false,
          message: 'No course assigned to this professor.',
          course: null,
          groups: [],
        });
      }

      res.json({ success: true, course, groups });
    } catch (err) {
      res.status(err.status || 500).json({ success: false, message: err.message });
    }
  }

  async getStudents(req, res) {
    try {
      const { group, page } = req.query;
      const result = await this.professorService.getStudents(req.session.userId, group, page);
      res.json({ success: true, ...result });
    } catch (err) {
      res.status(err.status || 500).json({ success: false, message: err.message });
    }
  }

  async saveGrade(req, res) {
    try {
      const studentId = parseInt(req.body.studentId);
      const grade = parseFloat(req.body.grade);
      await this.professorService.saveGrade(req.session.userId, studentId, grade);
      res.json({ success: true, message: 'Grade saved successfully' });
    } catch (err) {
      res.status(err.status || 500).json({ success: false, message: err.message });
    }
  }
}

module.exports = ProfessorController;
