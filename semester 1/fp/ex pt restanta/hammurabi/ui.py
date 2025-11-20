
class Ui:
    def __init__(self,service):
        self.__service = service

    @property
    def service(self):
        return self.__service

    def start(self):
        current_year=self.service.initial_state()
        index=1
        won=False
        while True and index<=5:
            if current_year.population>=100 and current_year.land>=1000:
                print("You won")
                won=True
                break
            print("In year ",index)
            print(current_year)
            a=input("Acres to buy/sell(+/-) -> ")
            while not self.ui_buy_sell_land(current_year,a):
                a=input("Acres to buy/sell(+/-) -> ")
            population=current_year.population
            b=input("Units to feed the population -> ")
            while not self.ui_feed_population(current_year,b):
                b=input("Units to feed the population -> ")
            if current_year.population<population//2:
                print("more than half of the population died")
                print("Game over")
                break
            if current_year.population==population:
                self.service.new_people(current_year)
            c=input("Acres to plant -> ")
            while not self.ui_plant_land(current_year,c):
                c=input("Acres to plant -> ")
            self.service.new_year(current_year)
            index+=1
        if index>5 and not won:
            print("You lost")
            print("Game over")

    def ui_buy_sell_land(self,current_year,a):
        try:
            a=int(a)
            self.service.update_land(current_year,a)
            return True
        except ValueError as e:
            print(e)
            return False

    def ui_feed_population(self,current_year,b):
        try:
            b=int(b)
            self.service.feed_population(current_year,b)
            return True
        except ValueError as e:
            print(e)
            return False

    def ui_plant_land(self,current_year,c):
        try:
            c=int(c)
            self.service.plant_land(current_year,c)
            return True
        except ValueError as e:
            print(e)
            return False