
def cutting_rod(price,n):
    if n==0:#base case
        return 0," "
    max_val=-1 #maximal profit
    cuts=" " #stores the cuts it made to obtain the maximum profit
    for i in range(1,n+1): #for every first cut i
        actual_price=price[i-1]+cutting_rod(price,n-i)[0]
        next_cuts=cutting_rod(price,n-i)[1]
        if actual_price>max_val:
            max_val=actual_price
            cuts=str(i)+" "+next_cuts
    return max_val,cuts
a=int(input("Enter rod length: "))
l= []
for j in range(0,a):
    x=int(input())
    l.append(x)
result="the maximum profit  is "+str(cutting_rod(l,a)[0])+" and is obtained by cutting the rod in pieces:"+cutting_rod(l,a)[1]
print(result)