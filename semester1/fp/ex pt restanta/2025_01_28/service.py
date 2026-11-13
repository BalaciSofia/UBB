from texttable import Texttable
class Service:
    def __init__(self,repo):
        self.__repo=repo

    @property
    def repo(self):
        return self.__repo

    def print_board(self):
        t=Texttable()
        for i in range (3):
            row=[' ' for _ in range(3)]
            for j in range(3):
                row[j]=self.repo.get_game.get_board[i][j]
            t.add_row(row)
        return t.draw()

    def validate(self,a,b):
        try:
            a=int(a)
            b=int(b)
        except ValueError:
            raise ValueError("Invalid input.A and B must be integers")
        if a<0 or a>2 or b<0 or b>2:
            raise ValueError("Invalid input.A and B must be between 0 and 2")
        if self.repo.get_game.get_board[a][b]!=' ':
            raise ValueError("Invalid input.Position already taken")
        return True

    def validate_movement(self,a,b,player_piece):
        try:
            a = int(a)
            b = int(b)
        except ValueError:
            raise ValueError("Invalid input.A and B must be integers")
        if a<0 or a>2 or b<0 or b>2:
            raise ValueError("Invalid input.A and B must be between 0 and 2")
        if self.repo.get_game.get_board[a][b]!=player_piece:
            raise ValueError("Invalid input.Position not taken by player")
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (1, 1), (-1, 1), (1, -1)]
        for da, db in directions:
            na, nb = a + da, b + db
            if 0 <= na < 3 and 0 <= nb < 3 and self.repo.get_game.get_board[na][nb] == ' ':
                return True
        raise ValueError("Invalid input. Position not near blank space")

    def find_space(self):
        for i in range(3):
            for j in range(3):
                if self.repo.get_game.get_board[i][j]==' ':
                    return i,j

    def replace(self,a,b,c,d,piece):
        self.repo.modify(a,b,c,d,piece)

    def place(self,a,b,piece):
        self.repo.place(a,b,piece)

    def remove(self,a,b):
        self.repo.remove(a,b)

    def computer_move(self,piece,player_piece):
        #check winning move by simulating all moves
        best_move=None
        for i in range(3):
            for j in range(3):
                if self.repo.get_game.get_board[i][j]==' ':
                    self.repo.half_place(i,j,piece)
                    if self.repo.get_game.check_win(piece):
                        best_move=(i,j)
                    self.remove(i,j)
        if best_move==None:
            for i in range(3):
                for j in range(3):
                    if self.repo.get_game.get_board[i][j] == ' ':
                        self.repo.half_place(i, j, player_piece)
                        if self.repo.get_game.check_win(player_piece):
                            best_move = (i, j)
                        self.remove(i, j)
        if best_move==None:
            for i in range(3):
                for j in range(3):
                    if self.repo.get_game.get_board[i][j]==' ':
                            best_move=(i,j)
                            break
        self.place(best_move[0],best_move[1],piece)

    def how_many(self):
        count=0
        for i in range(3):
            for j in range(3):
                if self.repo.get_game.get_board[i][j]=='X':
                    count+=1
        return count

    def computer_move2(self, piece):
        # Find all pieces of the computer
        computer_pieces = []
        for i in range(3):
            for j in range(3):
                if self.repo.get_game.get_board[i][j] == piece:
                    computer_pieces.append((i, j))

        # Try to move each piece to an adjacent empty space
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (1, 1), (-1, 1), (1, -1)]
        for a, b in computer_pieces:
            for da, db in directions:
                na, nb = a + da, b + db
                if 0 <= na < 3 and 0 <= nb < 3 and self.repo.get_game.get_board[na][nb] == ' ':
                    self.repo.modify(a, b, na, nb, piece)
                    return