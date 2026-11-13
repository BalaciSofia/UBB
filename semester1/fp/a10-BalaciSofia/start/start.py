
from services import ServiceBoard
from ui import Ui

def main():
    service = ServiceBoard()
    ui = Ui(service)
    interface=input("Choose interface(1 for console, 2 for graphical): ").strip()
    if interface=="1":
        ui.play_console()
    elif interface=="2":
        ui.play_graph()
    else:
        print("Invalid input")
if __name__ == "__main__":
    main()