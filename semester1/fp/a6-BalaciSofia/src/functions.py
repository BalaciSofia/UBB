#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
from datetime import datetime

def get_day(t):
    return t['date']
def get_amount(t):
    return t['amount']
def get_type(t):
    return t['type']
def get_description(t):
    return t['description']
def set_day(t, day):
    t['date'] = day
def set_amount(t, amount):
    t['amount'] = amount
def set_type(t, type):
    t['type'] = type
def set_description(t, description):
    t['description'] = description

def add_transaction(t,com,mem):
    """
    :param t: the list of all transactions
    :param com: the command entered by the user which contains the amount,type and description
    :param mem: the list of all past lists of transactions
    :return: the new transaction list and the new memory list
    """
    amount=int(com[1])
    t.append({'date':datetime.today().day,'amount':amount,'type':com[2],'description':com[3]})
    mem.append(t)

def test_add_transaction():
    initial_list=[]
    initial_memory=[]
    command=["add","50","in","pizza"]
    add_transaction(initial_list,command,initial_memory)
    assert initial_list==[{'date':datetime.today().day,'amount':50,'type':'in','description':'pizza'}]
    assert initial_memory==[[{'date':datetime.today().day,'amount':50,'type':'in','description':'pizza'}]]

def insert_transaction(t,com,mem):
    """
    :param t: the list of all transactions
    :param com: the command entered by the user which contains the date,amount,type and description
    :param mem: the list of all past lists of transactions
    :return: the new transaction list and the new memory list
    """
    amount=int(com[2])
    date=int(com[1])
    t.append({'date':date,'amount':amount,'type':com[3],'description':com[4]})
    mem.append(t)

