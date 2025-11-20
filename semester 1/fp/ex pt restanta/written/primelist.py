class PrimeListException(Exception):
    """Custom exception for PrimeList modifications."""
    pass

class PrimeList:
    def __init__(self):
        self.primes = []

    def __is_prime(self, n):
        """Check if a number is prime."""
        if n < 2:
            return False
        for i in range(2, int(n ** 0.5) + 1):
            if n % i == 0:
                return False
        return True

    def __getitem__(self, index):
        """Return the prime number at the requested index, generating if necessary."""
        i=0
        prime=2
        while i<index+1:
            if self.__is_prime(prime):
                i+=1
            prime+=1
            if i==index+1:
                return prime-1

    def __setitem__(self, index, value):
        """Raise an exception since the list is read-only."""
        raise PrimeListException("List is read only")

# Example usage
data = PrimeList()
for i in range(10):
    print(data[i])  # Should print the first 10 prime numbers

print(data[100])  # Should print the 101st prime number

try:
    data[5] = 10  # Should raise an exception
except PrimeListException as ple:
    print(ple)  # Should print "List is read only"

