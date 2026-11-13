
class Student:
    def __init__(self, student_id,name,group):
        self.__student_id = student_id
        self.__name = name
        self.__group = group

    @property
    def get_student_id(self):
        return self.__student_id

    def set_student_id(self,student_id):
        self.__student_id = student_id

    @property
    def get_name(self):
        return self.__name

    def set_name(self,name):
        self.__name = name

    @property
    def get_group(self):
        return self.__group

    def set_group(self,group):
        self.__group = group

    def __str__(self):
        return f"student_id: {self.get_student_id}, name: {self.get_name}, group: {self.get_group}"
