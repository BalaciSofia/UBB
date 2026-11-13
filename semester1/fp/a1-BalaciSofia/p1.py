# Solve the problem from the first set here
# Problem no.2
import math
a = int(input("Enter the number: "))
def isprime (x):
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
isposible=0
for j in range(2,a//2+1):
    if isprime(j)==1 and isprime(a-j)==1 and j!=a-j:
            print("two prime numbers that add up to ",a," are ",j," and ",a-j)
            isposible=1
            break
if isposible==0 :
    print("the number can't be written as a sum of two different and prime numbers")
