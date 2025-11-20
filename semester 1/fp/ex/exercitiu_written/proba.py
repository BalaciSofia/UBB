# def sum_of_even_elements(l):
#     """
#     Compute the sum of even elements in the given list.
#
#     Args:
#         l (list): The list of numbers.
#
#     Returns:
#         int: The sum of the even elements in the list.
#
#     Raises:
#         TypeError: If parameter l is not a Python list.
#         ValueError: If the list does not contain even numbers.
#     """
#     if not isinstance(l, list):
#         raise TypeError("Parameter l must be a Python list.")
#
#     even_numbers = [num for num in l if isinstance(num, (int, float)) and num % 2 == 0]
#
#     if not even_numbers:
#         raise ValueError("The list does not contain any even numbers.")
#
#     return sum(even_numbers)
#
#
# # Example usage:
# try:
#     numbers = [1, 2, 3, 4, 5, 6]
#     result = sum_of_even_elements(numbers)
#     print("Sum of even elements:", result)
# except (TypeError, ValueError) as e:
#     print(e)

"""
Created on Sep 26, 2016

@author: Arthur
"""

"""
    List
"""

myList = [1, 2, 3]
print(myList)

print(myList[1])

print('The list has', len(myList), 'elements')
print('Tha first element is', myList[0], 'and the last one is', myList[len(myList) - 1])

x = myList
#print(myList, x)

"""
    What happens here?
"""
x[1] = '?'
#print(myList, x)

"""
    List slicing
"""
myList = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
print(myList[:2])
print(myList[2:])
myList[5:] = ['a', 'b', 'c']
print(myList)

myList = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
myList[1:9] = 'x'
print(myList)

"""
    Tuple
"""
tup = 1, 2, 'a'
print(tup)
print(tup[1])

for e in tup:
    print(e)

"""
    What happens if we uncomment this line?
"""
# tup[1] = 'x'

"""
    Dictionary
"""
d = {'num': 1, 'den': 2}
print(d)

print(d['num'])
d['num'] = 99
print(d['num'])

if 'num' in d:
    print('We have num!')

del d['num']

if 'num' in d:
    print('We have num!')