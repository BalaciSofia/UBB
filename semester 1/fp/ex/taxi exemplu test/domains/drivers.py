class Driver:
    def __init__(self, id, name):
        self.__id = id
        self.__name = name

    @property
    def get_id(self):
        return self.__id

    @property
    def get_name(self):
        return self.__name