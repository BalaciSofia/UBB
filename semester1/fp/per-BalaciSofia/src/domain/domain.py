from texttable import Texttable
import random

class Labyrinth:
    def __init__(self, labyrinth):
        self.__labyrinth = labyrinth
        self.place_ariadne()
        self.place_minotaur()

    def __str__(self):
        t = Texttable()
        # 1 is X, 0 is empty space, 9 is -
        for row in self.__labyrinth:
            row_str = []
            for cell in row:
                if cell == 1:
                    row_str.append("X")
                elif cell == 0:
                    row_str.append(" ")
                elif cell == 9:
                    row_str.append("-")
                elif cell == 2:
                    row_str.append("A")
                elif cell==3:
                    row_str.append("M")
            t.add_row(row_str)
        return t.draw()

    def place_minotaur(self):
        rows = len(self.__labyrinth)
        cols = len(self.__labyrinth[0])
        for col in range(cols-1,-1,-1):  # Iterate from right to left
            valid_rows = [row for row in range(rows) if self.__labyrinth[row][col] != 1 and self.__labyrinth[row][col] != 9]
            if valid_rows:
                m_row = random.choice(valid_rows)
                self.__labyrinth[m_row][col] = 3
                return

    def place_ariadne(self):
        rows = len(self.__labyrinth)
        cols = len(self.__labyrinth[0])
        for col in range(cols):
            valid_rows = [row for row in range(rows) if self.__labyrinth[row][col] != 1]
            if valid_rows:
                a_row = random.choice(valid_rows)
                self.__labyrinth[a_row][col] = 2
                return

    def get_ariadne_position(self):
        for i in range(len(self.__labyrinth)):
            for j in range(len(self.__labyrinth[i])):
                if self.__labyrinth[i][j]==2:
                    return i,j

    def get_minotaur_position(self):
        for i in range(len(self.__labyrinth)):
            for j in range(len(self.__labyrinth[i])):
                if self.__labyrinth[i][j]==3:
                    return i,j

    def get_exit_position(self):
        for i in range(len(self.__labyrinth)):
            for j in range(len(self.__labyrinth[i])):
                if self.__labyrinth[i][j]==9:
                    return i,j

    def change_ariadne_direction(self, dir):
        a_row, a_col = self.get_ariadne_position()
        rows = len(self.__labyrinth[0])
        cols = len(self.__labyrinth[0])

        if dir == "u" and a_row > 0 and self.__labyrinth[a_row - 1][a_col] != 1:
            self.__labyrinth[a_row][a_col] = 0
            self.__labyrinth[a_row - 1][a_col] = 2
        elif dir == "d" and a_row < rows - 1 and self.__labyrinth[a_row + 1][a_col] != 1:
            self.__labyrinth[a_row][a_col] = 0
            self.__labyrinth[a_row + 1][a_col] = 2
        elif dir == "l" and a_col > 0 and self.__labyrinth[a_row][a_col - 1] != 1:
            self.__labyrinth[a_row][a_col] = 0
            self.__labyrinth[a_row][a_col - 1] = 2
        elif dir == "r" and a_col < cols - 1 and self.__labyrinth[a_row][a_col + 1] != 1:
            self.__labyrinth[a_row][a_col] = 0
            self.__labyrinth[a_row][a_col + 1] = 2

    def ariadne_win(self,pos):
        if self.get_ariadne_position()==pos:
            return True

    def minotaur_win(self,pos):
        if self.get_ariadne_position()==pos:
            return True


