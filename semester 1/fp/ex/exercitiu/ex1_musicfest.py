"""
music festival
->name
->month(1-12)
->ticket cost
->list of artists

1:have 6 music festivals hard coded in the application
2
"""

'''
FUNCTIONS----------------------------------------------------------------------------------------------------------------
'''
def initialize():
    mf= [{'name': "Sziget", 'month': 8, 'cost': 1200, 'artists': ['JB', 'Billie', 'Ariana']},
         {'name': "Coachella", 'month': 4, 'cost': 1500, 'artists': ['Drake', 'Beyonce']},
         {'name':"Tomorrowland",'month':3,'cost':1300,'artists':['David Guetta','Alesso']},
         {'name':"Untold",'month':10,'cost':900,'artists':['Shawn Mendes,Sabrina']},
         {'name':"Ultra music festival",'month':1,'cost':1430,'artists':['Calvin Harris']},
         {'name':"Electric",'month':12,'cost':900,'artists':['Ed Sheeran','Taylor Swift','Camilla','5SOS']}]
    return mf
def add(mf,n,m,c,a):
    new={'name':n,'month':m,'cost':c,'artists':a}
    mf.append(new)

def test_add():
    lst=[]
    lst1=[{'name':"Ultra music festival",'month':1,'cost':1430,'artists':['Calvin Harris']}]
    name="Ultra music festival"
    month=1
    cost=1430
    artists=['Calvin Harris']
    add(lst,name,month,cost,artists)
    assert lst==lst1

def search(mf,name):
    for i in mf:
        if i['name'] == name:
            return 1
    return 0
def test_search():
    lst=[{'name': "Sziget", 'month': 8, 'cost': 1200, 'artists': ['JB', 'Billie', 'Ariana']},
         {'name': "Coachella", 'month': 4, 'cost': 1500, 'artists': ['Drake', 'Beyonce']},
         {'name':"Tomorrowland",'month':3,'cost':1300,'artists':['David Guetta','Alesso']},
         {'name':"Untold",'month':10,'cost':900,'artists':['Shawn Mendes,Sabrina']},
         {'name':"Ultra music festival",'month':1,'cost':1430,'artists':['Calvin Harris']},
         {'name':"Electric",'month':12,'cost':900,'artists':['Ed Sheeran','Taylor Swift','Camilla','5SOS']}]
    name="Ultra music festival"
    assert search(lst,name)==1
def f_spring(mf):
    spring=[]
    for i in mf:
        if i['month']==3 or i['month']==4 or i['month']==5 :
            spring.append(i)
    sort_by_date(spring)
    return spring
def f_winter(mf):
    winter=[]
    for i in mf:
        if i['month']==1 or i['month']==2 or i['month']==12:
            winter.append(i)
    sort_by_date(winter)
    return winter
def f_autumn(mf):
    autumn=[]
    for i in mf:
        if i['month']==9 or i['month']==10 or i['month']==11:
            autumn.append(i)
    sort_by_date(autumn)
    return autumn
def f_summer(mf):
    summer=[]
    for i in mf:
        if i['month']==6 or i['month']==7 or i['month']==8:
            summer.append(i)
    sort_by_date(summer)
    return summer
def swap(x,y):
    aux=x
    x=y
    y=aux
    return x,y
def sort_by_date(mf):
    for i in range(0,len(mf)-2):
        for j in range(i+1,len(mf[i])-1):
            if mf[i]['month']>mf[j]['month']:
               mf[i],mf[j]=swap(mf[i],mf[j])
            elif mf[i]['month']==mf[j]['month']:
                if mf[i]['name']>mf[j]['name']:
                    mf[i],mf[j]=swap(mf[i],mf[j])

'''
UI-------------------------------------------------------------------------------------------------------------------------
'''
def add_ui(mf):
    name = input("Enter name:")
    month = int(input("Enter month:"))
    cost = int(input("Enter cost:"))
    number_of_artists = int(input("Enter number of artists:"))
    artist = []
    for i in range(0,number_of_artists):
        artist.append (input("Enter name of artist:"))
    if month<0 or month>12:
        raise ValueError("Invalid month")
    if search(mf,name)==1:
        print("This festival already exists")
        return
    add(mf,name,month,cost,artist)

def show_ui(mf):
    season=input("Enter season:").strip().lower()
    if season=="spring":
        print(f_spring(mf))
        return
    if season=="autumn":
        print(f_autumn(mf))
        return
    if season=="summer":
        print(f_summer(mf))
        return
    if season=="winter":
        print(f_winter(mf))
def main_ui():
    command=input("Enter command:")
    command=command.lower().strip()
    mf=initialize()
    while True:
        command = input("Enter command:")
        command = command.lower().strip()
        if command=="add":
            add_ui(mf)
        if command=="show":
            show_ui(mf)
test_add()
test_search()
main_ui()