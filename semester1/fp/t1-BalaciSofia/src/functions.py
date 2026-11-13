

def initialize():
     return[{'name':"Untold",'month':1,'ticket_cost':700,'artists':["Madona","Ariana Grande"]},
            {'name':"Electric",'month':8,'ticket_cost':500,'artists':["5SOS"]},
            {'name':"Sziget",'month':11,'ticket_cost':900,'artists':["Justin Biber","Beyonce","Olivia"]}]

def verify_add(month,name,mf):
    try:
        month = int(month)
        if month < 0 or month > 12:
             raise ValueError("Month must be between 1 and 12")
    except:
        raise ValueError
    for i in mf:
        if i['name'] == name:
            raise ValueError("Name must be unique")
def add(mf,n,m,t,a):
    mf.append({'name':n,'month':m,'ticket_cost':t,'artists':a})

def test_add():
    lst=[]
    name="SummerFest"
    month=2
    ticket_cost=700
    artist=["Niki","Anne Marie","Drake"]
    lst1=[{'name':name,'month':month,'ticket_cost':ticket_cost,'artists':artist}]
    add(lst,name,month,ticket_cost,artist)
    assert lst == lst1

def search_artist(mf,art):
    new_mf=[]
    for i in mf:
         for j in range(len(i['artists'])):
             if i['artists'][j]==art:
                new_mf.append(i)
    return new_mf


def display_spring(mf):
    list_display=[]
    for i in mf:
        if i['month']==3 or i['month']==4 or i['month']==5:
            list_display.append(i)
    list_display=sorted(list_display,key=lambda x:x['month'] and x['name'])
    return list_display
def display_summer(mf):
    list_display=[]
    for i in mf:
        if i['month']==6 or i['month']==7 or i['month']==8:
            list_display.append(i)
    list_display=sorted(list_display,key=lambda x:x['month'] and x['name'])
    return list_display
def display_winter(mf):
    list_display=[]
    for i in mf:
        if i['month']==12 or i['month']==1 or i['month']==2:
            list_display.append(i)
    list_display=sorted(list_display,key=lambda x:x['month'] and x['name'])
    return list_display
def display_autumn(mf):
    list_display=[]
    for i in mf:
        if i['month']==9 or i['month']==10 or i['month']==11:
            list_display.append(i)
    list_display=sorted(list_display,key=lambda x:x['month'] and x['name'])
    return list_display