from unittest import TestCase

from domains import Order, Driver
from repositories import RepoDrivers, RepoOrders


class Service:
    def __init__(self, driver_repo, order_repo ):
        self.__driver_repo = driver_repo
        self.__order_repo = order_repo

    @property
    def get_driver_repo(self):
        return self.__driver_repo

    @property
    def get_order_repo(self):
        return self.__order_repo

    def check_id_exists(self,id):
        """
        check if driver id exists
        :param id: the id we search for
        :return: true if exists false otherwise
        """
        for driver in self.get_driver_repo.get_drivers:
            if driver.get_id == id:
                return True
        return False
    def check_distance(self,distance):
        """
        Check if distance is valid
        :param distance: the given distance
        :return: true if valid false otherwise
        """
        if distance < 1:
            return False
        return True
    def add_order(self,id,distance):
        """
        adding an order
        :param id: the id of the driver for the order
        :param distance: the distance of the order
        """
        if not self.check_id_exists(id):
            raise ValueError("Driver id does not exist")
        if not self.check_distance(distance):
            raise ValueError("Distance is not valid")
        order=Order(id,distance)
        self.get_order_repo.add_order(order)
    def calculate_income(self,id):
        income=0
        d_name=""
        for o in self.get_order_repo.get_orders:
            if o.get_id == id:
               income=income+o.get_distance*2.5
        for d in self.get_driver_repo.get_drivers:
            if d.get_id == id:
                d_name=d.get_name
        return income,d_name

class TestForAdd(TestCase):
    def setUp(self) -> None:
        self.driver_repo=RepoDrivers("drivers_test")
        self.order_repo=RepoOrders("orders_test")
        self.service=Service(self.driver_repo,self.order_repo)

    def test_add_order(self):
        self.service.add_order(1,10)
        self.assertEqual(len(self.service.get_order_repo.get_orders),1)

    def test_add_order_invalid_id(self):
        with self.assertRaises(ValueError):
            self.service.add_order(2,10)

    def test_add_order_invalid_distance(self):
        with self.assertRaises(ValueError):
            self.service.add_order(1,0)

    def test_check_id_exists(self):
        self.assertTrue(self.service.check_id_exists(1))

    def test_check_id_not_exists(self):
        self.assertFalse(self.service.check_id_exists(2))

    def test_check_distance(self):
        self.assertTrue(self.service.check_distance(10))

    def test_check_distance_invalid(self):
        self.assertFalse(self.service.check_distance(0))