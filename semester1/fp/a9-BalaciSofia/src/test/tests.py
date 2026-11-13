from unittest import TestCase
from src.repository.MemoryRepo import MemoryRepositoryAssignment, MemoryRepositoryStudent, MemoryRepositoryGrades
from src.repository.TextfileRepo import  TextFileRepositoryStudent, TextFileRepositoryAssignment, TextFileRepositoryGrades
from src.repository.BinaryfileRepo import  BinaryFileRepositoryGrades, BinaryFileRepositoryAssignment,BinaryFileRepositoryStudent
from src.services import Services
from src.domain import Grade

class TestMemoryRepository(TestCase):
    def setUp(self):
        self.repo_stud=MemoryRepositoryStudent()
        self.repo_asg=MemoryRepositoryAssignment()
        self.repo_grade=MemoryRepositoryGrades()
        self.services=Services(self.repo_stud,self.repo_asg,self.repo_grade)

    def test_add_student(self):
        self.services.add_student(1, "Alice", 215)
        students = self.repo_stud.get_all_students()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id, 1)
        self.assertEqual(students[0].get_name, "Alice")
        self.assertEqual(students[0].get_group, 215)

    def test_remove_student_id(self):
        self.services.add_student(1, "Alice", 215)
        self.services.add_student(2, "Mary", 215)
        students = self.repo_stud.get_all_students()
        self.assertEqual(len(students), 2)
        self.services.remove_student_id(1)
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id, 2)
        self.assertEqual(students[0].get_name, "Mary")
        self.assertEqual(students[0].get_group, 215)

    def test_remove_student_name(self):
        self.services.add_student(1, "Alice", 215)
        self.services.add_student(2, "Mary", 215)
        students = self.repo_stud.get_all_students()
        self.assertEqual(len(students), 2)
        self.services.remove_student_name("Alice")
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id, 2)
        self.assertEqual(students[0].get_name, "Mary")
        self.assertEqual(students[0].get_group, 215)

    def  test_update_student(self):
        self.services.add_student(1, "Alice", 215)
        students = self.repo_stud.get_all_students()
        self.services.update_student(1,"Mary")
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id,    1)
        self.assertEqual(students[0].get_name, "Mary")
        self.assertEqual(students[0].get_group, 215)

    def test_add_assignment(self):
        self.services.add_assignment(1, "nothing", 2024-12-26)
        assignments = self.repo_asg.get_all_assignments()
        self.assertEqual(len(assignments), 1)
        self.assertEqual(assignments[0].get_assignment_id, 1)
        self.assertEqual(assignments[0].get_description, "nothing")
        self.assertEqual(assignments[0].get_deadline, 2024-12-26)

    def test_remove_assignment_id(self):
        self.services.add_assignment(1, "nothing", 2024-12-26)
        self.services.add_assignment(2, "nothing2", 2024-12-27)
        assignments = self.repo_asg.get_all_assignments()
        self.assertEqual(len(assignments), 2)
        self.services.remove_assignment_id(1)
        self.assertEqual(len(assignments), 1)
        self.assertEqual(assignments[0].get_assignment_id, 2)
        self.assertEqual(assignments[0].get_description, "nothing2")
        self.assertEqual(assignments[0].get_deadline, 2024-12-27)

    def test_update_assignment(self):
        self.services.add_assignment(1, "nothing", 2024 - 12 - 26)
        assignments = self.repo_asg.get_all_assignments()
        self.services.update_assignment(1,2024-12-27)
        self.assertEqual(len(assignments), 1)
        self.assertEqual(assignments[0].get_assignment_id, 1)
        self.assertEqual(assignments[0].get_description, "nothing")
        self.assertEqual(assignments[0].get_deadline, 2024 - 12 - 27)

    def test_search_std(self):
        self.services.add_student(1, "Alice", 215)
        self.assertEqual(self.services.search_std(1),1)
        self.assertEqual(self.services.search_std(2),0)

    def test_search_assignment(self):
        self.services.add_assignment(1, "nothing", 2024 - 12 - 26)
        self.assertEqual(self.services.search_assignment(1),1)
        self.assertEqual(self.services.search_assignment(2),0)

    def test_give_student(self):
        self.services.add_student(1, "Alice", 215)
        self.services.add_assignment(1, "nothing", 2024 - 12 - 26)
        self.services.give_student(1,1)
        grades=self.repo_grade.get_all_grades()
        self.assertEqual(len(grades), 1)
        self.assertEqual(grades[0].get_student_id, 1)
        self.assertEqual(grades[0].get_assignment_id, 1)
        self.assertEqual(grades[0].get_grade_value, "-")

    def test_search_group(self):
        self.services.add_student(1, "Alice", 215)
        self.assertEqual(self.services.search_group(215),1)
        self.assertEqual(self.services.search_group(214),0)

    def test_verify_assignment(self):
        grade=Grade(5,1,5)
        self.services.repo_grade.add_grade(grade)
        self.assertEqual(self.services.verify_assignment(1,5), 0)
        self.assertEqual(self.services.verify_assignment(1,7), 1)

    def test_grade(self):
        grade = Grade("-", 1, 5)
        grades= self.repo_grade.get_all_grades()
        self.services.repo_grade.add_grade(grade)
        self.services.grade(5,1,10)
        self.assertEqual(grades[0].get_grade_value, 10)
        self.assertEqual(grades[0].get_assignment_id, 5)
        self.assertEqual(grades[0].get_student_id, 1)

    def run_all_tests(self):
        self.test_add_student()
        self.test_remove_student_id()
        self.test_remove_student_name()
        self.test_update_student()
        self.test_add_assignment()
        self.test_remove_assignment_id()
        self.test_update_assignment()
        self.test_search_std()
        self.test_search_assignment()
        self.test_give_student()
        self.test_search_group()
        self.test_verify_assignment()
        self.test_grade()

