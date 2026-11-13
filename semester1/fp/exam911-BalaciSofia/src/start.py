from repository import ReservationRepo,RoomRepo
from ui import Ui
from service import Service
rez_repo=ReservationRepo("reservations.txt")
room_repo=RoomRepo("rooms.txt")
service=Service(room_repo,rez_repo)
ui=Ui(service)

ui.main_loop()
