# Solve the problem from the third set here
# Problem no.13
import math
n=int(input("enter the index of the element: "))
def prime (x):
    if x < 2:
        return 0
    if x == 2:
        return 1
    if x % 2 == 0 and x != 2:
        return 0
    for i in range(3, int(math.sqrt(x)) + 1, 2):
        if x % i == 0:
            return 0
    return 1
def find(y):
    if y<4:
        return y
    nr=4
    y=y-3
    while y!=0:
        aux=nr
        if prime(nr)==1:
            y=y-1
            if y==0: return nr
        else:
            for d in range(2,nr//2+1):
                if nr%d==0:
                    y=y-1
                if y==0:return d
                while nr%d==0:
                    nr=nr//d
        nr=aux+1
print("the",n,"-th element of the sequence is ",find(n))
# 1 2 3 2 5 2 3 7 2 3 2 5 2 3 13