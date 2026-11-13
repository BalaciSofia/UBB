def is_valid(v):
    n=len(v)
    #check for any length k subsequence that appears twice consecutively
    for k in range(1,n//2+1):
        if v[-k:]==v[-(2*k):-k]:
            return False
    return True
def generate_numbers(n):
    stack=[[]]
    while stack:
        l=stack.pop() #Get the last sequence from the stack
        if len(l)==n:
            print(''.join(map(str,l)))  #Print the sequence as a string
            continue
        last_digit=l[-1] if l else 0
        for digit in range(1,10):
            if digit!=last_digit:
                 l_new=l+[digit]  #Create a new sequence
                 if is_valid(l_new):
                    stack.append(l_new)  #Add the new sequence to the stack
x=int(input("Enter the number of digits: "))
generate_numbers(x)
