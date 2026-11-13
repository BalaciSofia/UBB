from ui import Ui
from repo import GameRepo
from service import Service
def main():
    print("1. New game")
    print("2. Load game")
    print("3. Exit")
    option = input("Enter option: ")
    if option == '1':
        repo = GameRepo("save.txt", 1)
        service=Service(repo)
        ui=Ui(service)
        ui.game()
    elif option == '2':
        repo = GameRepo("save.txt", 2)
        service=Service(repo)
        ui=Ui(service)
        ui.game()
    elif option == '3':
        return
    else:
        print("Invalid option")

if __name__ == '__main__':
    main()