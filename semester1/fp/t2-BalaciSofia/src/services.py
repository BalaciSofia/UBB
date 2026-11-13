import random
class Services:
    def __init__(self,repo):
        self.__repo=repo

    @property
    def get_repo(self):
        return self.__repo

    def sort_players(self):
       return sorted(self.get_repo.get_players,key=lambda p:p.get_strength,reverse=True)

    def player_count(self):
        return len(self.get_repo.get_players)

    def player_count_verify(self):
        n=2
        while self.player_count()>n:
            n=n*2
        if self.player_count()==n:
            return True,0
        return False,int(n/2)

    def play_qualifying(self,n):
        players=[]
        noplayers=self.player_count()-n
        i=self.player_count()-1
        while self.player_count()-i-1!=noplayers:
            players.append(self.sort_players()[i])
            i-=1
        return players

    def play_pair(self):
        players = self.get_repo.get_players.copy()
        random.shuffle(players)
        pairs = []
        while len(players) >= 2:
            pair = (players.pop(), players.pop())
            pairs.append(pair)
        return pairs

    def remove_player(self,player):
        self.get_repo.remove_player(player)



