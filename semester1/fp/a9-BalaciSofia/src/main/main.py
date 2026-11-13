from datetime import datetime

from src.repository.MemoryRepo import MemoryRepositoryAssignment, MemoryRepositoryStudent, MemoryRepositoryGrades
from src.repository.TextfileRepo import  TextFileRepositoryStudent, TextFileRepositoryAssignment, TextFileRepositoryGrades
from src.repository.BinaryfileRepo import  BinaryFileRepositoryGrades, BinaryFileRepositoryAssignment,BinaryFileRepositoryStudent
from src.domain.student import Student
from src.domain.assignment import Assignment
from src.domain.grade import Grade
from faker import Faker
from src.services.services import Services
from src.ui.ui import UI
import random
from random import shuffle

def main():
    with open("settings.properties", "r") as file:
        lines = file.readlines()
        lines[0].strip()
        parts = lines[0].split("=")
        repo=parts[1].strip()
        if repo!="Memory":
            if repo=="Textfile":
                lines[1].strip()
                parts=lines[1].split("=")
                repo_stud=TextFileRepositoryStudent(parts[1].strip())
                lines[2].strip()
                parts=lines[2].split("=")
                repo_asg=TextFileRepositoryAssignment(parts[1].strip())
                lines[3].strip()
                parts=lines[3].split("=")
                repo_grd=TextFileRepositoryGrades(parts[1].strip())
            elif repo=="Binaryfile":
                lines[1].strip()
                parts = lines[1].split("=")
                repo_stud = BinaryFileRepositoryStudent(parts[1].strip())
                lines[2].strip()
                parts = lines[2].split("=")
                repo_asg = BinaryFileRepositoryAssignment(parts[1].strip())
                lines[3].strip()
                parts = lines[3].split("=")
                repo_grd = BinaryFileRepositoryGrades(parts[1].strip())
            else:
                print("Repository not defined")
        else:
            repo_stud=MemoryRepositoryStudent()
            repo_asg=MemoryRepositoryAssignment()
            repo_grd=MemoryRepositoryGrades()
    fake = Faker()
    if not repo_stud.get_all_students():
        student_id=1
        for i in range(20):
            groups=[911,912,913,914,915,916,917,211,212,213,214,215,216,217]
            group=random.choice(groups)
            student=Student(student_id,fake.name(),group)
            repo_stud.add_student(student)
            student_id+=1
    if not repo_asg.get_all_assignments():
        assignment_id=1
        start_date=datetime(2024,10,1)
        end_date=datetime(2025,7,1)
        for i in range(20):
            assignment=Assignment(assignment_id,fake.text(max_nb_chars=30),fake.date_between(start_date=start_date, end_date=end_date))
            repo_asg.add_assignment(assignment)
            assignment_id+=1
    if not repo_grd.get_all_grades():
        students=repo_stud.get_all_students()
        assignments=repo_asg.get_all_assignments()
        shuffle(students)
        shuffle(assignments)
        for i in range(0,19):
            student_id=students[i].get_student_id
            assignment_id=assignments[i].get_assignment_id
            list_grades=[1,2,3,4,5,6,7,8,9,10,"-"]
            grade_value=random.choice(list_grades)
            grade=Grade(grade_value,student_id,assignment_id)
            repo_grd.add_grade(grade)
    services=Services(repo_stud, repo_asg, repo_grd)
    ui=UI(services)
    ui.actual_menu()
