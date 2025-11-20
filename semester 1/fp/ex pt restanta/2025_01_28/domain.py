
class Board:
    def __init__(self):
        self.__board=[[' ' for _ in range(3)]for _ in range(3)]

    @property
    def get_board(self):
        return self.__board

    def check_win(self,piece):
        for i in range(3):
            if self.__board[i][0]==self.__board[i][1]==self.__board[i][2]==piece:
                return True
            if self.__board[0][i]==self.__board[1][i]==self.__board[2][i]==piece:
                return True
        if self.__board[0][0]==self.__board[1][1]==self.__board[2][2]==piece:
            return True
        if self.__board[0][2]==self.__board[1][1]==self.__board[2][0]==piece:
            return True
        return False

    def place(self,a,b,piece):
        self.get_board[a][b]=piece
