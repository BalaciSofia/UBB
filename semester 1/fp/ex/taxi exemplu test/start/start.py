from service import Service
from repositories import RepoDrivers,RepoOrders
from ui import Ui


def main():
    repo_d=RepoDrivers("drivers.txt")
    repo_o=RepoOrders("orders.txt")
    service=Service(repo_d,repo_o)
    ui=Ui(service)
    ui.main_loop()

if __name__=="__main__":
    main()
