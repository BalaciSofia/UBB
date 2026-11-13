from src.domain import Reservation
from faker import Faker
from datetime import datetime
class Service:
    def __init__(self,room_repo,rez_repo):
        self.__room_repo=room_repo
        self.__rez_repo=rez_repo

    @property
    def room_repo(self):
        return self.__room_repo

    @property
    def rez_repo(self):
        return self.__rez_repo

    def generate(self):
        rooms = self.room_repo.get_rooms
        fake = Faker()
        room_capacity = {
            "a": 1,  # Room type A is for 1 guest
            "b": 2,  # Room type B for 2 guests
            "c": 4  # Room type C for 4 guests
        }
        l=[1,2,3,4,5]
        reservation_id = 1
        for i in range(1000):
            name = fake.name()
            date1 = fake.date_time_between(start_date=datetime(2025, 1, 1), end_date=datetime(2025, 12, 31))
            date2 = fake.date_time_between(start_date=datetime(2025, 1, 1), end_date=datetime(2025, 12, 31))
            if date1 > date2:
                date1, date2 = date2, date1
            room=1
            guests =1
            reservation = Reservation(reservation_id, room, name, guests, date1, date2)
            self.rez_repo.save_reservation(reservation)
            reservation_id+=1

    def get_available_rooms(self, arrival_date, departure_date):
        """
        Returns a list of rooms available between the arrival and departure dates.
        """
        available_rooms = []
        rooms = self.room_repo.get_rooms()
        for room in rooms:
            is_available = True
            for rez in self.rez_repo.get_reservations():
                if rez.get_room() == room.get_number():
                    if not (rez.get_departure_date <= arrival_date or rez.get_arrival_date >= departure_date):
                        is_available = False
                        break
            if is_available:
                available_rooms.append(room)

        return available_rooms

    def add_reservation(self, name, room_type, guests, arrival_date, departure_date):
        """
        Adds a new reservation by first checking for availability and then saving it.
        """
        room = self.get_room_by_type(room_type)

        if room:
            reservation_id = len(self.rez_repo.get_reservations()) + 1
            reservation = Reservation(reservation_id, room.get_number(), name, guests, arrival_date, departure_date)
            self.rez_repo.save_reservation(reservation)
        else:
            print(f"No rooms of type {room_type} available.")

    def delete_reservation(self, reservation_id):
        """
        Deletes a reservation by its ID.
        """
        for rez in self.rez_repo.get_reservations():
            if rez.get_id() == reservation_id:
                self.rez_repo.get_reservations().remove(rez)
                self.rez_repo.save()
                return True
        return False

    def get_room_by_type(self, room_type):
        """
        Returns the room object that matches the specified room type.
        """
        for room in self.room_repo.get_rooms():
            if room.get_type() == room_type:
                return room
        return None


