from src.domain.student import Student
from src.domain.assignment import Assignment
from src.domain.grade import Grade
from texttable import Texttable
from src.errors.custum_error import ServiceError

class Services:
    def __init__(self,student_repository,assignment_repository,grade_repository):
        self.__student_repository = student_repository
        self.__assignment_repository = assignment_repository
        self.__grade_repository = grade_repository

    @property
    def repo_stud(self):
        return self.__student_repository

    @property
    def repo_asg(self):
        return self.__assignment_repository

    @property
    def repo_grade(self):
        return self.__grade_repository

    def add_student(self,student_id,name,group):
        #test done
        """
        Adds a student to the repository.
        :param student_id: the student id
        :param name: the student name
        :param group: the student group
        """
        if group not in[911,912,913,914,915,916,917,211,212,213,214,215,216,217]:
            raise ServiceError("Group is non-existent")
        for stud in self.repo_stud.get_all_students():
            if stud.get_student_id == student_id:
                raise ServiceError("Student id already exists")
        student=Student(student_id,name,group)
        self.__student_repository.add_student(student)

    def remove_student_grade(self,student_id):
        """
        If a student is removed,its grades are also removed.
        :param student_id: the student id to be deleted
        :return:
        """
        for grd in self.repo_grade.get_all_grades():
            if grd.get_student_id == student_id:
                self.__grade_repository.remove_grade(grd)

    def remove_student_name(self,student_name):
        #test done
        """
        Removes a student from the repository locating by name.
        :param student_name: the student name of the removed student
        """
        ok=0
        for stud in self.repo_stud.get_all_students():
            if stud.get_name == student_name:
                self.repo_stud.remove_student(stud)
                self.remove_student_grade(stud.get_student_id)
                ok=1
        if ok==0:
            raise ServiceError("Student name not found")

    def remove_student_id(self,student_id):
        #test done
        """
        Removes a student from the repository locating by id.
        :param student_id: the student_id of the removed student
        """
        ok=0
        for stud in self.repo_stud.get_all_students():
            if stud.get_student_id == student_id:
                self.repo_stud.remove_student(stud)
                self.remove_student_grade(stud.get_student_id)
                ok=1
        if ok==0:
            raise ServiceError("Student id not found")

    def list_students(self):
        t=Texttable()
        t.add_row(["ID", "Name", "Group"])
        for stud in self.repo_stud.get_all_students():
            t.add_row([stud.get_student_id,stud.get_name,stud.get_group])
        return t

    def update_student(self,student_id,new_name):
        #test done
        """
        Updates a student s name identified by id.
        :param student_id: the student id
        :param new_name:  the new student name
        """
        ok=0
        for stud in self.repo_stud.get_all_students():
            if stud.get_student_id == student_id:
                self.repo_stud.update_student(stud, new_name)
                ok=1
        if ok==0:
            raise ServiceError("Student id not found")

    def add_assignment(self,assignment_id,description,deadline):
        #test done
        """
        Adds an assignment to the repository.
        :param assignment_id: the assignment id
        :param description: its description
        :param deadline: its deadline
        """
        for asg in self.repo_asg.get_all_assignments():
            if asg.get_assignment_id == assignment_id:
                raise ServiceError("Assignment id already exists")
        assignment=Assignment(assignment_id,description,deadline)
        self.repo_asg.add_assignment(assignment)

    def remove_assignment_grade(self,assignment_id):
        """
        If an assignment is removed,it s grades are also removed.
        :param assignment_id:
        """
        for grd in self.repo_grade.get_all_grades():
            if grd.get_assignment_id == assignment_id:
                self.repo_grade.remove_grade(grd)

    def remove_assignment_id(self,assignment_id):
        #test done
        """
        Removes an assignment identified by id from the repository.
        :param assignment_id: the assignment id of the removed assignment
        """
        ok=0
        for asg in self.repo_asg.get_all_assignments():
            if asg.get_assignment_id == assignment_id:
                self.repo_asg.remove_assignment(asg)
                ok=1
        if ok==0:
            raise ServiceError("Assignment id not found")

    def update_assignment(self,assignment_id,deadline):
        #test done
        ok=0
        for asg in self.repo_asg.get_all_assignments():
            if asg.get_assignment_id == assignment_id:
                self.repo_asg.update_assignment(asg, deadline)
                ok=1
        if ok==0:
            raise ServiceError("Assignment id not found")

    def list_assignments(self):
        t=Texttable()
        t.add_row(["ID", "Description", "Deadline"])
        for asg in self.repo_asg.get_all_assignments():
            t.add_row([asg.get_assignment_id,asg.get_description,asg.get_deadline])
        return t

    def search_std(self,student_id):
        #test done
        """
        Verify if student_id exists
        :param student_id: student id to be searched
        :return: 1 if found, 0 if not
        """
        for stud in self.repo_stud.get_all_students():
            if stud.get_student_id == student_id:
                return 1
        return 0

    def search_assignment(self,assignment_id):
        #test done
        """
        Verify if assignment_id exists
        :param assignment_id: assignment id to be searched
        :return: 1 if found, 0 if not
        """
        for asg in self.repo_asg.get_all_assignments():
            if asg.get_assignment_id == assignment_id:
                return 1
        return 0

    def give_student(self,student_id,assignment_id):
        #test done
        """
        Gives a student an assignment.
        :param student_id: the student id of the student
        :param assignment_id: the assignment id to be given
        """
        if self.search_std(student_id)==0:
            raise ServiceError("Student not found")
        if self.search_assignment(assignment_id)==0:
            raise ServiceError("Assignment not found")
        for grd in self.repo_grade.get_all_grades():
            if grd.get_student_id == student_id and grd.get_assignment_id == assignment_id:
                raise ServiceError("Student already has this assignment")
        grade=Grade("-",student_id,assignment_id,)
        self.repo_grade.add_grade(grade)

    def search_group(self,group):
        #test done
        """
        Verify if group exists
        :param group: group to be searched
        :return: 1 if found, 0 if not
        """
        for stud in self.repo_stud.get_all_students():
            if stud.get_group == group:
                return 1
        return 0

    def verify_assignment(self,student_id,assignment_id):
        #test done
        """
        Verify if a student is already assigned an assignment.
        :param student_id:
        :param assignment_id:
        :return:1 if not,0 if already assigned
        """
        for grd in self.repo_grade.get_all_grades():
            if grd.get_student_id == student_id and grd.get_assignment_id == assignment_id:
                return 0
        return 1

    def give_group(self,group,assignment_id):
        """
        Give a group an assignment.
        :param group:
        :param assignment_id:
        """
        if self.search_group(group)==0:
            raise ServiceError("Group not found")
        if self.search_assignment(assignment_id)==0:
            raise ServiceError("Assignment not found")
        for std in self.repo_stud.get_all_students():
            if std.get_group == group:
                if self.verify_assignment(std.get_student_id,assignment_id):
                    grade = Grade("-", std.get_student_id, assignment_id)
                    self.repo_grade.add_grade(grade)

    def list_grades(self):
        t=Texttable()
        t.add_row(["Grade","Student ID","Assignment ID"])
        for grd in self.repo_grade.get_all_grades():
            t.add_row([grd.get_grade_value,grd.get_student_id,grd.get_assignment_id])
        return t

    def list_assignments_one_student(self,student_id):
        t=Texttable()
        l=[]
        t.add_row(["Assignment ID"])
        for grd in self.repo_grade.get_all_grades():
            if grd.get_student_id == student_id and grd.get_grade_value=="-":
                t.add_row([grd.get_assignment_id])
                l.append(grd.get_assignment_id)
        return t,l

    def grade(self,assignment_id,student_id,grade_value):
        #test done
        """
        Grades a student s assignment.
        :param assignment_id: the assignment that is being graded
        :param student_id: the student that is being graded
        :param grade_value: the grade value
        """
        for grd in self.repo_grade.get_all_grades():
            if grd.get_student_id == student_id and grd.get_assignment_id == assignment_id:
                grd.set_grade_value(grade_value)



