import random
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
        if verif==False:
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
    print("option 5: Exit")
    option=int(input("Enter your choice:"))
    if option==1:
        n = int(input("Enter list length:"))
        if n==0 or n==1:
            print("Length must be greater than or equal to 2.")
            n=int(input("Enter another list length:"))
        for j in range(n):
            l.append(random.randint(0, 1000))
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
    if option==5:
        out=1
        print("Thank You!")