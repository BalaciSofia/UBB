
class Board:
    def __init__(self):
        self.__board = [[' ' for i in range(6)] for j in range(6)]

    @property
    def get_board(self):
        return self.__board

    def __getitem__(self, index):
        return self.__board[index]

    def __setitem__(self, x, y, piece):
        self.__board[x][y] = piece

    def check_win_order(self):
        board = self.__board

        # Check rows and columns
        for i in range(6):
            if all(board[i][j] == board[i][0] != ' ' for j in range(1, 5)):
                return True
            if all(board[j][i] == board[0][i] != ' ' for j in range(1, 5)):
                return True
            if all(board[i][j] == board[i][1] != ' ' for j in range(2, 6)):
                return True
            if all(board[j][i] == board[1][i] != ' ' for j in range(2, 6)):
                return True

        # Check diagonals
        if all(board[i][i] == board[0][0] != ' ' for i in range(1, 5)):
            return True
        if all(board[i + 1][i + 1] == board[1][1] != ' ' for i in range(1, 5)):
            return True
        if all(board[i][5 - i] == board[0][5] != ' ' for i in range(1, 5)):
            return True
        if all(board[i + 1][4 - i] == board[1][4] != ' ' for i in range(1, 5)):
            return True

        return False

    def check_win_chaos(self):
        if not any(' ' in sublist for sublist in self.__board):
            return True
