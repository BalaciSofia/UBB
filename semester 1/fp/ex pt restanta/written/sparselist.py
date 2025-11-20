class SparseList:
    def __init__(self):
        self.data = {}  # Dictionary to store nonzero values
        self.max_index = -1  # Keeps track of the largest index set

    def __setitem__(self, index, value):
        self.data[index] = value  # Set value
        if index > self.max_index:
            self.max_index = index
    def __getitem__(self, index):
        if index in self.data:
            return self.data[index]
        return 0
    def __iter__(self):
        return SparseListIterator(self)  # Return an iterator

class SparseListIterator:
    def __init__(self, sparse_list):
        self.sparse_list = sparse_list
        self.current_index = 0  # Start from index 0

    def __iter__(self):
        return self

    def __next__(self):
        if self.current_index > self.sparse_list.max_index:
            raise StopIteration  # End of iteration
        value = self.sparse_list[self.current_index]  # Get value
        self.current_index += 1
        return value

# Test the implementation
data1 = SparseList()
data1[0] = 1
data1[2] = 2  # Only these values are stored

# Print sparse list values
for iter1 in data1:
    for iter2 in data1:
        print(iter1, iter2)  # Nested iteration
