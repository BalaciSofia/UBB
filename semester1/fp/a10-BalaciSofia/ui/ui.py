import sys

import pygame
class Ui:
    def __init__(self,services):
        self.__services = services

    @property
    def get_services(self):
        return self.__services

    #main game loop for console
    def play_console(self):
        end_game=False
        self.get_services.list_board()
        while not end_game:
            #-----the player chooses it s move------
            #
            move = input("choose next move(1-7):")
            while not self.handle_move(move):
                move=input("choose next move(1-7):")
            #
            self.get_services.list_board()
            #
            #-----checks------
            if self.get_services.board.is_winner('X'):
                end_game=True
                print("You win!")
            elif self.get_services.board.is_full():
                print("It's a draw!")
                end_game=True
            if not end_game:
                #-----computer turn----
                print("computer's turn")
                self.computer_move()
                #
                self.get_services.list_board()
                #
                #----checks----
                if self.get_services.board.is_winner('O'):
                    end_game = True
                    print("I win!")
                elif self.get_services.board.is_full():
                    print("It's a draw!")
                    end_game=True

    #main game loop for graphic
    def play_graph(self):
        pygame.init()
        """
        630x630
        a square is 90x90
        7cols 6rows(7 rows with empty one) 
        """
        screen=pygame.display.set_mode((630,630))
        pygame.display.set_caption("Connect Four")
        self.draw_board(screen,self.get_services.board)
        end_game=False
        while not end_game:
            #-----the player chooses it s move------
            #
            font=pygame.font.SysFont("Arial",70)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    end_game=True
                    sys.exit()
                if event.type == pygame.MOUSEMOTION:
                    pygame.draw.rect(screen,(0,0,0),(0,0,630,90))
                    position=event.pos[0]
                    pygame.draw.circle(screen,(48,92,222),(position,45),40)
                    pygame.display.update()
                if event.type == pygame.MOUSEBUTTONDOWN:
                    move = event.pos[0]
                    move = int(move // 90) + 1
                    #self.handle_move(move)
                    if self.handle_move(move):
                        self.draw_board(screen, self.get_services.board)
                        if self.get_services.board.is_winner('X'):
                            end_game = True
                            label=font.render("You win!",True,(255,0,127))
                            pygame.draw.rect(screen, (0, 0, 0), (0, 0, 630, 90))
                            screen.blit(label,(200,10))
                        elif self.get_services.board.is_full():
                            end_game = True
                            label=font.render("It's a draw!",True,(255,0,127))
                            pygame.draw.rect(screen, (0, 0, 0), (0, 0, 630, 90))
                            screen.blit(label,(200,10))
                        self.draw_board(screen, self.get_services.board)
                        if not end_game:
                            # -----computer turn----
                            self.computer_move()
                            self.draw_board(screen, self.get_services.board)
                            # ----checks----
                            if self.get_services.board.is_winner('O'):
                                end_game = True
                                label=font.render("I win!",True,(255,0,127))
                                pygame.draw.rect(screen, (0, 0, 0), (0, 0, 630, 90))
                                screen.blit(label, (230, 10))
                            elif self.get_services.board.is_full():
                                end_game = True
                                label = font.render("It's a draw!",True, (255, 0, 127))
                                pygame.draw.rect(screen, (0, 0, 0), (0, 0, 630, 90))
                                screen.blit(label, (200, 10))
                        self.draw_board(screen, self.get_services.board)
                if end_game:
                    pygame.time.wait(6000)

    def handle_move(self,move):
        try:
            move=int(move)
            move-=1
            if move not in range(0,7):
                raise ValueError("selection not in range")
            self.get_services.player_move(move)
            return True
        except ValueError as e:
            print(e)
            return False

    def computer_move(self):
        self.get_services.computer_move()

    def draw_board(self,screen,board):
        PINK=[232,158,184]#back
        RED=[210,10,46]
        BLUE=[48,92,222]
        BLACK=[0,0,0]
        for c in range(7):
            for r in range(6):
                pygame.draw.rect(screen,PINK,(c*90,r*90+90,90,90))
                if board.get_board[r][c]==' ':
                    pygame.draw.circle(screen,BLACK,(c*90+45,r*90+135),40)
                elif board.get_board[r][c]=='X':
                    pygame.draw.circle(screen,BLUE,(c*90+45,r*90+135),40)
                else:
                    pygame.draw.circle(screen,RED,(c*90+45,r*90+135),40)
        pygame.display.update()
