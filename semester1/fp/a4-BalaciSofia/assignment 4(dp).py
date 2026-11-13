"""Maximize the profit when selling a rod of length n. The rod can be cut into pieces of integer
lengths and pieces can be sold individually. The prices are known for each possible length. 
For example, if rod length n = 7, and the price array is price = [1, 5, 8, 9, 10, 17, 17] 
(the price of a piece of length 3 is 8), the maximum profit  is 18, and is obtained by cutting the rod
into 3 pieces, two of length two and one of length 3. Display the profit and the length of rod
sections sold to obtain it."""
def cutting_rod(n,v):
    memo=[0]*(n+1)#this list will contain on position i the maximum profit that can be obtained
    cuts=[0]*(n+1)#this list will contain on position i the first cut that needs to be sold for a maximum profit
    for l in range (1,n+1): #for every list length(till the one we search for) we determine the maximum profit
        for i in range(1,l+1): #for every first cut i we calculate the possible prices
            actual_price=v[i-1]+memo[l-i] #every actual price is equal to the price of the first cut(i)+the maximum profit of the remaining rod which is saved in the memo list
            if actual_price>memo[l]:#if the actual price that starts with cut i is the greatest it will be stored in memo list to be used in the next iteration
                memo[l]=actual_price
                cuts[l]=i
    print(memo)
    cut=n
    result1=" "
    result="the maximum profit  is "+str(memo[n])+" and is obtained by cutting the rod in "
    pieces=0
    while cut!=0:
        result1=result1+str(cuts[cut])
        cut=cut-cuts[cut]
        if cut!=0:result1=result1+","
        pieces=pieces+1
    result=result+str(pieces)+" pieces:"+result1
    return result
a=int(input("Enter rod length: "))
price = []
for j in range(0,a):
    x=int(input())
    price.append(x)
print(cutting_rod(a,price))