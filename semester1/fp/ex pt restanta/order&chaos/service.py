from faker.generator import random
from texttable import Texttable

class Service:
    def __init__(self,repo):
        self.__repo = repo

    @property
    def repo(self):
        return self.__repo

    def print_board(self):
        t=Texttable()
        for i in range(6):
            row = []
            for j in range(6):
                row.append(self.repo.get_board[i][j])
            t.add_row(row)
        return t.draw()

    def validate(self,x,y):
        if x<0 or x>5 or y<0 or y>5:
            raise ValueError("coordinates out of bounds[0,5]")
        if self.repo.get_board[x][y] != ' ':
            raise ValueError("cell already occupied")
        return True

    def place(self,x,y,piece):
        self.repo.place(x,y,piece)

    def best_move(self):
        # block win
        for i in range(6):
            for j in range(6):
                if self.repo.get_board[i][j] == ' ':
                    self.repo.get_board[i][j] = 'O'
                    if self.repo.get_board.check_win_order():
                        return i, j, 'X'
                    self.repo.get_board[i][j] = ' '
        for i in range(6):
            for j in range(6):
                if self.repo.get_board[i][j] == ' ':
                    self.repo.get_board[i][j] = 'X'
                    if self.repo.get_board.check_win_order():
                        return i, j, 'O'
                    self.repo.get_board[i][j] = ' '
        # random move
        for i in range(6):
            for j in range(6):
                if self.repo.get_board[i][j] == ' ':
                    return i, j, random.choice(['X', 'O'])

    def chaos_move(self):
        move=self.best_move()
        self.repo.place(move[0],move[1],move[2])
