"""
14.Generate all numbers of n digits with the property that no number has two identical neighboring subsequences.
For example, for n=6, 121312 is correct, and 121313 and 132132 are not correct.
"""
def is_valid(v):
    n=len(v)
    #Check for any length k subsequence that appears twice consecutively
    for k in range(1,n//2+1):
        if v[-k:]==v[-(2*k):-k]:
            return False
    return True
def generate_numbers(n,l=None):
    if l is None:
        l=[]
    if len(l)==n:
        print(''.join(map(str,l)))
        return
    else:
        last_digit=l[-1] if l else 0
        for digit in range(1,10):
            if digit!=last_digit:
                new_l=l+[digit]
                if is_valid(new_l):
                    generate_numbers(n,new_l)
x=int(input("Enter the number of digits: "))
generate_numbers(x)
