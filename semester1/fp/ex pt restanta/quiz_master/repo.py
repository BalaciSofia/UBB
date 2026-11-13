from domain import Question

class QuestionRepo:
    def __init__(self,filename):
        self.__filename = filename
        self.__questions = self.load()

    @property
    def get_questions(self):
        return self.__questions

    @property
    def filename(self):
        return self.__filename

    def load(self):
        questions = []
        with open(self.filename,"r") as f:
            lines = f.readlines()
            for line in lines:
                parts = line.strip().split(";")
                id = parts[0]
                text = parts[1]
                answers = parts[2].split(",")
                correctAnswer = parts[3]
                difficulty = parts[4]
                questions.append(Question(id,text,answers,correctAnswer,difficulty))
        return questions

    def save(self):
        with open(self.filename,"w") as f:
            for q in self.get_questions:
                f.write(f"{q.getId};{q.getText};{','.join(q.getAnswers)};{q.getCorrectAnswer};{q.getDifficulty}\n")

    def add_question(self,question):
        self.get_questions.append(question)
        self.save()