
class MemoryRepositoryStudent:
    def __init__(self):
        self.__students = []

    @property
    def get_students(self):
        return self.__students

    def get_all_students(self):
        return self.get_students

    def add_student(self,student):
        """
        Adds a student to memory list
        :param student:an object student(which has an id,name,group)
        """
        self.get_students.append(student)
    def remove_student(self,student):
        """
        Removes a student from memory list
        :param student: an object student(which has an id,name,group)
        """
        self.get_students.remove(student)

    def update_student(self,student,name):
        """
        Updates a student in memory list
        :param student: the student that is being updated
        :param name: the new name of the student with id student_id
        """
        student.set_name(name)

    def clear_students(self):
        self.__students = []

class MemoryRepositoryAssignment:
    def __init__(self):
        self.__assignments = []

    @property
    def get_assignments(self):
        return self.__assignments

    def get_all_assignments(self):
        return self.get_assignments

    def add_assignment(self,assignment):
        """
        Adds an assignment to memory list
        :param assignment: an object assignment(which has an id,description,deadline)
        """
        self.get_assignments.append(assignment)

    def remove_assignment(self,assignment):
        """
        Removes an assignment from memory list
        :param assignment: an object assignment(which has an id,description,deadline)
        """
        self.get_assignments.remove(assignment)

    def update_assignment(self,assignment,deadline):
        """
        Updates an assignment in memory list
        :param assignment: the object assignment(which has an id,description,deadline)
        :param deadline: the new deadline for the assignment with id assignment.id
        """
        assignment.set_deadline(deadline)

    def clear_assignments(self):
        self.__assignments = []

class MemoryRepositoryGrades:
    def __init__(self):
        self.__grades = []

    @property
    def get_grades(self):
        return self.__grades

    def get_all_grades(self):
        return self.get_grades

    def add_grade(self,grade):
        """
        Adds a grade to memory list
        :param grade: an object grade(which has an assignment_id,student_id,grade_value)
        """
        self.get_grades.append(grade)

    def remove_grade(self, grade):
        """
        Removes a grade from memory list
        :param grade:
        """
        self.get_grades.remove(grade)
    def update_grade(self,grade,grade_value):
        grade.set_grade_value(grade_value)
