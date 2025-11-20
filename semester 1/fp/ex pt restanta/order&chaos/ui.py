
class Ui:
    def __init__(self,service):
        self.__service = service

    @property
    def service(self):
        return self.__service

    def game(self):
        print(self.service.print_board())
        while True:
            print("Order turn:")
            self.order_turn()
            print(self.service.print_board())
            if self.service.repo.get_board.check_win_order():
                print("Order wins!")
                break
            print("Chaos turn:")
            self.chaos_turn()
            print(self.service.print_board())
            if self.service.repo.get_board.check_win_chaos():
                print("Chaos wins!")
                break

    def order_turn(self):
        while True:
            try:
                piece = input("piece: ")
                if piece not in ['X', 'O']:
                    raise ValueError("invalid piece(X/O)")
                x = int(input("x: "))
                y = int(input("y: "))
                if self.service.validate(x, y):
                    self.service.repo.place(x, y, piece)
                    break
            except Exception as e:
                print(e)

    def chaos_turn(self):
        self.service.chaos_move()

