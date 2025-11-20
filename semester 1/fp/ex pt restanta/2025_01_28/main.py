
class Ui:
    def __init__(self,service):
        self.__service = service

    @property
    def service(self):
        return self.__service

    def game(self,player_piece,computer_piece):
        if self.service.how_many()<4:
            self.placement(player_piece,computer_piece)
        if not self.service.repo.get_game.check_win(player_piece) and not self.service.repo.get_game.check_win(computer_piece):
            self.movement(player_piece,computer_piece)
        else:
            print("Game over!")

    def new_game(self):
        # choosing piece
        print("1. X")
        print("2. O")
        piece = int(input("Choose your piece: "))
        if piece == 1:
            player_piece = 'X'
            computer_piece = 'O'
        elif piece == 2:
            player_piece = 'O'
            computer_piece = 'X'
        else:
            print("Invalid option")
            return
        with open(self.service.repo.get_filename, 'w') as file:
            file.write(player_piece + ',' + computer_piece + '\n')
        self.game(player_piece,computer_piece)

    def load_game(self):
        with open(self.service.repo.get_filename, 'r') as file:
            lines = file.readlines()
            lines[0] = lines[0].strip()
            lines[0] = lines[0].split(',')
            player_piece = lines[0][0]
            computer_piece = lines[0][1]
        if self.service.repo.get_game.check_win(player_piece) == False and self.service.repo.get_game.check_win(computer_piece) == False:
            self.game(player_piece,computer_piece)
        else:
            print(self.service.print_board())
            print("Game is already over!")

    def placement(self,player_piece,computer_piece):
        print("placement phase:")
        if player_piece == 'X':
            index=0
            print(self.service.print_board())
            while True:
                print("player turn :")
                while True:
                    try:
                        a = input("Enter row: ")
                        b = input("Enter column: ")
                        if self.service.validate(a, b):
                            self.service.place(int(a), int(b), player_piece)
                            if self.service.repo.get_game.check_win(player_piece):
                                print(self.service.print_board())
                                print("You won!")
                                break
                            break
                    except ValueError as ve:
                        print(ve)
                print(self.service.print_board())
                print("computer turn :")
                self.service.computer_move(computer_piece, player_piece)
                print(self.service.print_board())
                if self.service.repo.get_game.check_win(computer_piece):
                    print("Computer won!")
                    break
                index=index+1
                if index==4:
                    break
        else:
            print(self.service.print_board())
            index=0
            while True:
                print("computer turn :")
                self.service.computer_move(computer_piece, player_piece)
                print(self.service.print_board())
                if self.service.repo.get_game.check_win(computer_piece):
                    print("Computer won!")
                    break
                print("player turn :")
                while True:
                    try:
                        a = input("Enter row: ")
                        b = input("Enter column: ")
                        if self.service.validate(a, b):
                            self.service.place(int(a), int(b), player_piece)
                            if self.service.repo.get_game.check_win(player_piece):
                                print(self.service.print_board())
                                print("You won!")
                                break
                            break
                    except ValueError as ve:
                        print(ve)
                print(self.service.print_board())
                index=index+1
                if index==4:
                    break

    def movement(self,player_piece,computer_piece):
        print("movement phase:")
        print(self.service.print_board())
        space=self.service.find_space()
        while True:
            print("player turn:")
            while True:
                try:
                    print("enter coordinates of the piece you want to move:")
                    a = input("Enter row: ")
                    b = input("Enter column: ")
                    if self.service.validate_movement(a,b,player_piece):
                        self.service.replace(int(a),int(b),space[0],space[1],player_piece)
                        space=(int(a),int(b))
                        if self.service.repo.get_game.check_win(player_piece):
                            print(self.service.print_board())
                            print("You won!")
                            return
                        break
                except ValueError as ve:
                    print(ve)
            print(self.service.print_board())
            print("computer turn:")
            self.service.computer_move2(computer_piece)
            space=self.service.find_space()
            print(self.service.print_board())
            if self.service.repo.get_game.check_win(computer_piece):
                print("Computer won!")
                break
