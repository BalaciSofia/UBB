import random
import time
from texttable import Texttable

'''
----------------------------------------------------------------------------------------------------------------
functions for assignment 2
----------------------------------------------------------------------------------------------------------------
'''
#exponential search
def search(x,s):    #x-the list s-searched number
    i = 1
    while i < len(x) and x[i] < s:
        i*=2
    left=i//2
    right = min(i,len(x)-1)
    while left <= right:
        mid=(left+right)//2
        if x[mid]==s:
            return mid
        else:
            if x[mid]<s:
                left=mid+1
            else:
                 right=mid-1
    return -1
#Cocktail Sort
def sort1(x,step):
    print("step 0:",x)
    verif=True
    front=0
    back=len(x)-1
    contor=0
    while verif:
        verif=False
        for i in range(front,back):
            if x[i]>x[i+1]:
                aux=x[i]
                x[i]=x[i+1]
                x[i+1]=aux
                verif=True
                contor+=1
                if contor%step==0:
                    print("step:",contor,"list",x)
        if not verif:
            return x
        verif=False
        back-=1
        for i in range(back-1,front-1,-1):
            if x[i]>x[i+1]:
                aux=x[i]
                x[i]=x[i+1]
                x[i+1]=aux
                verif=True
                contor+= 1
                if contor%step==0:
                    print("step:", contor, "list:", x)
        front+=1
    return x
#Comb Sort
def nextgap(gap):
    gap=(gap * 10)//13
    if gap < 1:
        return 1
    return gap
def sort2(x,step):
    print("step 0:",x)
    gap=len(x)
    verif=True
    contor=0
    while gap!=1 or verif==True:
        gap=nextgap(gap)
        verif=False
        for i in range(0,len(x)-gap):
            if x[i]>x[i+gap]:
                aux = x[i]
                x[i] = x[i + 1]
                x[i + 1] = aux
                verif = True
                contor += 1
                if contor%step==0:
                    print("step:", contor, "list:", x)
    return x
'''
-----------------------------------------------------------------------------------------------------------------
functions for assignment 3
-----------------------------------------------------------------------------------------------------------------
'''
'''
-----------------------------------------------------------------------------------------------------------------
Cocktail Sort
'''
def sort1_3(x):
    verif=True
    front=0
    back=len(x)-1
    while verif:
        verif=False
        for i in range(front,back):
            if x[i]>x[i+1]:
                aux=x[i]
                x[i]=x[i+1]
                x[i+1]=aux
                verif=True
        if not verif:
            return x
        verif=False
        back-=1
        for i in range(back-1,front-1,-1):
            if x[i]>x[i+1]:
                aux=x[i]
                x[i]=x[i+1]
                x[i+1]=aux
        front+=1
    return x
'''
best case: O(n)
->when the list is already sorted//it goes forward once, no swaps were made so it stops
worst case:O(n^2)
->when the list is sorted in reverse order//this means the biggest number is at the front and it takes n swaps
for it to arrive in it s right spot, the same happens for every element of the list

'''
def best1(lis):
    sort1_3(lis)#sorted
    t1_start = time.perf_counter()
    sort1_3(lis)
    t1_stop=time.perf_counter()
    result=t1_stop-t1_start
    return result
def worst1(lis):
    lis=sorted(lis, reverse=True)#sorted in reverse
    t1_start = time.perf_counter()
    sort1_3(lis)
    t1_stop = time.perf_counter()
    result = t1_stop - t1_start
    return result
def average1(lis):
    t1_start = time.perf_counter()
    sort1_3(lis)
    t1_stop = time.perf_counter()
    result = t1_stop - t1_start
    return result
'''
------------------------------------------------------------------------------------------------------------------
Comb Sort
'''
def nextgap_3(gap):
    gap=(gap * 10)//13
    if gap < 1:
        return 1
    return gap
def sort2_3(x):
    gap=len(x)
    verif=True
    while gap!=1 or verif==True:
        gap=nextgap_3(gap)
        verif=False
        for i in range(0,len(x)-gap):
            if x[i]>x[i+gap]:
                aux = x[i]
                x[i] = x[i + 1]
                x[i + 1] = aux
                verif = True
    return x
'''
best case: O(nlogn)
->when the list is already sorted//
1 2 3 4 5 6 7 8
gap=8
gap=6//i=0,2 compares 1 with 7, 2 with 8
gap=4//i=0,4 compares 1 with 5, 2 with 6, 3 with 7, 4 with 8
gap=3//i=0,5 compares 1 with 4, 2 with 5, 3 with 6, 4 with 7, 5 with 8
gap=2//i=0,6 compares 1 with 3, 2 with 4, 3 with 5, 4 with 6, 5 with 7, 6 with 8
gap=1 done 
Since the algorithm effectively skips many comparisons due to the shrinking gap,
it quickly confirms that no swaps are needed.
worst case: O(n^2)
->when the list is sorted in reverse order//
'''
def best2(lis):
    sort2_3(lis)#let it be already sorted
    t2_start = time.perf_counter()
    sort2_3(lis)
    t2_stop=time.perf_counter()
    result=t2_stop-t2_start
    return result
def worst2(lis):
    lis=sorted(lis, reverse=True)#sorted in reverse
    t2_start = time.perf_counter()
    sort2_3(lis)
    t2_stop = time.perf_counter()
    result = t2_stop - t2_start
    return result
def average2(lis):
    t2_start = time.perf_counter()
    sort2_3(lis)
    t2_stop = time.perf_counter()
    result = t2_stop - t2_start
    return result
