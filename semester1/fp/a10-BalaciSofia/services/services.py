from copy import deepcopy
from unittest import TestCase
from domain.board import Board


class ServiceBoard:
    def __init__(self):
        self.board=Board()

    def list_board(self):
        print('  -1- -2- -3- -4- -5- -6- -7-')
        for row in self.board.get_board:
            print (' | '+' | '.join(row)+' | ')
        print('-'*32)

    def player_move(self,move):
        """
        executes the player s move
        :param move: the column he chose
        :return: new board with the player move
        """
        if not self.board.drop(move, 'X'):
            raise ValueError("Column is full! Try again.")

    def best_move(self):
        """
        searches the board for the best move the computer can make
        :return: the best move
        options:
            1.Computer next move is a win
            2.Computer next move has to block the player

        """
        actual_board=deepcopy(self.board)

        # Check for winning move for the computer ('O')
        for col in range(7):
            if actual_board.get_board[0][col] == ' ':  # Check if the column is not full
                actual_board.drop(col, 'O')  # Simulate the move
                if actual_board.is_winner('O'):  # Check for win
                    return col  # Found a winning move
                actual_board = deepcopy(self.board) #If not found undo to the original board

        actual_board=deepcopy(self.board)

        # Check if player has a move that can win in the next turn ('X')
        for col in range(7):
            if actual_board.get_board[0][col] == ' ':
                actual_board.drop(col, 'X')  # Simulate the player's move
                if actual_board.is_winner('X'):  # Check for player's win
                    return col  # Block the player's winning move
                actual_board = deepcopy(self.board)

        actual_board=deepcopy(self.board)
        # If no immediate winning or blocking moves, try to select a preferred center column
        for col in [3, 2, 4, 1, 5, 0, 6]:  # Check center columns first
            if actual_board.get_board[0][col] == ' ':
                return col  # Return first available column

        return None  # Should not reach here if there are available columns

    def computer_move(self):
        """
        executes the computer s move
        :return: new board with the computer move
        """
        move=self.best_move()
        self.board.drop(move,'O')


class TestsService(TestCase):
    def setUp(self):
        self.__services=ServiceBoard()

    def test_player_move(self):
        self.__services.player_move(2)
        self.assertEqual(self.__services.board.get_board[5][2], 'X')
        self.__services.player_move(2)
        self.assertEqual(self.__services.board.get_board[4][2], 'X')

    def test_best_move_vertical(self):
        #block vertical
        self.__services.player_move(2)
        self.__services.player_move(2)
        self.__services.player_move(2)
        move=self.__services.best_move()
        self.assertEqual(move, 2)

        #win vertical
        self.__services.board.drop(1,'O')
        self.__services.board.drop(1,'O')
        self.__services.board.drop(1,'O')
        move=self.__services.best_move()
        self.assertEqual(move, 1)

    def test_best_move_horizontal(self):
        #block horizontal
        self.__services.player_move(0)
        self.__services.player_move(1)
        self.__services.player_move(2)
        move=self.__services.best_move()
        self.assertEqual(move, 3)

        #win horizontal
        self.__services.board.drop(6,'O')
        self.__services.board.drop(5,'O')
        self.__services.board.drop(4,'O')
        move=self.__services.best_move()
        self.assertEqual(move, 3)

    def test_best_move_oblique(self):
        #block
        self.__services.board.drop(1,'O')
        self.__services.board.drop(1,'X')
        self.__services.board.drop(2,'X')
        self.__services.board.drop(2,'O')
        self.__services.board.drop(2,'X')
        self.__services.board.drop(3,'O')
        self.__services.board.drop(3,'X')
        self.__services.board.drop(3,'O')
        self.__services.board.drop(3,'X')
        move=self.__services.best_move()
        self.assertEqual(move, 0)

        #win
        self.__services.board.drop(1, 'X')
        self.__services.board.drop(1, 'O')
        self.__services.board.drop(2, 'O')
        self.__services.board.drop(2, 'X')
        self.__services.board.drop(2, 'O')
        self.__services.board.drop(3, 'X')
        self.__services.board.drop(3, 'O')
        self.__services.board.drop(3, 'X')
        self.__services.board.drop(3, 'O')
        move=self.__services.best_move()
        self.assertEqual(move, 0)

    def test_computer_move(self):
        self.__services.board.drop(6, 'O')
        self.__services.computer_move()
        self.assertEqual(self.__services.board.get_board[3][0], 'X' )
