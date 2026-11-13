
class Ui:
    def __init__(self,service):
        self.__service=service

    @property
    def service(self):
        return self.__service

    def start(self):
        direction_A=None
        end_position=self.service.repo.get_exit_position()
        while True:
            self.service.print_lab()
            minotaur_position = self.service.repo.get_minotaur_position()
            print("Move Ariadne with u,r,d,l,m,m [value]")
            a=input(">>>")
            while self.validate_move(a,direction_A)==False:
                a=input(">>>")
            if len(a)==1 and a in ["u","r","d","l"]:
                direction_A=a
            if self.service.ariadne_win(end_position)==True:
                print("Ariadne wins")
                break
            if self.service.minotaur_win(minotaur_position)==True:
                print("Minotaur wins")
                break
        self.service.print_lab()

    def validate_move(self, move, direction):
        try:
            if len(move) == 1:
                if move not in ["u", "r", "d", "l", "m"]:
                    raise ValueError("Invalid command.")
                if move == "m":
                    if direction is None:
                        raise ValueError("Invalid command. No previous direction set.")
                    else:
                        self.service.move_ariadne(direction)
                else:
                    direction = move
                    self.service.move_ariadne(direction)
                return direction

            elif len(move.split()) == 2:
                command, value = move.split()
                if command != "m":
                    raise ValueError("Invalid command.")
                if direction is None:
                    raise ValueError("Invalid command. No previous direction set.")
                index = int(value)
                self.service.move_ariadne_more(direction, index)
                return direction

            else:
                raise ValueError("Invalid command.")
        except ValueError as ve:
            print(ve)
            return False

