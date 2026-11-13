import random

from domain import Info
class Service:
    def __init__(self):
        pass

    def initial_state(self):
        first_year=Info(0,0,100,1000,3,200,20,2800)
        return first_year

    def update_land(self,info,a):
        if a<0:
            if abs(a)>info.land:
                raise ValueError("You don't have enough land to sell.")
            info.set_land(info.land+a)
            info.set_grain_stock(info.grain_stock+abs(a)*info.land_price)
        else:
            if a*info.land_price>info.grain_stock:
                raise ValueError("You don't have enough grain to buy land.")
            info.set_land(info.land+a)
            info.set_grain_stock(info.grain_stock-a*info.land_price)

    def feed_population(self,info,b):
        if b>info.grain_stock:
            raise ValueError("You don't have enough grain to feed the population.")
        info.set_grain_stock(info.grain_stock-b)
        info.set_starved(info.population-b//20)

    def plant_land(self,info,c):
        if c>info.land:
            raise ValueError("You don't have enough land to plant.")
        if info.population*10<c:
            raise ValueError("You don't have grain to plant.")
        info.set_land(info.land-c)

    def new_year(self,info):
        info.set_land_price(random.randint(15,25))
        info.set_harvest(random.randint(1,6))
        info.set_rats()

    def new_people(self,info):
        info.set_immigrants(random.randint(0,10))

