
class Ui:
    def __init__(self,service):
        self.__service = service

    @property
    def get_service(self):
        return self.__service

    def print_options(self):
        print("1. Add Order")
        print("2. Display Drivers")
        print("3. Display Orders")
        print("4. Solicit income information")
        print("5. Exit")
    def main_loop(self):
        while True:
            self.print_options()
            option = input("Enter your option: ")
            if option == "1":
                self.ui_add_order()
            elif option == "2":
                self.ui_display_drivers()
            elif option == "3":
                self.ui_display_orders()
            elif option == "4":
                self.ui_display_income()
            elif option == "5":
                print("Exiting...")
                break
            else:
                print("Invalid option. Please try again.")

    def ui_add_order(self):
        try:
            print("Enter the order details:")
            id = input("Driver ID: ")
            distance = int(input("Distance: "))
            self.get_service.add_order(id, distance)
        except Exception as e:
            print(f"An error occurred: {e}")

    def ui_display_drivers(self):
        for driver in self.get_service.get_driver_repo.get_drivers:
            print(f"Driver ID: {driver.get_id}, Driver Name: {driver.get_name}")

    def ui_display_orders(self):
        for order in self.get_service.get_order_repo.get_orders:
            print(f"Driver ID: {order.get_id}, Distance: {order.get_distance}")

    def ui_display_income(self):
        id=input("Enter the driver id: ")
        income,name=self.get_service.calculate_income(id)
        print(f"Income for driver {name} with id {id} is {income}")
