from domains import Driver
from domains import Order


class RepoDrivers:
    def __init__(self, filename):
         self.__filename = filename
         self.__drivers = self.load()

    @property
    def get_drivers(self):
        return self.__drivers

    def load(self):
        drivers=[]
        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for l in lines:
                id, name = l.split(',')
                id=id.strip()
                name=name.strip()
                driver=Driver(id, name)
                drivers.append(driver)
        return drivers

class RepoOrders:
    def __init__(self, filename):
        self.__filename=filename
        self.__orders=self.load()

    @property
    def get_orders(self):
        return self.__orders

    def load(self):
        orders=[]
        with open(self.__filename, 'r') as f:
            lines = f.readlines()
            for l in lines:
                id, distance = l.split(',')
                distance=int(distance)
                id=id.strip()
                order=Order(id, distance)
                orders.append(order)
        return orders

    def save(self):
        with open(self.__filename,'w') as f:
            for o in self.get_orders:
                f.write(f'{o.get_id},{o.get_distance}\n')

    def add_order(self,order):
        self.get_orders.append(order)
        self.save()