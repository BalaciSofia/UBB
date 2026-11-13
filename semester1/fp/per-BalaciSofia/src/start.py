
from src.repo.textfilerepo import Repository
from src.service.service import Service
from src.ui.ui import Ui

def main():
    repo=Repository("labyrinth_simple.txt")
    service=Service(repo)
    ui=Ui(service)
    ui.start()


if __name__=='__main__':
    main()
