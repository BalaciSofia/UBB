import pickle
from src.domain import Student


class Repository:
    def add(self, student):
        pass

    def remove(self, student):
        pass

    def get_all(self):
        pass


class MemoryRepository(Repository):
    def __init__(self):
        self.__students = []

    @property
    def students(self):
        return self.__students

    def add(self, student):
        """Adds a student to a memory list

        Args:
            student (student): has an id, name and group number
        """
        self.__students.append(student)

    def remove(self, student_id):
        self.__students = [student for student in self.__students if student.id != student_id]

    def get_all(self):
        return self.students

    def clear(self):
        self.__students = []


class TextFileRepository(Repository):
    def __init__(self, filename):
        self.__filename = filename
        self.__students = self.load()

    @property
    def students(self):
        return self.__students

    @property
    def file_name(self):
        return self.__filename

    def load(self):
        students = []
        try:
            with open(self.file_name, "r") as file:
                lines = file.readlines()
                for line in lines:
                    line = line.strip()
                    parts = line.split(",")
                    student = Student(int(parts[0]), parts[1], int(parts[2]))
                    students.append(student)
        except FileNotFoundError:
            pass
        return students

    def save(self):
        with open(self.file_name, "w") as file:
            for student in self.students:
                file.write(str(student.id) + "," + student.name + "," + str(student.group) + "\n")

    def add(self, student):
        """Adds a student to a text file

        Args:
            student (student): has an id, name and group number
        return: None (The file will be saved)
        """
        self.students.append(student)
        self.save()

    def remove(self, student_id):
        self.__students = [student for student in self.__students if student.id != student_id]

    def get_all(self):
        return self.__students

    def clear(self):
        self.__students = []
        self.save()


class BinaryFileRepository(Repository):

    def __init__(self, filename="students.pickle"):
        self.__filename = filename
        self.__students = self.load()

    @property
    def students(self):
        return self.__students

    @property
    def file_name(self):
        return self.__filename

    def load(self):
        try:
            with open(self.file_name, "rb") as file:
                return pickle.load(file)
        except FileNotFoundError:
            return []

    def save(self):
        with open(self.file_name, "wb") as file:
            pickle.dump(self.students, file)

    def add(self, student):
        """Adds a student to a binary file using the pickle module

        Args:
            student (student): has an id, name and group number
        return: None (The file will be saved)
        """
        self.students.append(student)
        self.save()

    def remove(self, student_id):
        self.__students = [student for student in self.__students if student.id != student_id]

    def get_all(self):
        return self.__students

    def clear(self):
        self.__students = []
        self.save()

