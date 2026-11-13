
class Player:
    def __init__(self,id,name,strength):
        self.__id = id
        self.__name = name
        self.__strength = strength

    @property
    def get_id(self):
        return self.__id
    @property
    def get_name(self):
        return self.__name
    @property
    def get_strength(self):
        return self.__strength
