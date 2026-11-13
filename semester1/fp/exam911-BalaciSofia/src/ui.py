from datetime import datetime
class Ui:

    def __init__(self, service):
        self.__service = service

    @property
    def service(self):
        return self.__service

    def show_menu(self):
        print("Option 1: Create a reservation")
        print("Option 2: Delete reservation")
        print("Option 3: Exit")

    def main_loop(self):
        self.service.generate()
        while True:
            self.show_menu()
            option = input(">>> ")

            # Convert option to integer
            try:
                option = int(option)
            except ValueError:
                print("Invalid option, please enter a number.")
                continue

            if option == 1:
                self.ui_add_reservation()
            elif option == 2:
                self.ui_delete_reservation()
            elif option == 3:
                print("Exiting...")
                break  # Exit the loop
            else:
                print("Invalid option, please try again.")

    def ui_add_reservation(self):
        arrival_date = input("Enter arrival date (month/day): ")
        departure_date = input("Enter departure date (month/day): ")

        try:
            arrival_month, arrival_day = map(int, arrival_date.split('/'))
            departure_month, departure_day = map(int, departure_date.split('/'))

            arrival_date = datetime(2025, arrival_month, arrival_day)
            departure_date = datetime(2025, departure_month, departure_day)

            available_rooms = self.service.get_available_rooms(arrival_date, departure_date)

            if not available_rooms:
                print("No rooms available for the selected dates.")
                return

            print("Available rooms:")
            for idx, room in enumerate(available_rooms, 1):
                print(f"{idx}. Room {room.get_number()} ({room.get_type()} - {room.get_capacity()} guests)")

            room_choice = input(f"Choose a room (1-{len(available_rooms)}): ")

            try:
                room_choice = int(room_choice)
                if 1 <= room_choice <= len(available_rooms):
                    selected_room = available_rooms[room_choice - 1]
                    name = input("Enter guest name: ")

                    guests = selected_room.get_capacity()

                    self.service.add_reservation(name, selected_room.get_type(), guests, arrival_date,
                                                 departure_date)
                    print(f"Reservation for {name} in room {selected_room.get_number()} added successfully!")
                else:
                    print("Invalid room choice.")
            except ValueError:
                print("Invalid input. Please enter a valid number.")
        except ValueError:
            print("Invalid date format. Please enter the dates in 'month/day' format.")

    def ui_delete_reservation(self):
        reservation_id = input("Enter the reservation ID to delete: ")
        try:
            reservation_id = int(reservation_id)
            success = self.service.delete_reservation(reservation_id)
            if success:
                print(f"Reservation {reservation_id} deleted successfully.")
            else:
                print(f"Reservation {reservation_id} not found.")
        except ValueError:
            print("Invalid reservation ID. Please enter a number.")

