from src.repository import TextFileRepository, MemoryRepository, BinaryFileRepository
from src.services import Services, TestMemoryRepository,TestBinaryFileRepository,TestTextFileRepository
from src.ui import UI
import random


def main():
    repo=BinaryFileRepository() # BinaryFileRepository() or MemoryRepository() or TextFileRepository()
    services=Services(repo)
    ui=UI(services)
    if not repo.get_all():
        names_list = [
            "Abel","Aladin","Bob", "Catalin", "David", "Eusebiu",
            "Florin", "George" "Ivon", "Juve",
            "Marcel", "Laurentiu", "Mona", "Nicolae", "Oscar",
            "Paul", "Rita", "Samuel","Tina"
        ]
        for i in range(10):
            student_id = i + 1
            name = random.choice(names_list)
            group = random.randint(911, 918)
            services.add_student(student_id, name, group)

    ui.print_menu()

def start():
    TestMemoryRepository()
    TestBinaryFileRepository()
    TestTextFileRepository()
    main()

start()