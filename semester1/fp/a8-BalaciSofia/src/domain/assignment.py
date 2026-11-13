
class Assignment:
    def __init__(self,assignment_id,description,deadline):
        self.__assignment_id = assignment_id
        self.__description = description
        self.__deadline = deadline

    @property
    def get_assignment_id(self):
        return self.__assignment_id

    def set_assignment_id(self,assignment_id):
        self.__assignment_id = assignment_id

    @property
    def get_description(self):
        return self.__description

    def set_description(self,description):
        self.__description = description

    @property
    def get_deadline(self):
        return self.__deadline

    def set_deadline(self,deadline):
        self.__deadline = deadline

    def __str__(self):
        return f"assignment_id: {self.get_assignment_id}, description: {self.get_description}, deadline: {self.get_deadline}"
