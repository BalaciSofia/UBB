from domain import Board
class GameRepo:
    def __init__(self,filename,option):
        self.__filename=filename
        self.__game=self.load(option)

    @property
    def get_filename(self):
        return self.__filename

    @property
    def get_game(self):
        return self.__game

    def load(self,opt):
        if opt==1:
            return Board()
        else:
            game = Board()
            with open(self.get_filename, 'r') as file:
                lines = file.readlines()
                turn = 0
                index=0
                for line in lines:
                    if index!=0:
                        line = line.strip()
                        parts = line.split(',')
                        if turn == 0:
                            game.place(int(parts[0]), int(parts[1]), 'X')
                        else:
                            game.place(int(parts[0]), int(parts[1]), 'O')
                        turn = (turn + 1) % 2
                    else:
                        index+=1
            return game

    def place(self,a,b,piece):
        self.__game.place(a,b,piece)
        self.save(a,b)

    def half_place(self,a,b,piece):
        self.__game.place(a,b,piece)

    def remove(self,a,b):
        self.__game.place(a,b,' ')

    def modify(self,a,b,c,d,piece):
        self.__game.place(c,d,piece)
        self.__game.place(a,b,' ')

        with open(self.get_filename, 'r') as file:
            lines = file.readlines()

        with open(self.get_filename, 'w') as file:
            for line in lines:
                if line.strip() == str(a) + ',' + str(b):
                    file.write(str(c) +','+ str(d) +'\n')
                else:
                    file.write(line)

    def save(self,a,b):
        with open(self.__filename, 'a') as file:
            file.write(str(a) + ',' + str(b) + '\n')

