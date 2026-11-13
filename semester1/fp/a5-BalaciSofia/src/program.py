#
# Write the implementation for A5 in this file
#
import math
# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_complex_number(a,b):
    return [a,b]
    
def get_real(lis,poz):
    return lis[poz][0]
    
def get_imag(lis,poz):
    return lis[poz][1]
    
def set_real(lis,poz,value):
    lis[poz][0] = value
    return lis[poz][0]
    
def set_imag(lis,poz,value):
    lis[poz][1] = value
    return lis[poz][1]
    
def to_string(lis,poz):
    return f"{lis[poz][0]}+{lis[poz][1]}i"

#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
"""
def create_complex_number(a, b):
    return {'real': a,'img': b}

def get_real(dicti,poz):
    return dicti[poz]['real']

def get_imag(dicti,poz):
    return dicti[poz]['img']

def set_real(dicti,poz,value):
    dicti[poz]['real'] = value
    return dicti[poz]['real']

def set_imag(dicti,poz,value):
    dicti[poz]['img'] = value
    return dicti[poz]['img']

def to_string(dicti,poz):
    return f"{dicti[poz]['real']}+{dicti[poz]['img']}i"
"""

#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def calculate_module(a,b):
    if math.sqrt(a*a+b*b)>10:
        return 11
    else:
        return int(math.sqrt(a*a+b*b))
def subarray_module_1_10(cn):
    start=0
    finish=0
    long1=-1
    long2=-1
    longest_subarray=0
    for i in range(len(cn)):
        module=calculate_module(get_real(cn,i),get_imag(cn,i))
        if 0 <= module <= 10:
            finish=i
        else:
            if finish-start>longest_subarray:
                longest_subarray=finish-start
                long1=start
                long2=finish
            start=i+1
            finish=i+1
    if finish-start>longest_subarray:
        long1=start
        long2=finish
    return long1,long2
def alternative_subsequence(cn):
    n=len(cn)
    modules=[0]*n
    for i in range(n):
        modules[i]=calculate_module(get_real(cn,i),get_imag(cn,i))
    up=[1]*n
    down=[1]*n
    parent_up=[-1]*n  #to reconstruct the subsequence
    parent_down=[-1]*n
    for i in range(1,n):
        for j in range(i):
            if modules[i]>modules[j]:
                if down[j]+1>up[i]:
                    up[i]=down[j]+1
                    parent_up[i]=j
            elif modules[i]<modules[j]:
                if up[j]+1>down[i]:
                    down[i]=up[j]+1
                    parent_down[i]=j
    #maximum length and the corresponding ending point
    max_len=0
    end_idx=-1
    is_up=True  # We need to know whether the subsequence ends in an "up" or "down"
    for i in range(n):
        if up[i]>max_len:
            max_len=up[i]
            end_idx=i
            is_up=True
        if down[i] > max_len:
            max_len = down[i]
            end_idx = i
            is_up = False
    subsequence = []
    while end_idx != -1:
        subsequence.append(cn[end_idx])
        if is_up:
            end_idx=parent_up[end_idx]
            is_up=False
        else:
            end_idx=parent_down[end_idx]
            is_up=True
    subsequence.reverse()
    return subsequence
#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#
def read_complex_number():
    a=int(input("enter real part of complex number"))
    b=int(input("enter imaginary part of complex number"))
    return create_complex_number(a,b)
def display_complex_number(cn,poz1,poz2):
    for i in range (poz1,poz2+1):
        print(to_string(cn,i))
def menu():
    print("option 1: Read a list of complex numbers")
    print("option 2: Display the entire list of numbers on the console.")
    print("option 3: A longest subarray of numbers where each number's modulus is in the [0, 10] range.")
    print("option 4: A longest alternating subsequence, when considering each number's modulus")
    print("option 5: Exit the application.")
op=0
complex_numbers=[create_complex_number(1,7),create_complex_number(9,10),create_complex_number(5,10),
                 create_complex_number(2,3),create_complex_number(5,6),create_complex_number(3,4),
                 create_complex_number(4,6),create_complex_number(3,5),create_complex_number(12,13),
                 create_complex_number(6,2)]
how_many=0
while op!=5:
    menu()
    op=int(input("enter your choice: "))
    if op==1:
        complex_numbers=[]
        how_many=int(input("Enter how many numbers you'd like to read:"))
        for _ in range(how_many):
            new=read_complex_number()
            complex_numbers.append(new)
    elif op==2:
        display_complex_number(complex_numbers,0,len(complex_numbers)-1)
    elif op==3:
        s,f=subarray_module_1_10(complex_numbers)
        print("Longest subarray of numbers with modulus between 0 and 10:")
        display_complex_number(complex_numbers,s,f)
    elif op==4:
        subseq = alternative_subsequence(complex_numbers)
        print("Longest alternating subsequence based on modulus:")
        for k in range(len(subseq)):
            print(to_string(subseq, k))
    elif op==5:
        print("Goodbye!")
    else:
        print("invalid option")



