from service import Service
from ui import Ui
def main():
    service=Service()
    ui=Ui(service)
    ui.start()

if __name__ == '__main__':
    main()