'''
--------------------------------------------------------------------------------------------------------------------
main
'''
out=0
first=0
second=0
third=0
l=[]
l1=[]
while out==0:
    print("option 1: Generate random list")
    print("option 2: Sort list using Cocktail Sort")
    print("option 3: Sort list using Comb Sort")
    print("option 4: Search wanted element in list")
    print("option 5: Best case")
    print("option 6: Worst case")
    print("option 7: Average case")
    print("option 8: Exit")
    option=int(input("Enter your choice:"))
    if option==1:
        m= int(input("Enter list length:"))
        if m==0 or m==1:
            print("Length must be greater than or equal to 2.")
            m=int(input("Enter another list length:"))
        l=[random.randint(0, 1000) for _ in range(m)]
        l1=l[:]
        print("The random generated list is:")
        print(l)
        first=1
        second=0
        third=0
    if option==2:
        if first==0: print("The list wasn't generated yet. Please generate one to use this option")
        else:
            steps=int(input("Enter step size:"))
            if third==1:
                print("The final sorted list:", sort1(l1,steps))
            else:
                print("The final sorted list:",sort1(l,steps))
            second=1
    if option==3:
        if first==0: print("The list wasn't generated yet. Please generate one to use this option")
        else:
            steps1 = int(input("Enter step size:"))
            if second==1:
                print("The final sorted list:", sort2(l1, steps1))
            else:
                print("The final sorted list:", sort2(l, steps1))
            third=1
    if option==4:
        if first==0: print("The list wasn't generated yet. Please generate one to use this option")
        else:
            if second==0 and third==0: print("The list isn't sorted yet. Please use option 2 or 3 before this option")
            else:
                numb = int(input("Enter searched number:"))
                y=search(l,numb)
                if y==-1:
                    print("The searched element was not found")
                else: print("The searched element is found at position",y)
    if option==5:#best case using l_1 ;rez1_1 & best1 for cocktail;rez1_2 & best2 for comb;
        p=int(input("Enter the starting length:"))
        t = Texttable()
        t.add_row(['number of elements','cocktail sort','unit','comb sort','unit'])
        for k in range(0,5):
            l_1 = [random.randint(0, 1000) for _ in range((2**k)*p)]
            if best1(l_1)<1:
                rez1_1=best1(l_1)*1000
                if best2(l_1)<1:
                    rez1_2=best2(l_1)*1000
                    t.add_row([(2**k)*p,rez1_1,'milliseconds',rez1_2,'milliseconds'])
                else:
                    rez1_2=best2(l_1)
                    t.add_row([(2**k)*p,rez1_1,'milliseconds',rez1_2,'seconds'])
            else:
                rez1_1=best1(l_1)
                if best2(l_1)<1:
                    rez1_2=best2(l_1)*1000
                    t.add_row([(2**k)*p,rez1_1,'seconds',rez1_2,'milliseconds'])
                else:
                    rez1_2=best2(l_1)
                    t.add_row([(2**k)*p,rez1_1,'seconds',rez1_2,'seconds'])
        print("BEST CASE")
        print(t.draw())
    if option==6:#worst case;using l_2;rez2_1 & worst1 for cocktail; rez2_2 & worst2 for comb
        p=int(input("Enter the starting length:"))
        t = Texttable()
        t.add_row(['number of elements', 'cocktail sort','unit', 'comb sort','unit'])
        for k in range(0, 5):
            l_2 = [random.randint(0, 1000) for _ in range((2**k)*p)]
            if worst1(l_2)<1:
                rez2_1=worst1(l_2)*1000
                if worst2(l_2)<1:
                    rez2_2=worst2(l_2)*1000
                    t.add_row([(2**k)*p,rez2_1,'milliseconds',rez2_2,'milliseconds'])
                else:
                    rez2_2=worst2(l_2)
                    t.add_row([(2**k)*p,rez2_1,'milliseconds',rez2_2,'seconds'])
            else:
                rez2_1=worst1(l_2)
                if worst2(l_2)<1:
                    rez2_2=worst2(l_2)*1000
                    t.add_row([(2**k)*p,rez2_1,'seconds',rez2_2,'milliseconds'])
                else:
                    rez2_2=worst2(l_2)
                    t.add_row([(2**k)*p,rez2_1,'seconds',rez2_2,'seconds'])
        print("WORST CASE")
        print(t.draw())
    if option==7:
        p=int(input("Enter the starting length:"))
        t = Texttable()
        t.add_row(['number of elements', 'cocktail sort','unit', 'comb sort','unit'])
        for k in range(0, 5):
            l_3 = [random.randint(0, 1000) for _ in range((2**k)*p)]
            if average1(l_3)<1:
                rez3_1=average1(l_3)*1000
                if average2(l_3)<1:
                    rez3_2=average2(l_3)*1000
                    t.add_row([(2**k)*p,rez3_1,'milliseconds',rez3_2,'milliseconds'])
                else:
                    rez3_2=average2(l_3)
                    t.add_row([(2**k)*p,rez3_1,'milliseconds',rez3_2,'seconds'])
            else:
                rez3_1=average1(l_3)
                if average2(l_3)<1:
                    rez3_2=average2(l_3)*1000
                    t.add_row([(2**k)*p,rez3_1,'seconds',rez3_2,'milliseconds'])
                else:
                    rez3_2=average2(l_3)
                    t.add_row([(2**k)*p,rez3_1,'seconds',rez3_2,'seconds'])
        print("AVERAGE CASE")
        print(t.draw())
    if option==8:
        out=1
        print("Thank You!")