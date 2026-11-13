import pickle

class BinaryFileRepositoryStudent:
    def __init__(self,filename):
        self.__filename = filename
        self.__students=self.load()

    @property
    def get_filename(self):
        return self.__filename
    @property
    def get_students(self):
        return self.__students

    def get_all_students(self):
        return self.get_students

    def load(self):
        try:
            with open(self.get_filename, "rb") as file:
                return pickle.load(file)
        except FileNotFoundError:
            return []

    def save(self):
        with open(self.get_filename, "wb") as file:
            pickle.dump(self.get_students, file)

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
        self.__students=[]
        self.save()

class BinaryFileRepositoryAssignment:
    def __init__(self,filename):
        self.__filename = filename
        self.__assignments=self.load()

    @property
    def get_filename(self):
        return self.__filename

    @property
    def get_assignments(self):
        return self.__assignments

    def get_all_assignments(self):
        return self.get_assignments

    def load(self):
        try:
            with open(self.get_filename, "rb") as file:
                return pickle.load(file)
        except FileNotFoundError:
            return []

    def save(self):
        with open(self.get_filename, "wb") as file:
            pickle.dump(self.get_assignments, file)

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

class BinaryFileRepositoryGrades:
    def __init__(self,filename):
        self.__filename = filename
        self.__grades=self.load()

    @property
    def get_filename(self):
        return self.__filename

    @property
    def get_grades(self):
        return self.__grades

    def get_all_grades(self):
        return self.get_grades

    def load(self):
        try:
            with open(self.get_filename, "rb") as file:
                return pickle.load(file)
        except FileNotFoundError:
            return []

    def save(self):
        with open(self.get_filename, "wb") as file:
            pickle.dump(self.get_grades, file)

    def add_grade(self,grade):
        self.get_grades.append(grade)
        self.save()

    def remove_grade(self, grade):
        self.get_grades.remove(grade)
        self.save()

    def clear(self):
        self.__grades=[]
        self.save()

    def update_grade(self, grade, grade_value):
        grade.set_grade_value(grade_value)
        self.save()


