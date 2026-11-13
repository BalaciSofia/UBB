#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#

import random
import functions
from texttable import Texttable

from src.functions import insert_transaction, remove_transaction1, remove_transaction2, remove_transaction3, \
    replace_transaction, filter_transaction1, filter_transaction2, undo_transaction


def print_possible_commands():
    print("Please use the following commands accordingly:")
    print("To add a transaction enter:")
    print("\t->add <value> <type> <description>")
    print("\t->insert <day> <value> <type> <description>")
    print("To modify a transaction enter:")
    print("\t->remove <day>")
    print("\t->remove <start day> to <end day>")
    print("\t->remove <type>")
    print("\t->replace <day> <type> <description> with <value>")
    print("To display al transactions having different properties enter:")
    print("\t-> list")
    print("\t->list <type>")
    print("\t->list [ < | = | > ] <value>")
    print("\t->list balance <day>")
    print("To filter enter")
    print("\t->filter <type>")
    print("\t->filter <type> <value>")
    print("To undo enter:")
    print("\t->undo")
    print("To exit enter:")
    print("\t->exit")


def command_add(command,transaction_list,transaction_memory):
    """
    command[1] is int and>0
    command[2] is str and is in or out
    command[3] is str whatever
    add <value> <type> <description>
    """
    try:
        if len(command)!=4:
            raise ValueError("Invalid command! Reminder : add <value> <type> <description>")
        try:
            value=int(command[1])
        except ValueError:
            raise ValueError("The value must be an integer")
        if value<=0:
            raise ValueError("The value must be greater than 0")
        if command[2]!="in" and command[2]!="out":
            raise ValueError("The type must be either <in> or <out>")
        functions.add_transaction(transaction_list,command,transaction_memory)
        print("Transaction added successfully")
    except ValueError as err:
        print(err)

def command_insert(command,transaction_list,transaction_memory):
    """
    command[1] is int 0<command[1]<31
    command[2] is int and >0
    command[3] is str and is in or out
    command[4] is str whatever
    insert <day> <value> <type> <description>
    """
    try:
        if len(command)!=5:
            raise ValueError("Invalid command. Reminder: insert <day> <value> <type> <description>")
        try:
            day=int(command[1])
            value=int(command[2])
        except ValueError:
            raise ValueError("The day and value must be integers")
        if not 1<=day<31:
            raise ValueError("The day must be between 1 and 31")
        if value<=0:
            raise ValueError("The value must be greater than 0")
        if command[3]!="in" and command[3]!="out":
            raise ValueError("The type must be either <in> or <out>")
        insert_transaction(transaction_list,command,transaction_memory)
        print("Transaction inserted successfully")
    except ValueError as err:
        print(err)

def command_remove(command,transaction_list,transaction_memory):
    """
    remove <day>
    *0<day<31
    remove <start day> to <end day>
    *start day<end day
    remove <type>
    *type==in/out
    """
    try:
        if len(command)==2:
            if command[1].isdigit():
                day=int(command[1])
                if not 0 < day < 31:
                    raise ValueError("The day must be between 1 and 31")
                remove_transaction1(transaction_list, command, transaction_memory)
                print("Transaction removed successfully")
            elif command[1]!="in" and command[1]!="out":
                raise ValueError("The second argument must be either a day or a type")
            else:
                 remove_transaction2(transaction_list,command,transaction_memory)
                 print("Transaction removed successfully")
        elif len(command)==4 and command[2]=="to":
            try:
                if command[1].isdigit() and command[3].isdigit():
                    start_day=int(command[1])
                    end_day=int(command[3])
                    if not 31>start_day>0 or not 31>end_day>0:
                        raise ValueError("The day must be between 1 and 31")
                    if start_day>=end_day:
                        raise ValueError("The start day must be less than the end day")
                    remove_transaction3(transaction_list,command,transaction_memory)
                    print("Transaction removed successfully")
                else:
                    raise ValueError("The days must be integers")
            except ValueError as e:
                print(e)
        else:
            raise ValueError("The remove command is invalid!")
    except ValueError as err:
        print(err)

def command_replace (command,transaction_list,transaction_memory):
    """
    replace <day> <type> <description> with <value>
    day int >0,<31
    type in/out
    value int>0
    """
    try:
        if len(command)!=6:
            raise ValueError("The command is invalid.Reminder: replace <day> <type> <description> with <value>")
        if command[4]!="with":
            raise ValueError("The command is invalid.Reminder: replace <day> <type> <description> with <value>")
        if command[2]!="in" and command[2]!="out":
            raise ValueError("The type must be either <in> or <out>")
        try:
            day=int(command[1])
            value=int(command[5])
            if day<1 or day>30:
                print("The day must be between 1 and 31")
                return
        except:
            raise ValueError("The day and value must be integers")
        if value<=0:
            raise ValueError("The value must be greater than 0")

        if functions.search_transaction(transaction_list,command)==0:
            raise ValueError("The transaction you entered does not exist")
        replace_transaction(transaction_list,command,transaction_memory)
    except ValueError as err:
        print(err)

