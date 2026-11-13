
class Info:
    def __init__(self,starved:int,immigrants:int,population:int,land:int,harvest:int,rats:int,land_price:int,grain_stock:int):
        self.__starved = starved
        self.__immigrants=immigrants
        self.__population=population
        self.__land=land
        self.__harvest=harvest
        self.__rats=rats
        self.__land_price=land_price
        self.__grain_stock=grain_stock

    @property
    def starved(self):
        return self.__starved

    @property
    def immigrants(self):
        return self.__immigrants

    @property
    def population(self):
        return self.__population

    @property
    def land(self):
        return self.__land

    @property
    def harvest(self):
        return self.__harvest

    @property
    def rats(self):
        return self.__rats

    @property
    def land_price(self):
        return self.__land_price

    @property
    def grain_stock(self):
        return self.__grain_stock

    def set_land(self,land):
        self.__land=land

    def set_grain_stock(self,grain_stock):
        self.__grain_stock=grain_stock

    def set_starved(self,starved):
        self.__starved=starved

    def set_land_price(self,land_price):
        self.__land_price=land_price

    def set_immigrants(self,immigrants):
        self.__immigrants=immigrants

    def set_harvest(self,harvest):
        self.__harvest=harvest

    def set_rats(self,rats):
        self.__rats=rats
    def __str__(self):
        return (f"{self.starved} people starved.\n"
                f"{self.immigrants} came to the city.\n"
                f"City population is {self.population}.\n"
                f"City owns {self.land} acres of land.\n"
                f"Harvest was {self.harvest} units per acre.\n"
                f"Rats ate {self.rats} bushels.\n"
                f"Land price is {self.land_price} units per acre.\n"
                f"Grain stocks are {self.grain_stock} units.\n")

