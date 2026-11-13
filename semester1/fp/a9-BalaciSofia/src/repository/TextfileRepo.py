from src.domain.student import Student
from src.domain.assignment import Assignment
from src.domain.grade import Grade

class TextFileRepositoryStudent:
    def __init__(self,filename):
        self.__filename = filename
        self.__students = self.load()

    @property
    def get_filename(self):
        return self.__filename

    def get_all_students(self):
        return self.get_students

    @property
    def get_students(self):
        return self.__students

    def load(self):
        students = []
        with open(self.get_filename,'r') as file:
            lines=file.readlines()
            for line in lines:
                line=line.strip()
                parts=line.split(',')
                student=Student(int(parts[0]),parts[1],int(parts[2]))
                students.append(student)
        return students
    def save(self):
        with open(self.get_filename,'w') as file:
            for student in self.get_all_students():
                file.write(str(student.get_student_id)+","+student.get_name+","+str(student.get_group)+"\n")
    def add_student(self,student):
        self.get_students.append(student)
        self.save()
    def remove_student(self,student):
        self.get_students.remove(student)
        self.save()
    def update_student(self,student,name):
        student.set_name(name)
        self.save()
    def clear(self):
        self.__students = []
        self.save()

class TextFileRepositoryAssignment:
    def __init__(self,filename):
        self.__filename = filename
        self.__assignments =self.load()

    @property
    def get_assignments(self):
        return self.__assignments

    def get_all_assignments(self):
        return self.get_assignments

    def load(self):
        assignments = []
        with open(self.__filename,'r') as file:
            lines=file.readlines()
            for line in lines:
                line=line.strip()
                parts=line.split(',')
                assignment=Assignment(int(parts[0]),parts[1],parts[2])
                assignments.append(assignment)
        return assignments

    def save(self):
        with open(self.__filename,'w') as file:
            for assignment in self.get_all_assignments():
                file.write(str(assignment.get_assignment_id)+","+assignment.get_description+","+str(assignment.get_deadline)+"\n")

    def add_assignment(self,assignment):
        self.get_assignments.append(assignment)
        self.save()

    def remove_assignment(self,assignment):
        self.get_assignments.remove(assignment)
        self.save()

    def update_assignment(self,assignment,deadline):
        assignment.set_deadline(deadline)
        self.save()

    def clear(self):
        self.__assignments=[]
        self.save()

class TextFileRepositoryGrades:
    def __init__(self,filename):
        self.__filename = filename
        self.__grades=self.load()

    @property
    def get_grades(self):
        return self.__grades

    def get_all_grades(self):
        return self.get_grades

    def load(self):
        grades = []
        with open(self.__filename,'r') as file:
            lines=file.readlines()
            for line in lines:
                line=line.strip()
                parts=line.split(',')
                try:
                    grade_value=int(parts[0])
                    grade=Grade(grade_value,int(parts[1]),int(parts[2]))
                except ValueError:
                    grade=Grade(str(parts[0]),int(parts[1]),int(parts[2]))
                grades.append(grade)
        return grades

    def save(self):
        with open(self.__filename,'w') as file:
            for grade in self.get_all_grades():
                file.write(str(grade.get_grade_value)+","+str(grade.get_student_id)+","+str(grade.get_assignment_id)+"\n")

    def add_grade(self,grade):
        self.get_grades.append(grade)
        self.save()

    def remove_grade(self, grade):
        self.get_grades.remove(grade)
        self.save()

    def update_grade(self,grade,grade_value):
        grade.set_grade_value(grade_value)
        self.save()

    def clear(self):
        self.__grades=[]
        self.save()
