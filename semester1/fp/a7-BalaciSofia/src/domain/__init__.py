class Student:
    def __init__(self, id: int, name: str, group: int):
        self.__id = id
        self.__name = name
        self.__group = group

    @property
    def id(self):
        return self.__id
    @property
    def name(self):
        return self.__name
    @property
    def group(self):
        return self.__group

    def get_info(self):
        return f"Student {self.name} - id {self.id} is in group {self.group}"

