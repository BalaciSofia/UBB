
class Assignment:
    def __init__(self,id,name,solution):
        self.__id = id
        self.__name = name
        self.__solution = solution

    @property
    def get_id(self):
        return self.__id

    @property
    def get_name(self):
        return self.__name

    @property
    def get_solution(self):
        return self.__solution