# Solve the problem from the second set here
# Problem no.11
a=int(input("Enter first number: "))
b=int(input("Enter second number: "))
def samenumb(x,y):
    while x > 0:
        aux = y
        e = 0
        while aux > 0:
            if x % 10 == aux % 10:
                e = 1
            aux = aux // 10
        if e == 0:
            return 0
        x = x // 10
    return 1
def propertyp(x,y):
    if samenumb(x,y)==1 and samenumb(y,x)==1 : return 1
    else: return 0
if propertyp(a,b)==1 :
    print("the given numbers have property P")
else:
    print("the given numbers do not have property P")
