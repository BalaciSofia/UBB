import unittest

class Board:
    def __init__(self):
        self.__board=[[' ' for _ in range(7)]for _ in range(6)]

    @property
    def get_board(self):
        return self.__board

    def drop(self,column,piece):
        """
        drops a piece on the board
        :param column: the column to drop in
        :param piece: the piece to drop
        """
        for row in reversed(self.get_board):
            if row[column]==' ':
                row[column]=piece
                return True
        return False

    def is_winner(self, piece):
        """
        Checks if someone won
        :param piece: the player hom we check
        :return: true if game is won by player piece
        """
        # Check horizontal, vertical, and diagonal lines for a win
        for r in range(6):
            for c in range(7):
                if self.check_direction(r, c, 1, 0, piece) or \
                        self.check_direction(r, c, 0, 1, piece) or \
                        self.check_direction(r, c, 1, 1, piece) or \
                        self.check_direction(r, c, 1, -1, piece):
                    return True
        return False

    def check_direction(self, r, c, dr, dc, piece):
        """
         Check if there is a Connect 4 starting from row r,column c in direction (dr, dc)
        :param r: row
        :param c: column
        :param dr: direction x
        :param dc: direction y
        :param piece: X/O
        """
        for i in range(4):
            nr = r + i * dr
            nc = c + i * dc
            if not (0 <= nr < 6 and 0 <= nc < 7) or self.get_board[nr][nc] != piece:
                return False
        return True

    def is_full(self):
        """
        Checks if the board is full
        """
        return all(' ' not in row for row in self.get_board)


class TestBoard(unittest.TestCase):
    def setUp(self):
        self.board = Board()

    def test_drop(self):
        self.board.drop(3, 'X')
        self.assertEqual(self.board.get_board[5][3], 'X')

    def test_drop_in_full_column(self):
        for _ in range(6):
            self.board.drop(2, 'O')
        result = self.board.drop(2, 'X')  #False
        self.assertFalse(result)

    def test_horizontal_win(self):
        for col in range(4):
            self.board.drop(col, 'X')
        self.assertTrue(self.board.is_winner('X'))

    def test_vertical_win(self):
        for _ in range(4):
            self.board.drop(3, 'O')
        self.assertTrue(self.board.is_winner('O'))

    def test_diagonal_win(self):
        self.board.drop(2, 'X')
        self.board.drop(3, 'X')
        self.board.drop(4, 'X')
        self.board.drop(5, 'X')
        self.assertTrue(self.board.is_winner('X'))

        self.board = Board()
        self.board.drop(5, 'O')
        self.board.drop(4, 'X')
        self.board.drop(3, 'X')
        self.board.drop(2, 'X')
        self.board.drop(1, 'X')
        self.assertTrue(self.board.is_winner('X'))

    def test_is_full(self):
        self.assertFalse(self.board.is_full())
        for row in self.board.get_board:
            for col in range(7):
                row[col] = 'X'
        self.assertTrue(self.board.is_full())


