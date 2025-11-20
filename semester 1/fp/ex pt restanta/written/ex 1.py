# class A:
#     def __str__(self):
#         return "a"
#
# class B(A):
#     def __init__(self, a=None):
#         self._a = a
#
#     def __str__(self):
#         return str(self._a) + "b" + A.__str__(self)
#
# a = A()
# print(a)
#
# b = B(a)
# print(b)
#
# c = B(b)
# print(c)


a=1
def f(a):
    a=2
def g(a):
    a[0]=2
x=3
f(x)
print(a)
print(x)
x=[3,3]
g(x)
print(x)
x=str(x)
print(x)