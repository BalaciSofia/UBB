class UI:
    def __init__(self, services):
        self.__services = services

    @property
    def services(self):
        return self.__services

    def print_menu(self):
        while True:
            print("1. Add student")
            print("2. Display students")
            print("3. Remove students by group")
            print("4. Undo")
            print("0. Exit")

            choice=input(">>>")
            if choice == '1':
                self.add_student()
            elif choice == '2':
                self.display_students()
            elif choice == '3':
                while True:
                    group = input("Group: ")
                    try:
                        group = int(group)
                        break
                    except ValueError:
                        print("Invalid input.")
                if not self.services.check_group(group):
                    print("No students in group")
                else:
                    self.services.remove_students_by_group(group)
            elif choice == '4':
                if not self.services.history:
                    print("No more undos")
                else:
                    self.services.undo()
            elif choice == '0':
                break
            else:
                print("Invalid choice")

    def add_student(self):
        id = int(input("ID: "))
        name = input("Name: ")
        group = int(input("Group: "))
        try:
            self.services.add_student(id, name, group)
        except ValueError as ve:
            print(ve)

    def display_students(self):
        self.services.display_students()

    def remove_students_by_group(self):
        group = int(input("Group: "))
        self.services.remove_students_by_group(group)
