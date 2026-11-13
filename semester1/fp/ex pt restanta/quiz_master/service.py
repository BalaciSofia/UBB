import random
import unittest
from domain import Question
from repo import QuestionRepo

class Service:
    def __init__(self,q_repo):
        self.__q_repo =q_repo

    @property
    def q_repo(self):
        return self.__q_repo

    def add_question(self,id,text,answers,correctAnswer,difficulty):
        self.q_repo.add_question(Question(id,text,answers,correctAnswer,difficulty))

    def enough_questions(self,difficulty,number_of_questions):
        count=0
        for q in self.q_repo.get_questions:
            if q.getDifficulty==difficulty:
                count+=1
        if count>=number_of_questions/2:
            return True
        return False

    def create_quiz(self,difficulty,number_of_questions,filename):
        """
        Create a quiz with a given difficulty and number of questions
        :param difficulty: the given difficulty
        :param number_of_questions: number of questions
        :param filename: the filename where the quiz will be saved
        """
        if not self.enough_questions(difficulty,number_of_questions):
            raise ValueError("Not enough questions")
        with open(filename, "w") as f:
            questions = []
            rest = []
            quiz = []
            for q in self.q_repo.get_questions:
                if q.getDifficulty == difficulty and len(questions) < number_of_questions / 2:
                    questions.append(q)
                else:
                    rest.append(q)
            quiz = questions
            random.shuffle(rest)
            for q in rest:
                if len(quiz) < number_of_questions:
                    quiz.append(q)
            difficulty_order = {"easy": 1, "medium": 2, "hard": 3}
            quiz.sort(key=lambda x: difficulty_order[x.getDifficulty])
            for q in quiz:
                f.write(f"{q.getId};{q.getText};{','.join(q.getAnswers)};{q.getCorrectAnswer};{q.getDifficulty}\n")




class TestService(unittest.TestCase):
    def setUp(self):
        self.q_repo = QuestionRepo("test.txt")
        self.service = Service(self.q_repo)

    def test_create_quiz(self):
        self.service.add_question("1","text1",["a","b","c"],"a","easy")
        self.service.add_question("2","text2",["a","b","c"],"a","easy")
        self.service.add_question("3","text3",["a","b","c"],"a","medium")
        self.service.add_question("4","text4",["a","b","c"],"a","medium")
        self.service.add_question("5","text5",["a","b","c"],"a","hard")
        self.service.add_question("6","text6",["a","b","c"],"a","hard")
        self.service.create_quiz("easy",4,"test_quiz.txt")
        with open("test_quiz.txt","r") as f:
            lines = f.readlines()
            self.assertEqual(len(lines),4)
            self.assertEqual(lines[0],"1;text1;a,b,c;a;easy\n")
            self.assertEqual(lines[1],"2;text2;a,b,c;a;easy\n")

        self.service.create_quiz("medium",4,"test_quiz.txt")
        with open("test_quiz.txt","r") as f:
            lines = f.readlines()
            self.assertEqual(len(lines),4)
            self.assertTrue("3;text3;a,b,c;a;medium\n" in lines)
            self.assertTrue("4;text4;a,b,c;a;medium\n" in lines)

        self.service.create_quiz("hard",4,"test_quiz.txt")
        with open("test_quiz.txt","r") as f:
            lines = f.readlines()
            self.assertEqual(len(lines),4)
            self.assertTrue("5;text5;a,b,c;a;hard\n" in lines)
            self.assertTrue("6;text6;a,b,c;a;hard\n" in lines)
        self.service.create_quiz("easy",5,"test_quiz.txt")
        with open("test_quiz.txt","r") as f:
            lines = f.readlines()
            self.assertEqual(len(lines),5)
            self.assertEqual(lines[0],"1;text1;a,b,c;a;easy\n")
            self.assertEqual(lines[1],"2;text2;a,b,c;a;easy\n")
