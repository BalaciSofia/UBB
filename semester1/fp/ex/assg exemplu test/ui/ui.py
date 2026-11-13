
class Ui:
    def __init__(self,service):
        self.__service = service

    @property
    def get_service(self):
        return self.__service

    def show_menu(self):
        print("1.Display assignments")
        print("2.Add assignment")
        print("3.Display assignments sorted bu id")
        print("4.Dishonesty check")
        print("5.Exit")

    def main_loop(self):
        while True:
            self.show_menu()
            option=input("Choose an option:")
            if option=="1":
                self.ui_display_assignments()
            elif option=="2":
                self.ui_add_assignment()
            elif option=="3":
                self.ui_display_assignments_sorted_by_id()
            elif option=="4":
                self.ui_dishonesty_check()
            elif option=="5":
                print("Exiting...")
                break
            else:
                print("Invalid option.")


    def ui_display_assignments(self):
        for asg in self.get_service.get_repo.get_assignments:
            print(f'ID:{asg.get_id}-Name:{asg.get_name}-Solution{asg.get_solution}')

    def ui_add_assignment(self):
        id = int(input("Enter assignment id:"))
        name = input("Enter assignment name:")
        solution = input("Enter assignment solution:")
        try:
            self.get_service.add_assignment(id,name,solution)
        except Exception as e:
            print(e)

    def ui_display_assignments_sorted_by_id(self):
        assignments=self.get_service.sort_by_id()
        for asg in assignments:
            print(f'ID:{asg.get_id}-Name:{asg.get_name}-Solution{asg.get_solution}')

    def ui_dishonesty_check(self):
        list_dishonesty=self.get_service.dishonesty_check()
        for i in list_dishonesty:
            print(f'{i[0]} --> {i[2]}% of {i[1]}  solution')