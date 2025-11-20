

#ex1:YYXYYX


#ex2:

class PrimeListException(Exception):
    """Custom exception for PrimeList."""
    pass

class PrimeList:
    def __init__(self):
        self._primes = []  # List to store calculated primes

    def __is_prime(self, num):
        """Helper function to check if a number is prime."""
        if num < 2:
            return False
        for i in range(2, int(num**0.5) + 1):
            if num % i == 0:
                return False
        return True

    def __generate_primes_up_to(self, index):
        """Generate primes up to the requested index."""
        n = 2  # Start checking for primes from 2
        while len(self._primes) <= index:
            if self.__is_prime(n):
                self._primes.append(n)
            n += 1

    def __getitem__(self, index):
        """Handle indexing to dynamically grow the list."""
        if index < 0:
            raise IndexError("Negative indexing is not supported.")
        self.__generate_primes_up_to(index)
        return self._primes[index]

    def __setitem__(self, index, value):
        """Make the list read-only by raising an exception."""
        raise PrimeListException("List is read only")

# Example usage:
data = PrimeList()
# Print the first 10 primes
for i in range(10):
    print(data[i])  # Prints: 2 3 5 7 11 13 17 19 23 29

# Access the 100th prime
print(data[100])  # Prints: 547

# Test exception when trying to modify the list
try:
    data[5] = 10
except PrimeListException as ple:
    print(ple)  # Prints: List is read only


#ex3:0(n^3*log10n)