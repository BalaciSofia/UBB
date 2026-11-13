from datetime import datetime
from src.errors.custum_error import IdNotInteger
class UI:
    def __init__(self,services):
        self.__services = services

    @property
    def get_services(self):
        return self.__services

    def actual_menu(self):
        options={
            "1": self.ui_add_stud,
            "2": self.ui_remove_stud,
            "3": self.ui_list_stud,
            "4": self.ui_update_stud,
            "5": self.ui_add_asg,
            "6": self.ui_remove_asg,
            "7": self.ui_list_asg,
            "8": self.ui_update_asg,
            "9": self.ui_give_stud,
            "a": self.ui_give_group,
            "b": self.ui_grade,
            "c": self.ui_list_grades,
        }
        while True:
            print("\n1: Add a student               5: Add an assignment                  9: Give assignment to a student")
            print("2: Remove a student            6: Remove an assignment               a: Give assignment to a group")
            print("3: List all students           7: List all assignments               b: Grade an assignment")
            print("4: Update a student's name     8: Update an assignment's deadline    c: List grades")
            print("\nq: Quit\n")
            option = input(">>>")
            if option in options:
                options[option]()
            elif option == "q":
                print("Thank you!")
                break
            else:
                print("Invalid option. Please try again.")
                continue

    def ui_add_stud(self):
        while True:
            try:
                try:
                    student_id = int(input("Student ID: "))
                    break
                except ValueError:
                    print("Student ID must be an integer. Please try again.")
            except IdNotInteger as e:
                print(e)

        while True:
            try:
                group = int(input("Student Group: "))
                break
            except ValueError:
                print("Student Group must be an integer. Please try again.")
        name = input("Student Name: ")
        try:
            self.get_services.add_student(student_id, name, group)
            print("Student added successfully!")
        except Exception as e:
            print(f"Error adding student: {e}")
    def ui_remove_stud(self):
        while True:
            print("1: Remove by name")
            print("2: Remove by id")
            option = input(">>>")
            if option == "1":
                name = input("Student Name: ")
                try:
                    self.get_services.remove_student_name(name)
                    print("Student removed successfully!")
                except Exception as e:
                    print(e)
                break
            elif option == "2":
                while True:
                    try:
                        try:
                            student_id = int(input("Student ID: "))
                            break
                        except ValueError:
                            print("Student ID must be an integer. Please try again.")
                    except IdNotInteger as e:
                        print(e)
                try:
                    self.get_services.remove_student_id(student_id)
                    print("Student removed successfully")
                except Exception as e:
                    print(e)
                break
            else:
                print("Invalid option. Please try again.")
    def ui_list_stud(self):
        t=self.get_services.list_students()
        print(t.draw())
    def ui_update_stud(self):
        while True:
            try:
                try:
                    student_id = int(input("Student ID you want to update: "))
                    break
                except ValueError:
                    print("Student ID must be an integer. Please try again.")
            except IdNotInteger as e:
                print(e)
        new_name=input("Student new name: ")
        try:
            self.get_services.update_student(student_id,new_name)
            print("Student updated successfully!")
        except Exception as e:
            print(e)

    def ui_add_asg(self):
        while True:
            try:
                try:
                    assignment_id = int(input("Assignment ID: "))
                    break
                except ValueError:
                    print("Assignment ID must be an integer. Please try again.")
            except IdNotInteger as e:
                print(e)
        while True:
            try:
                try:
                    date= input("Enter a deadline (format: YYYY-MM-DD): ")
                    deadline= datetime.strptime(date, "%Y-%m-%d").date()
                except ValueError:
                    raise ValueError("Deadline must be formatted as YYYY-MM-DD")
                if deadline < datetime.now().date():
                    raise ValueError("Deadline is not in the future")
                break
            except ValueError as v:
                print(v)
        description = input("Assignment Description: ")
        try:
            self.get_services.add_assignment(assignment_id,description,deadline)
        except Exception as e:
            print(f"Error adding student: {e}")
    def ui_remove_asg(self):
        while True:
            try:
                try:
                    assignment_id = int(input("Assignment ID: "))
                    break
                except ValueError:
                    print("Assignment ID must be an integer. Please try again.")
            except IdNotInteger as e:
                print(e)
        try:
            self.get_services.remove_assignment_id(assignment_id)
            print("Assigment removed successfully")
        except Exception as e:
            print(e)
    def ui_list_asg(self):
        t=self.get_services.list_assignments()
        print(t.draw())
    def ui_update_asg(self):
        while True:
            try:
                try:
                    assignment_id = int(input("Assignment ID you want to update: "))
                    break
                except ValueError:
                    print("Assignment ID must be an integer. Please try again.")
            except IdNotInteger as e:
                print(e)
        while True:
            try:
                try:
                    date = input("Enter the new deadline (format: YYYY-MM-DD): ")
                    deadline = datetime.strptime(date, "%Y-%m-%d").date()
                except ValueError:
                    raise ValueError("Deadline must be formatted as YYYY-MM-DD")
                if deadline < datetime.now().date():
                    raise ValueError("Deadline is not in the future")
                break
            except ValueError as v:
                print(v)
        try:
            self.get_services.update_assignment(assignment_id,deadline)
            print("Assigment updated successfully!")
        except Exception as e:
            print(e)

    def ui_give_stud(self):
        while True:
            try:
                try:
                    student_id = int(input("Student ID you want to give assignment to: "))
                    break
                except ValueError:
                    print("Student ID must be an integer. Please try again.")
            except IdNotInteger as e:
                print(e)
        while True:
            try:
                try:
                    assignment_id = int(input("Assignment ID you want to assign: "))
                    break
                except ValueError:
                    print("Assignment ID must be an integer. Please try again.")
            except IdNotInteger as e:
                print(e)
        try:
            self.get_services.give_student(student_id,assignment_id)
            print("Assignment given successfully!")
        except Exception as e:
            print(e)
    def ui_give_group(self):
        while True:
            try:
                try:
                    group = int(input("Group you want to give assignment to: "))
                    break
                except ValueError:
                    print("Group must be an integer. Please try again.")
            except IdNotInteger as e:
                print(e)
        while True:
            try:
                try:
                    assignment_id = int(input("Assignment ID you want to give: "))
                    break
                except ValueError:
                    print("Assignment ID must be an integer. Please try again.")
            except IdNotInteger as e:
                print(e)
        try:
            self.get_services.give_group(group,assignment_id)
            print("Assignment given successfully!")
        except Exception as e:
            print(e)
    def ui_grade(self):
        while True:
            try:
                try:
                    student_id= int(input("Student_id you want to grade: "))
                    break
                except ValueError:
                    print("Student_id must be an integer. Please try again.")
            except IdNotInteger as e:
                print(e)
        t,l=self.get_services.list_assignments_one_student(student_id)
        if not l:
            print("This student has al it s assignments graded")
        else:
            print("This student has this assignments not graded")
            print(t.draw())
            while True:
                try:
                    try:
                        assignment_id= int(input("Assignment you want to grade: "))
                        try:
                            if assignment_id not in l:
                                raise ValueError("Assignment id must be in the list")
                            else:
                                break
                        except ValueError as er:
                            print(er)
                    except ValueError:
                        print("Assignment ID must be an integer. Please try again.")
                except IdNotInteger as e:
                    print(e)

            while True:
                try:
                    try:
                        grade_value = int(input("Grade: "))
                        if grade_value < 1 or grade_value > 10:
                            raise ValueError("Grade must be between 1 and 10. Please try again.")
                        break
                    except ValueError:
                        print("Grade must be an integer between 1-10. Please try again.")
                except IdNotInteger as e:
                    print(e)
            try:
                self.get_services.grade(assignment_id,student_id,grade_value)
                print("Grade given successfully!")
            except Exception as e:
                print(e)
    def ui_list_grades(self):
        t=self.get_services.list_grades()
        print(t.draw())