def test_insert_transaction():
    initial_list = []
    initial_memory = []
    command = ["insert", "4","50", "in", "pizza"]
    insert_transaction(initial_list, command, initial_memory)
    assert initial_list == [{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'}]
    assert initial_memory == [[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'}]]

def remove_transaction1(t,com,mem):
    """
    :param t: the list of all transactions
    :param com: the command entered by the user which contains the date
    :param mem: the list of all past lists of transactions
    :return: the new transaction list and the new memory list
    """
    day=int(com[1])
    t[:]=[t1 for t1 in t if get_day(t1)!=day]
    mem.append(t)

def test_remove_transaction1():
    initial_list = [{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'}]
    initial_memory = [[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'}]]
    command = ["remove","4"]
    remove_transaction1(initial_list,command,initial_memory)
    assert initial_list==[]
    assert initial_memory==[[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'}],[]]

def remove_transaction2(t,com,mem):
    """
    :param t: the list of all transactions
    :param com: the command entered by the user which contains the type
    :param mem: the list of all past lists of transactions
    :return: the new transaction list and the new memory list
    """
    t[:]=[t2 for t2 in t if get_type(t2)!=com[1]]
    mem.append(t)

def test_remove_transaction2():
    initial_list = [{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'}]
    initial_memory = [[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'}]]
    command = ["remove", "in"]
    remove_transaction2(initial_list, command, initial_memory)
    assert initial_list == []
    assert initial_memory == [[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'}], []]

def remove_transaction3(t,com,mem):
    """
    :param t: the list of all transactions
    :param com: the command entered by the user which contains the start date and end date
    :param mem: the list of all past lists of transactions
    :return: the new transaction list and the new memory list
    """
    start_day=int(com[1])
    end_day=int(com[3])
    t[:]=[t3 for t3 in t if not(start_day<=get_day(t3)<=end_day)]
    mem.append(t)

def test_remove_transaction3():
    initial_list = [{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'},
                    {'date': 6, 'amount': 50, 'type': 'in', 'description': 'pizza'}]
    initial_memory = [[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'},
                       {'date': 6, 'amount': 50, 'type': 'in', 'description': 'pizza'}]]
    command = ["remove","4","to","7"]
    remove_transaction3(initial_list, command, initial_memory)
    assert initial_list == []
    assert initial_memory == [[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'},
                               {'date': 6, 'amount': 50, 'type': 'in', 'description': 'pizza'}], []]


def search_transaction(t,com):
    """
    :param t: the list of all transactions
    :param com: the command entered by the user which contains the date,type and description
    :return: 0 if the searched transaction is not found,1 otherwise
    """
    day = int(com[1])
    for t1 in t:
        if get_day(t1)==day and get_type(t1)==com[2].strip() and get_description(t1)==com[3].strip():
            return 1
    return 0

def test_search_transaction():
    initial_list = [{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'},
                    {'date': 6, 'amount': 50, 'type': 'in', 'description': 'pizza'}]
    command = ["replace","4","in","pizza","with","90"]
    ok=search_transaction(initial_list, command)
    assert ok==1

def replace_transaction(t,com,mem):
    """
    :param t: the list of all transactions
    :param com: the command entered by the user which contains the date,type and description
    :param mem: the list of all past lists of transactions
    :return: the new transaction list and the new memory list
    """
    amount=int(com[5])
    date=int(com[1])
    for i in t:
        if get_day(i)==date and get_type(i)==com[2] and get_description(i)==com[3]:
            set_amount(i,amount)
            break
    mem.append(t)

def test_replace_transaction():
    initial_list = [{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'},
                    {'date': 6, 'amount': 50, 'type': 'in', 'description': 'pizza'}]
    initial_memory = [[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'},
                       {'date': 6, 'amount': 50, 'type': 'in', 'description': 'pizza'}]]
    command = ["replace","4","in","pizza","with","90"]
    replace_transaction(initial_list, command, initial_memory)
    assert initial_list == [{'date': 4, 'amount': 90, 'type': 'in', 'description': 'pizza'},
                               {'date': 6, 'amount': 50, 'type': 'in', 'description': 'pizza'}]
    assert initial_memory == [[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'},
                               {'date': 6, 'amount': 50, 'type': 'in', 'description': 'pizza'}],
                              [{'date': 4, 'amount': 90, 'type': 'in', 'description': 'pizza'},
                               {'date': 6, 'amount': 50, 'type': 'in', 'description': 'pizza'}]]


def filter_transaction1(t,com,mem):
    """
    :param t: the list of all transactions
    :param com: the command entered by the user which contains the type
    :param mem: the list of all past lists of transactions
    :return: the new transaction list and the new memory list
    """
    t[:]=[t1 for t1 in t if get_type(t1)==com[1]]
    mem.append(t)

def test_filter_transaction1():
    initial_list = [{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'},
                    {'date': 6, 'amount': 50, 'type': 'out', 'description': 'pizza'}]
    initial_memory = [[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'},
                       {'date': 6, 'amount': 50, 'type': 'out', 'description': 'pizza'}]]
    command = ["filter", "in"]
    filter_transaction1(initial_list, command, initial_memory)
    assert initial_list==[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'}]
    assert initial_memory==[[{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'},
                       {'date': 6, 'amount': 50, 'type': 'out', 'description': 'pizza'}],
                            [{'date': 4, 'amount': 50, 'type': 'in', 'description': 'pizza'}]]

def filter_transaction2(t,com,mem):
    """
    :param t: the list of all transactions
    :param com: the command entered by the user which contains the type and amount
    :param mem: the list of all past lists of transactions
    :return: the new transaction list and the new memory list
    """
    amount=int(com[2])
    t[:]=[t2 for t2 in t if get_type(t2)==com[1] and get_amount(t2)<amount]
    mem.append(t)

def test_filter_transaction2():
    initial_list = [{'date': 4, 'amount': 49, 'type': 'in', 'description': 'pizza'},
                    {'date': 6, 'amount': 49, 'type': 'out', 'description': 'pizza'}]
    initial_memory = [[{'date': 4, 'amount': 49, 'type': 'in', 'description': 'pizza'},
                       {'date': 6, 'amount': 49, 'type': 'out', 'description': 'pizza'}]]
    command = ["filter", "in","50"]
    filter_transaction2(initial_list, command, initial_memory)
    assert initial_list == [{'date': 4, 'amount': 49, 'type': 'in', 'description': 'pizza'}]
    assert initial_memory == [[{'date': 4, 'amount': 49, 'type': 'in', 'description': 'pizza'},
                               {'date': 6, 'amount': 49, 'type': 'out', 'description': 'pizza'}],
                              [{'date': 4, 'amount': 49, 'type': 'in', 'description': 'pizza'}]]

def undo_transaction(t,old):
    """
    :param t: the list of all transactions
    :param old: the list of all past lists of transactions
    :return: the new transaction list and the new memory list
    """
    t[:]=old[len(old)-2]
    old.pop()
def test_undo_transaction():
    initial_list = [{'date': 4, 'amount': 49, 'type': 'in', 'description': 'pizza'},
                    {'date': 6, 'amount': 49, 'type': 'out', 'description': 'pizza'}]
    initial_memory = [[{'date':4,'amount': 49, 'type': 'in', 'description': 'pizza'}],
                      [{'date': 4, 'amount': 49, 'type': 'in', 'description': 'pizza'},
                       {'date': 6, 'amount': 49, 'type': 'out', 'description': 'pizza'}]]
    undo_transaction(initial_list, initial_memory)
    assert initial_list==[{'date': 4, 'amount': 49, 'type': 'in', 'description': 'pizza'}]

def run_all_tests():
    test_add_transaction()
    test_insert_transaction()
    test_remove_transaction1()
    test_remove_transaction2()
    test_remove_transaction3()
    test_search_transaction()
    test_replace_transaction()
    test_filter_transaction1()
    test_filter_transaction2()
    test_undo_transaction()