class FibMatrixIterator:
    def __init__(self, dim, add):
        self.__dim = dim
        self.__add = add
        self.__pos = -1
        self.__a = 0
        self.__b = 0
        self.__c = 1

    def __next__(self):
        self.__pos += 1
        if self.__pos == self.__dim * self.__dim:
            raise StopIteration
        self.__a = self.__b
        self.__b = self.__c
        self.__c = self.__a + self.__b
        return self.__a + self.__add

class FibMatrix:
    def __init__(self, dim):
        self.__dim = dim
        self.__add = 0

    def __add__(self, other: int):
        current_mat = FibMatrix(self.__dim)
        current_mat.__add = self.__add + other
        return current_mat

    def __str__(self):
        a = 0
        b = 1
        mat = ""
        for i in range(self.__dim):
            for j in range(self.__dim):
                mat = mat + str(a + self.__add) + " "
                c = a + b
                a = b
                b = c
            mat = mat + "\n"
        return mat

    def __iter__(self):
        return FibMatrixIterator(self.__dim, self.__add)

fm = FibMatrix(3)
print(fm)
fm = fm + 10
print(fm)
for i in fm:
    print(i)