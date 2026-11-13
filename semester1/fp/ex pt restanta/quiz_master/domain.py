
class Question:
    def __init__(self,id:str,text:str,answers:[],correctAnswer:str,difficulty:str):
        self.__id = id
        self.__text = text
        self.__answer = answers
        self.__correctAnswer = correctAnswer
        self.__difficulty = difficulty

    @property
    def getId(self):
        return self.__id

    @property
    def getText(self):
        return self.__text

    @property
    def getAnswers(self):
        return self.__answer

    @property
    def getCorrectAnswer(self):
        return self.__correctAnswer

    @property
    def getDifficulty(self):
        return self.__difficulty