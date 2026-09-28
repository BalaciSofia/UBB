class Grade {
  constructor({ gradeId, studentId, courseId, grade }) {
    this.gradeId = gradeId;
    this.studentId = studentId;
    this.courseId = courseId;
    this.grade = grade;
  }
}

module.exports = Grade;
