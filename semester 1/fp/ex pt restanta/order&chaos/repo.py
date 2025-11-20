from domain import Board
class GameRepo:
    def __init__(self, file_name,opt):
        self.__filename = file_name
        self.__board = self.load(opt)

    @property
    def get_file_name(self):
        return self.__filename

    @property
    def get_board(self):
        return self.__board

    def load(self,opt):
        board = Board()
        if opt==2:
            try:
                with open(self.__filename, "r") as f:
                    lines = f.readlines()
                    for line in lines:
                        move = line.strip().split(',')
                        board[int(move[0])][int(move[1])]= move[2]
            except FileNotFoundError:
                pass
        return board

    def save(self):
        with open(self.__filename, "w") as f:
            for i in range(6):
                for j in range(6):
                    if self.get_board[i][j] != ' ':
                        f.write(f"{i},{j},{self.get_board[i][j]}\n")

    def place(self, x, y, piece):
        self.__board[x][y] = piece
        self.save()
