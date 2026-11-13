
class Ui:
    def __init__(self,service):
        self.__service = service

    @property
    def service(self):
        return self.__service

    def main_loop(self):
        self.ui_display_players()
        if self.service.player_count_verify()[0]:
            self.ui_play_tournament()
        else:
            n=self.service.player_count_verify()[1]
            self.ui_play_qualifying(n)




    def ui_display_players(self):
        players=self.service.sort_players()
        for p in players:
            print(f" ID:{p.get_id}  Name: {p.get_name}  Strength: {p.get_strength}")

    def ui_play_tournament(self):
        while self.service.player_count()>1:
            print("Last",self.service.player_count(),"players")
            pairs=self.service.play_pair()
            i=0
            while pairs:
                print(f"id{pairs[i][0].get_id},name:{pairs[i][0].get_name},strength:{pairs[i][0].get_strength}")
                print(f"id{pairs[i][1].get_id},name:{pairs[i][1].get_name},strength:{pairs[i][1].get_strength}")
                option=input("choose player(1/2):")
                if option=="1":
                    self.service.remove_player(pairs[i][0])
                else:
                    self.service.remove_player(pairs[i][1])
                i+=1

        p=self.service.get_repo.get_players[0]
        print("winner is:")
        print(f"id:{p.get_id},name:{p.get_name},strength:{p.get_strength}")

    def ui_play_qualifying(self,n):
        p=self.service.play_qualifying(n)
        print("\nplayers for qualifying\n")
        for pl in p:
            print(f" ID:{pl.get_id}  Name: {pl.get_name}  Strength: {pl.get_strength}")
