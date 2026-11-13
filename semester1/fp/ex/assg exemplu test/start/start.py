from repository.textfilerepo import AssignmentsRepo
from service.service import Service
from ui.ui import Ui


def main():
    repo=AssignmentsRepo("assignments.txt")
    service=Service(repo)
    ui=Ui(service)
    ui.main_loop()

if __name__=="__main__":
    main()