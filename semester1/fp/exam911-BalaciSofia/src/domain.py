from datetime import datetime


class Reservation:
    def __init__(self,id:int ,room_number:int,name:str,no_guests:int,arrival_date:datetime,departure_date:datetime):
        self.__id=id
        self.__room_number=room_number
        self.__name=name
        self.__no_guests=no_guests
        self.__arrival_date=arrival_date
        self.__departure_date=departure_date

    @property
    def get_id(self):
        return self.__id

    @property
    def get_room(self):
        return self.__room_number

    @property
    def get_name(self):
        return self.__name

    @property
    def get_number_guests(self):
        return self.__no_guests

    @property
    def get_arrival_date(self):
        return self.__arrival_date

    @property
    def get_departure_date(self):
        return self.__departure_date

class Room:
    def __init__(self,nb,type):
        self.__nb=nb
        self.__type=type
        #a for single
        #b for double
        #c fo family
    @property
    def get_number(self):
        return self.__nb
    @property
    def get_type(self):
        return self.__type


