
class Service:
    def __init__(self,repo):
        self.__repo=repo

    @property
    def repo(self):
        return self.__repo

    def print_lab(self):
        print(self.__repo)

    def move_ariadne(self,direction):
        self.repo.change_ariadne_direction(direction)

    def move_ariadne_more(self,dir,index):
        for i in range(index):
            self.repo.change_ariadne_direction(dir)

    def ariadne_win(self,end_pos):
        if self.repo.ariadne_win(end_pos):
            return True

    def minotaur_win(self,minotaur_pos):
        if self.repo.minotaur_win(minotaur_pos):
            return True

    def get_end_pos(self):
        return self.repo.get_exit_position()