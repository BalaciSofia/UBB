from datetime import datetime

from src.domain import Reservation, Room

class ReservationRepo:
    def __init__(self, filename):
        self.__filename = filename
        self.__reservations = []

    def get_reservations(self):
        return self.__reservations

    def load(self):
        reservations = []
        with open(self.__filename, 'r') as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                parts = line.split(',')
                id = int(parts[0])
                room_nb = int(parts[1])
                name = parts[2]
                no_guests = int(parts[3])

                date = parts[4].split('-')
                arrival_date = datetime(int(date[0]), int(date[1]), int(date[2]))

                date = parts[5].split('-')
                departure_date = datetime(int(date[0]), int(date[1]), int(date[2]))

                res = Reservation(id, room_nb, name, no_guests, arrival_date, departure_date)
                reservations.append(res)

        self.__reservations = reservations

    def save_reservation(self, rez):
        self.__reservations.append(rez)
        self.save()

    def save(self):
        with open(self.__filename, 'w') as file:
            for rez in self.__reservations:
                file.write(f"{rez.get_id},{rez.get_room},{rez.get_name},{rez.get_number_guests},{rez.get_arrival_date},{rez.get_departure_date}\n")
        self.load()

class RoomRepo:
    def __init__(self, filename):
        self.__filename = filename
        self.__rooms = self.load()

    @property
    def get_rooms(self):
        return self.__rooms

    def load(self):
        rooms = []
        with open(self.__filename, 'r') as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                parts = line.split(',')
                number = int(parts[0])
                room_type = parts[1]
                if room_type == "single":
                    room = Room(number, 'a')
                elif room_type == "double":
                    room = Room(number, 'b')
                else:
                    room = Room(number, 'c')
                rooms.append(room)
        return rooms
