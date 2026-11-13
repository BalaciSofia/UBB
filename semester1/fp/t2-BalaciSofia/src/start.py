from repository import PlayersRepo
from services import Services
from ui import Ui
def main():
    repo=PlayersRepo("data.txt")
    service=Services(repo)
    ui=Ui(service)
    ui.main_loop()

if __name__=="__main__":
    main()