class TestBinaryfileRepository(TestCase):
    def setUp(self):
        self.repo_stud = BinaryFileRepositoryStudent("students_test.pickle")
        self.repo_asg = BinaryFileRepositoryAssignment("assignments_test.pickle")
        self.repo_grade = BinaryFileRepositoryGrades("grades_test.pickle")
        self.services = Services(self.repo_stud, self.repo_asg, self.repo_grade)


    def test_add_student(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        students = self.repo_stud.get_all_students()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id, 1)
        self.assertEqual(students[0].get_name, "Alice")
        self.assertEqual(students[0].get_group, 215)

    def test_remove_student_id(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        self.services.add_student(2, "Mary", 215)
        students = self.repo_stud.get_all_students()
        self.assertEqual(len(students), 2)
        self.services.remove_student_id(1)
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id, 2)
        self.assertEqual(students[0].get_name, "Mary")
        self.assertEqual(students[0].get_group, 215)

    def test_remove_student_name(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        self.services.add_student(2, "Mary", 215)
        students = self.repo_stud.get_all_students()
        self.assertEqual(len(students), 2)
        self.services.remove_student_name("Alice")
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id, 2)
        self.assertEqual(students[0].get_name, "Mary")
        self.assertEqual(students[0].get_group, 215)

    def  test_update_student(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        students = self.repo_stud.get_all_students()
        self.services.update_student(1,"Mary")
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id,    1)
        self.assertEqual(students[0].get_name, "Mary")
        self.assertEqual(students[0].get_group, 215)

    def test_add_assignment(self):
        self.repo_asg.clear()
        self.services.add_assignment(1, "nothing", 2024-12-26)
        assignments = self.repo_asg.get_all_assignments()
        self.assertEqual(len(assignments), 1)
        self.assertEqual(assignments[0].get_assignment_id, 1)
        self.assertEqual(assignments[0].get_description, "nothing")
        self.assertEqual(assignments[0].get_deadline, 2024-12-26)

    def test_remove_assignment_id(self):
        self.repo_asg.clear()
        self.services.add_assignment(1, "nothing", 2024-12-26)
        self.services.add_assignment(2, "nothing2", 2024-12-27)
        assignments = self.repo_asg.get_all_assignments()
        self.assertEqual(len(assignments), 2)
        self.services.remove_assignment_id(1)
        self.assertEqual(len(assignments), 1)
        self.assertEqual(assignments[0].get_assignment_id, 2)
        self.assertEqual(assignments[0].get_description, "nothing2")
        self.assertEqual(assignments[0].get_deadline, 2024-12-27)

    def test_update_assignment(self):
        self.repo_asg.clear()
        self.services.add_assignment(1, "nothing", 2024 - 12 - 26)
        assignments = self.repo_asg.get_all_assignments()
        self.services.update_assignment(1,2024-12-27)
        self.assertEqual(len(assignments), 1)
        self.assertEqual(assignments[0].get_assignment_id, 1)
        self.assertEqual(assignments[0].get_description, "nothing")
        self.assertEqual(assignments[0].get_deadline, 2024 - 12 - 27)
    def test_search_std(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        self.assertEqual(self.services.search_std(1),1)
        self.assertEqual(self.services.search_std(2),0)

    def test_search_assignment(self):
        self.repo_asg.clear()
        self.services.add_assignment(1, "nothing", 2024 - 12 - 26)
        self.assertEqual(self.services.search_assignment(1),1)
        self.assertEqual(self.services.search_assignment(2),0)

    def test_give_student(self):
        self.repo_stud.clear()
        self.repo_grade.clear()
        self.repo_asg.clear()
        self.services.add_student(1, "Alice", 215)
        self.services.add_assignment(1, "nothing", 2024 - 12 - 26)
        self.services.give_student(1,1)
        grades=self.repo_grade.get_all_grades()
        self.assertEqual(len(grades), 1)
        self.assertEqual(grades[0].get_student_id, 1)
        self.assertEqual(grades[0].get_assignment_id, 1)
        self.assertEqual(grades[0].get_grade_value, "-")

    def test_search_group(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        self.assertEqual(self.services.search_group(215),1)
        self.assertEqual(self.services.search_group(2),0)

    def test_verify_assignment(self):
        self.repo_grade.clear()
        grade=Grade(5,1,5)
        self.services.repo_grade.add_grade(grade)
        self.assertEqual(self.services.verify_assignment(1,5), 0)
        self.assertEqual(self.services.verify_assignment(1,7), 1)

    def test_grade(self):
        self.repo_grade.clear()
        grade = Grade("-", 1, 5)
        grades= self.repo_grade.get_all_grades()
        self.services.repo_grade.add_grade(grade)
        self.services.grade(5,1,10)
        self.assertEqual(grades[0].get_grade_value, 10)
        self.assertEqual(grades[0].get_assignment_id, 5)
        self.assertEqual(grades[0].get_student_id, 1)

    def run_all_tests(self):
        self.test_add_student()
        self.test_remove_student_id()
        self.test_remove_student_name()
        self.test_update_student()
        self.test_add_assignment()
        self.test_remove_assignment_id()
        self.test_update_assignment()
        self.test_search_std()
        self.test_search_assignment()
        self.test_give_student()
        self.test_search_group()
        self.test_verify_assignment()
        self.test_grade()
class TestTextfileRepository(TestCase):
    def setUp(self):
        self.repo_stud = TextFileRepositoryStudent("students_test.txt")
        self.repo_asg = TextFileRepositoryAssignment("assignments_test.txt")
        self.repo_grade = TextFileRepositoryGrades("grades_test.txt")
        self.services = Services(self.repo_stud, self.repo_asg, self.repo_grade)


    def test_add_student(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        students = self.repo_stud.get_all_students()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id, 1)
        self.assertEqual(students[0].get_name, "Alice")
        self.assertEqual(students[0].get_group, 215)

    def test_remove_student_id(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        self.services.add_student(2, "Mary", 215)
        students = self.repo_stud.get_all_students()
        self.assertEqual(len(students), 2)
        self.services.remove_student_id(1)
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id, 2)
        self.assertEqual(students[0].get_name, "Mary")
        self.assertEqual(students[0].get_group, 215)

    def test_remove_student_name(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        self.services.add_student(2, "Mary", 215)
        students = self.repo_stud.get_all_students()
        self.assertEqual(len(students), 2)
        self.services.remove_student_name("Alice")
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id, 2)
        self.assertEqual(students[0].get_name, "Mary")
        self.assertEqual(students[0].get_group, 215)

    def  test_update_student(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        students = self.repo_stud.get_all_students()
        self.services.update_student(1,"Mary")
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].get_student_id,    1)
        self.assertEqual(students[0].get_name, "Mary")
        self.assertEqual(students[0].get_group, 215)

    def test_add_assignment(self):
        self.repo_asg.clear()
        self.services.add_assignment(1, "nothing", 2024-12-26)
        assignments = self.repo_asg.get_all_assignments()
        self.assertEqual(len(assignments), 1)
        self.assertEqual(assignments[0].get_assignment_id, 1)
        self.assertEqual(assignments[0].get_description, "nothing")
        self.assertEqual(assignments[0].get_deadline, 2024-12-26)

    def test_remove_assignment_id(self):
        self.repo_asg.clear()
        self.services.add_assignment(1, "nothing", 2024-12-26)
        self.services.add_assignment(2, "nothing2", 2024-12-27)
        assignments = self.repo_asg.get_all_assignments()
        self.assertEqual(len(assignments), 2)
        self.services.remove_assignment_id(1)
        self.assertEqual(len(assignments), 1)
        self.assertEqual(assignments[0].get_assignment_id, 2)
        self.assertEqual(assignments[0].get_description, "nothing2")
        self.assertEqual(assignments[0].get_deadline, 2024-12-27)

    def test_update_assignment(self):
        self.repo_asg.clear()
        self.services.add_assignment(1, "nothing", 2024 - 12 - 26)
        assignments = self.repo_asg.get_all_assignments()
        self.services.update_assignment(1,2024-12-27)
        self.assertEqual(len(assignments), 1)
        self.assertEqual(assignments[0].get_assignment_id, 1)
        self.assertEqual(assignments[0].get_description, "nothing")
        self.assertEqual(assignments[0].get_deadline, 2024 - 12 - 27)

    def test_search_std(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        self.assertEqual(self.services.search_std(1),1)
        self.assertEqual(self.services.search_std(2),0)

    def test_search_assignment(self):
        self.repo_asg.clear()
        self.services.add_assignment(1, "nothing", 2024 - 12 - 26)
        self.assertEqual(self.services.search_assignment(1),1)
        self.assertEqual(self.services.search_assignment(2),0)

    def test_give_student(self):
        self.repo_stud.clear()
        self.repo_grade.clear()
        self.repo_asg.clear()
        self.services.add_student(1, "Alice", 215)
        self.services.add_assignment(1, "nothing", 2024 - 12 - 26)
        self.services.give_student(1,1)
        grades=self.repo_grade.get_all_grades()
        self.assertEqual(len(grades), 1)
        self.assertEqual(grades[0].get_student_id, 1)
        self.assertEqual(grades[0].get_assignment_id, 1)
        self.assertEqual(grades[0].get_grade_value, "-")

    def test_search_group(self):
        self.repo_stud.clear()
        self.services.add_student(1, "Alice", 215)
        self.assertEqual(self.services.search_group(215),1)
        self.assertEqual(self.services.search_group(2),0)

    def test_verify_assignment(self):
        self.repo_grade.clear()
        grade=Grade(5,1,5)
        self.services.repo_grade.add_grade(grade)
        self.assertEqual(self.services.verify_assignment(1,5), 0)
        self.assertEqual(self.services.verify_assignment(1,7), 1)

    def test_grade(self):
        self.repo_grade.clear()
        grade = Grade("-", 1, 5)
        grades= self.repo_grade.get_all_grades()
        self.services.repo_grade.add_grade(grade)
        self.services.grade(5,1,10)
        self.assertEqual(grades[0].get_grade_value, 10)
        self.assertEqual(grades[0].get_assignment_id, 5)
        self.assertEqual(grades[0].get_student_id, 1)

    def run_all_tests(self):
        self.test_add_student()
        self.test_remove_student_id()
        self.test_remove_student_name()
        self.test_update_student()
        self.test_add_assignment()
        self.test_remove_assignment_id()
        self.test_update_assignment()
        self.test_search_std()
        self.test_search_assignment()
        self.test_give_student()
        self.test_search_group()
        self.test_verify_assignment()
        self.test_grade()