def command_list (command,transaction_list,transaction_memory):
    t = Texttable()
    t.add_row(["index", "day", "amount", "type", "description"])
    if len(command)==1:
        for i in range (len(transaction_list)):
            t.add_row([i,transaction_list[i]['date'],transaction_list[i]['amount'],transaction_list[i]['type'],transaction_list[i]['description']])
        print(t.draw())
    elif len(command)==2:
        if command[1]!="in" and command[1]!="out":
            print("The type must be either <in> or <out>")
            return
        else:
            for i in range (len(transaction_list)):
                if transaction_list[i]['type']==command[1]:
                    t.add_row([i,transaction_list[i]['date'],transaction_list[i]['amount'],transaction_list[i]['type'],transaction_list[i]['description']])
            print(t.draw())
    elif len(command)==3:
        if command[1] in ["<","=",">"]:
            try:
                value=int(command[2])
                for i in range (len(transaction_list)):
                    if (command[1]=="<" and transaction_list[i]['amount']<value) or(command[1]==">" and transaction_list[i]['amount']>value) or (command[1]=="=" and transaction_list[i]['amount']==value):
                        t.add_row([i,transaction_list[i]['date'],transaction_list[i]['amount'],transaction_list[i]['type'],transaction_list[i]['description']])
                print(t.draw())
            except ValueError:
                print("The value must be an integer")
                return
        elif command[1]=="balance":
            try:
                day=int(command[2])
                if day<=0 or day>=31:
                    print("The day must be between 1 and 31")
                    return
                balance = (
                        sum(transaction_list[i]['amount']
                            for i in range(len(transaction_list))
                            if transaction_list[i]['type'] == 'in' and transaction_list[i]['date'] <= day)
                        -
                        sum(transaction_list[i]['amount']
                            for i in range(len(transaction_list))
                            if transaction_list[i]['type'] == 'out' and transaction_list[i]['date'] <= day)
                )
                print("the balance for day",day,"is", balance)
                return
            except ValueError:
                print("The day must be an integer")
        else:
            print("The list command is invalid")
    else:
        print("The list command is invalid")

def command_filter(command,transaction_list,transaction_memory):
    """
    filter <type>
    filter <type> <value>
    """
    try:
        if len(command)==2:
            if command[1]=="in" or command[1]=="out":
                filter_transaction1(transaction_list,command,transaction_memory)
            else:
                raise ValueError("The type must be either <in> or <out>")
        elif len(command)==3:
            if command[1]!="in" and command[1]!="out":
                raise ValueError("The type must be either <in> or <out>")
            else:
                if command[2].isdigit():
                    value=int(command[2])
                    if value>0:
                        filter_transaction2(transaction_list,command,transaction_memory)
                    else:
                        raise ValueError("The value must be greater than 0")
                else:
                    raise ValueError("The value must be an integer")
        else:
            raise ValueError("invalid command")
    except ValueError as err:
        print(err)

def command_undo (command,transaction_list,transaction_memory):
    if len(command)!=1:
        print("The command is invalid")
        return
    else:
        if len(transaction_memory)==1:
            print("No more undo s")
        else:
            undo_transaction(transaction_list,transaction_memory)
def main_loop():
    commands = {
        "add": command_add,
        "insert": command_insert,
        "remove": command_remove,
        "replace": command_replace,
        "list": command_list,
        "filter": command_filter,
        "undo": command_undo
    }
    transaction_list = [{
        'date': random.randint(1, 30),
        'amount': random.randint(1, 1000),
        'type': random.choice(["in", "out"]),
        'description': random.choice(["salary", "pizza", "groceries", "rent"])
    } for _ in range(10)]
    transaction_memory = [transaction_list[:]]
    while True:
        command = input("\nEnter a command (or type 'help' for options): ").strip().lower()
        if command == "help":
            print_possible_commands()
        elif command == "exit":
            print("Thank you for using this program!")
            break
        elif command== "":
            print("No command entered")
        else:
            command=command.split()
            command_name=command[0].strip()
            if not command_name in commands:
                print("This command does not exist")
                continue
            else:
                select_command=commands.get(command_name)
                select_command(command, transaction_list, transaction_memory)

