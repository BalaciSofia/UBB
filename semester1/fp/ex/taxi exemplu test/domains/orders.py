class Order:
    def __init__(self, id,distance):
        self.__id = id
        self.__distance = distance

    @property
    def get_id(self):
        return self.__id

    @property
    def get_distance(self):
        return self.__distance