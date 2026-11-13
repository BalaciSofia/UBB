

"""
music festival
->name
->month
->ticket cost
->list of artists
"""
from src.functions import (initialize, verify_add, add, search_artist,display_autumn,display_summer,display_winter,display_spring)


def add_ui(mf):
    name = input("Name: ")
    month = input("Month: ")
    ticket = input("Ticket: ")
    number_of_artists = int(input("Number of artists: "))
    artist=[]
    for i in range (number_of_artists):
        artist.append(input("Artist: "))
    try:
        verify_add(month,name,mf)
        add(mf,name,month,ticket,artist)
    except ValueError as e:
        print(e)


def select_season(season,mf):
    if season=="spring":
        print(display_spring(mf))
    elif season=="summer":
        print(display_summer(mf))
    elif season=="winter":
        print(display_winter(mf))
    elif season=="autumn":
        print(display_autumn(mf))
    else:
        print('Invalid season. Choose between spring,summer,winter,autumn')
def display(mf):
    for i in mf:
        print(i)
def main_loop():
    mf=initialize()
    while True:
        print("option1:Add a music festival")
        print("option2:Show festivals during a season")
        print("option3:Display all festivals where an artist performs")
        print("option4:Display all festivals")
        print("option5:Exit the application")
        choice =int( input("Enter your choice: "))
        if choice == 1:
            add_ui(mf)
        elif choice == 2:
            season=input("Season: ")
            select_season(season,mf)
        elif choice == 3:
            art=input("Artist: ")
            result=search_artist(mf,art)
            if len(result)==0:
                print("Artist not found")
            else:
                result.sort(key=lambda x:x['month'])
                print(result)
        elif choice == 4:
            display(mf)
        elif choice == 5:
            break