from domain import Player

class PlayersRepo:
    def __init__(self,filename):
        self.__filename = filename
        self.__players = self.load()

    @property
    def get_players(self):
        return self.__players

    @property
    def get_filename(self):
        return self.__filename

    def load(self):
        players=[]
        with open(self.get_filename,'r') as f:
            lines=f.readlines()
            for l in lines:
                id,name,strength=l.split(',')
                id=id.strip()
                name=name.strip()
                strength=int(strength)
                player=Player(id,name,strength)
                players.append(player)
        return players

    def save(self):
        with open(self.get_filename,'w') as f:
            for p in self.get_players:
                f.write(f'{p.get_id},{p.get_name},{p.get_strength}\n')

    def remove_player(self,player):
        self.get_players.remove(player)
        self.save()



