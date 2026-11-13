const CourseRepository = require('../repositories/CourseRepository');
const UserRepository = require('../repositories/UserRepository');
const GradeRepository = require('../repositories/GradeRepository');

const PAGE_SIZE = 4;

class ProfessorService {
  constructor() {
    this.courseRepository = new CourseRepository();
    this.userRepository = new UserRepository();
    this.gradeRepository = new GradeRepository();
  }

  async getContext(professorId) {
    const course = await this.courseRepository.findByProfessorId(professorId);
    if (!course) {
      return { course: null, groups: [] };
    }

    const groupCodes = await this.userRepository.findDistinctGroups();
    const groups = groupCodes.map(code => ({ value: code, label: code }));

    return {
      course: { courseId: course.courseId, name: course.name },
      groups,
    };
  }

  async getStudents(professorId, groupCode, page) {
    const course = await this.courseRepository.findByProfessorId(professorId);
    if (!course) {
      const err = new Error('No course assigned to this professor');
      err.status = 403;
      throw err;
    }

    if (!groupCode) {
      const err = new Error('Group is required');
      err.status = 400;
      throw err;
    }

    const currentPage = Math.max(1, parseInt(page) || 1);
    const total = await this.userRepository.countStudentsByGroup(groupCode);
    const totalPages = Math.max(1, Math.ceil(total / PAGE_SIZE));
    const safePage = Math.min(currentPage, totalPages);
    const offset = (safePage - 1) * PAGE_SIZE;

    const students = await this.userRepository.findStudentsByGroup(groupCode, PAGE_SIZE, offset);
    const studentIds = students.map(s => s.userId);
    const gradeRows = await this.gradeRepository.findByStudentsAndCourse(studentIds, course.courseId);

    const gradeMap = new Map(gradeRows.map(g => [g.studentId, g.grade]));

    return {
      students: students.map(s => ({
        userId: s.userId,
        name: s.name,
        grade: gradeMap.has(s.userId) ? gradeMap.get(s.userId) : null,
      })),
      page: safePage,
      totalPages,
    };
  }

  async saveGrade(professorId, studentId, grade) {
    if (!studentId || studentId <= 0 || grade < 1 || grade > 10) {
      const err = new Error('Invalid grade payload');
      err.status = 400;
      throw err;
    }

    const course = await this.courseRepository.findByProfessorId(professorId);
    if (!course) {
      const err = new Error('No course assigned to this professor');
      err.status = 403;
      throw err;
    }

    const student = await this.userRepository.findById(studentId);
    if (!student || student.role !== 'student') {
      const err = new Error('Student not found');
      err.status = 400;
      throw err;
    }

    await this.gradeRepository.upsert(studentId, course.courseId, grade);
  }
}

module.exports = ProfessorService;
