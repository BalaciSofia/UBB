from src.domain.domain import Labyrinth

class Repository:
    def __init__(self, filename):
        self.__filename=filename
        self.__labyrinth = self.load_labyrinth(filename)

    def load_labyrinth(self, filename):
        labyrinth=[]
        with open(filename, "r") as f:
            for line in f:
                line = line.strip()
                labyrinth.append([int(x) for x in line])
        return Labyrinth(labyrinth)

    def __str__(self):
        return str(self.__labyrinth)

    def minotaur_win(self, minotaur_pos):
        if self.__labyrinth.minotaur_win(minotaur_pos):
            return True

    def ariadne_win(self,end_pos):
        if self.__labyrinth.ariadne_win(end_pos):
            return True

    def change_ariadne_direction(self, direction):
        self.__labyrinth.change_ariadne_direction(direction)

    def get_minotaur_position(self):
        return self.__labyrinth.get_minotaur_position()

    def get_exit_position(self):
        return self.__labyrinth.get_exit_position()





