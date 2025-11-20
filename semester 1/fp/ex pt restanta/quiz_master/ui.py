
class Ui:
    def __init__(self,service):
        self.__service = service

    @property
    def service(self):
        return self.__service

    def start(self):
        instr=['add','create','start','exit']
        while True:
            print("1. Add question : add<id>;<text>;<answer1>,<answer2>,<answer3>;<correctAnswer>;<difficulty>")
            print("2. Create quiz : create<difficulty><number_of_questions><filename>")
            print("3. Start quiz : start<filename>")
            print("4. Exit")
            cmd = input(">>>")
            if ' ' not in cmd:
                cmd=cmd.split(';')
            else:
                cmd=cmd.split(' ')
            if cmd[0] not in instr:
                print("Invalid command")
                continue
            if cmd[0]=='add':
                self.ui_add(cmd)
            elif cmd[0]=='create':
                self.ui_create(cmd)
            elif cmd[0]=='start':
                self.ui_start(cmd)
            elif cmd[0]=='exit':
                return
    def ui_add(self,cmd):
        try:
            if len(cmd)!=6:
                raise ValueError("Invalid add command(add;<id>;<text>;<answer1>,<answer2>,<answer3>;<correctAnswer>;<difficulty>)")
            id = cmd[1]
            text = cmd[2]
            answers = cmd[3].split(',')
            correctAnswer = cmd[4]
            if correctAnswer not in answers:
                raise ValueError("Invalid correct answer")
            difficulty = cmd[5]
            if difficulty not in ['easy','medium','hard']:
                raise ValueError("Invalid difficulty")
            self.service.add_question(id,text,answers,correctAnswer,difficulty)
        except Exception as e:
            print(e)

    def ui_create(self,cmd):
        try:
            if len(cmd)!=4:
                raise ValueError("Invalid create command(create<difficulty><number_of_questions><filename>)")
            difficulty = cmd[1]
            if difficulty not in ['easy','medium','hard']:
                raise ValueError("Invalid difficulty")
            number_of_questions = int(cmd[2])
            filename = cmd[3]
            self.service.create_quiz(difficulty,number_of_questions,filename)
        except Exception as e:
            print(e)

    def ui_start(self,cmd):
        try:
            if len(cmd)!=2:
                raise ValueError("Invalid start command(start<filename>)")
            filename = cmd[1]
            with open(filename,"r") as f:
                lines = f.readlines()
                score = 0
                for line in lines:
                    parts = line.strip().split(";")
                    id = parts[0]
                    text = parts[1]
                    answers = parts[2].split(",")
                    correctAnswer = parts[3]
                    difficulty = parts[4]
                    print(id,text,"Difficulty:",difficulty)
                    for i in range(3):
                        print(f"{i+1}. {answers[i]}")
                    answer = input("Enter answer: ")
                    if answer not in ['1','2','3']:
                        print("Invalid answer")
                        continue
                    if answers[int(answer)-1]==correctAnswer:
                        if difficulty=='easy':
                            score+=1
                        elif difficulty=='medium':
                            score+=2
                        elif difficulty=='hard':
                            score+=3
                print(f"Score: {score}")
        except Exception as e:
            print(e)
