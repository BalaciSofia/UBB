
class Grade:
    def __init__(self, grade_value, student_id,assignment_id):
        self.__grade_value = grade_value
        self.__student_id = student_id
        self.__assignment_id = assignment_id

    @property
    def get_assignment_id(self):
        return self.__assignment_id

    def set_assignment_id(self,assignment_id):
        self.__assignment_id = assignment_id

    @property
    def get_student_id(self):
        return self.__student_id

    def set_student_id(self,student_id):
        self.__student_id = student_id

    @property
    def get_grade_value(self):
        return self.__grade_value

    def set_grade_value(self,grade_value):
        self.__grade_value = grade_value

    def __str__(self):
        return f"assignment_id:{self.__assignment_id}, student_id:{self.__student_id}, grade_value:{self.__grade_value}"
