from random import random
from faker.generator import random
from repo import QuestionRepo
from service import Service
from ui import Ui

def load_questions(filename):
    with open(filename, 'r') as file:
        if len(file.read()) == 0:
            with open(filename, 'w') as file:
                for _ in range(100):
                    id = random.randint(1, 1000)
                    text = random.words(10)
                    answers = [random.words(5) for _ in range(4)]
                    correctAnswer = random.choice(answers)
                    difficulty = random.choice(['easy', 'medium', 'hard'])
                    file.write(f"{id};{text};{','.join(answers)};{correctAnswer};{difficulty}\n")
        else:
            return

def main():
    #load_questions("questions.txt")
    q_repo=QuestionRepo("questions.txt")
    service = Service(q_repo)
    ui=Ui(service)
    ui.start()

if __name__ == "__main__":
    main()