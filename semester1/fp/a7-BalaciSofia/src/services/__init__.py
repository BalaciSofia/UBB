import os
from src.domain import Student
import unittest
from src.repository import MemoryRepository, TextFileRepository, BinaryFileRepository


class Services:
    def __init__(self, repository):
        self.__repository = repository
        self.__history = []

    @property
    def repository(self):
        return self.__repository

    @property
    def history(self):
        return self.__history

    def add_student(self, id, name, group):
        """This method calls the add method of the repository (Memo,Binary,TextFile)

        Args:
            id (int): the id of the student
            name (str): the name of the student
            group (int): the group of the student
        """
        if any(student.id == id for student in self.repository.get_all()):
            raise ValueError(f"Student with ID {id} already exists.")
        student = Student(id, name, group)
        self.repository.add(student)
        self.history.append(("add", student))

    def display_students(self):
        students = self.repository.get_all()
        if students:
            for student in students:
                print(student.get_info())
        else:
            print("No students")

    def remove_students_by_group(self, group):
        students = self.repository.get_all()
        students_to_remove = [student for student in students if student.group == group]
        remaining_students = [student for student in students if student.group != group]

        # Remove students in the group
        self.repository.clear()
        for student in remaining_students:
            self.repository.add(student)

        self.history.append(("remove_group", group, students_to_remove))

    def check_group(self, group):
        students = self.repository.get_all()
        for student in students:
            if student.group == group:
                return True
        return False

    def undo(self):
        if not self.history:
            print("No more undos")
            return

        last_action = self.history.pop()
        if last_action[0] == 'add':
            student = last_action[1]
            self.repository.remove(student.id)
            print(f"Undid add action for student: {student.id}")
        elif last_action[0] == 'remove_group':
            students = last_action[2]
            for student in students:
                self.repository.add(student)
            print(f"Undid remove_group action for group: {last_action[1]}")


class TestMemoryRepository(unittest.TestCase):
    def setUp(self):
        self.repo = MemoryRepository()
        self.services = Services(self.repo)

    def test_add_student(self):
        self.services.add_student(1, "Alice", 5)
        students = self.repo.get_all()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].id, 1)
        self.assertEqual(students[0].name, "Alice")
        self.assertEqual(students[0].group, 5)

    def test_add_duplicate_student(self):
        self.services.add_student(1, "Alice", 5)
        self.services.add_student(1, "Alice", 5)  # Adding duplicate
        students = self.repo.get_all()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].id, 1)

    def test_remove_students_by_group(self):
        self.services.add_student(1, "Alice", 5)
        self.services.add_student(2, "Bob", 6)
        self.services.remove_students_by_group(5)
        students = self.repo.get_all()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].id, 2)

        # Undo the removal
        self.services.undo()
        students = self.repo.get_all()
        self.assertEqual(len(students), 2)

    def test_undo_add(self):
        self.services.add_student(1, "Alice", 5)
        self.assertEqual(len(self.repo.get_all()), 1)
        self.services.undo()
        self.assertEqual(len(self.repo.get_all()), 0)

    def tearDown(self):
        self.repo.clear()


class TestTextFileRepository(unittest.TestCase):
    def setUp(self):
        self.repo = TextFileRepository("students.txt")
        self.services = Services(self.repo)

    def test_add_student(self):
        self.services.add_student(1, "Alice", 5)
        students = self.repo.get_all()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].id, 1)
        self.assertEqual(students[0].name, "Alice")
        self.assertEqual(students[0].group, 5)

    def test_add_duplicate_student(self):
        self.services.add_student(1, "Alice", 5)
        self.services.add_student(1, "Alice", 5)  # Adding duplicate
        students = self.repo.get_all()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].id, 1)

    def test_remove_students_by_group(self):
        self.services.add_student(1, "Alice", 5)
        self.services.add_student(2, "Bob", 6)
        self.services.remove_students_by_group(5)
        students = self.repo.get_all()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].id, 2)

        # Undo the removal
        self.services.undo()
        students = self.repo.get_all()
        self.assertEqual(len(students), 2)

    def test_undo_add(self):
        self.services.add_student(1, "Alice", 5)
        self.assertEqual(len(self.repo.get_all()), 1)
        self.services.undo()
        self.assertEqual(len(self.repo.get_all()), 0)

    def tearDown(self):
        try:
            os.remove(self.repo.file_name)
        except FileNotFoundError:
            pass


class TestBinaryFileRepository(unittest.TestCase):
    def setUp(self):
        self.repo = BinaryFileRepository("students.pickle")
        self.services = Services(self.repo)

    def test_add_student(self):
        self.services.add_student(1, "Alice", 5)
        students = self.repo.get_all()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].id, 1)
        self.assertEqual(students[0].name, "Alice")
        self.assertEqual(students[0].group, 5)

    def test_add_duplicate_student(self):
        self.services.add_student(1, "Alice", 5)
        self.services.add_student(1, "Alice", 5)  # Adding duplicate
        students = self.repo.get_all()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].id, 1)

    def test_remove_students_by_group(self):
        self.services.add_student(1, "Alice", 5)
        self.services.add_student(2, "Bob", 6)
        self.services.remove_students_by_group(5)
        students = self.repo.get_all()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].id, 2)

        # Undo the removal
        self.services.undo()
        students = self.repo.get_all()
        self.assertEqual(len(students), 2)

    def test_undo_add(self):
        self.services.add_student(1, "Alice", 5)
        self.assertEqual(len(self.repo.get_all()), 1)
        self.services.undo()
        self.assertEqual(len(self.repo.get_all()), 0)

    def tearDown(self):
        try:
            os.remove(self.repo.file_name)
        except FileNotFoundError:
            pass
