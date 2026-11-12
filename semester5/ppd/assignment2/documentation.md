# Lab 2 - Applying a convolution matrix in place

## 1. Requirements analysis

Same problem as Lab 1 (k = 3, nearest border element used outside F), but at the end F itself must contain the filtered image. No other result or temporary matrix may be allocated, only temporary vectors of total size O(n). Required: sequential and rows versions, in Java and C++ (dynamic allocation).

## 2. Design

The new row i depends on the original rows i - 1, i and i + 1, so each row must be saved before it is overwritten.

**Sequential** (2 vectors of size m): `prev` holds the original row i - 1 and `cur` a copy of row i. Row i + 1 is not modified yet, so it is read from F. The new row i is written into F, then `prev` and `cur` are swapped.

**Parallel - variant 1b.** Each thread gets a block of consecutive rows (n / p each, the first n % p threads get one more):

1. it copies the row above and the row below its block (they belong to the neighbour threads);
2. **barrier** - nobody writes into F before all threads copied their boundaries;
3. it runs the sequential algorithm on its rows, using the copied row below its last row.

**Structure** (same as Lab 1):

| Component | Java | C++ | Role |
|---|---|---|---|
| Main | `Main` | `main.cpp` | arguments, timing |
| Convolution | `Convolution`, `MyThreadOne` | `Convolution.cpp` | sequential and rows (1b) versions |
| InputOutput | `InputOutput` | `InputOutput.cpp` | read `date.txt`, check result, write `output.txt` |
| GenerateAndWriteMatrices | `GenerateAndWriteMatrices` | `GenerateAndWriteMatrices.cpp` | random `date.txt` and `expectedResult.txt` |
| FileManager, RandomNumberGenerator | same names | same names | matrix files, random numbers |

## 3. Implementation details

- Explicit threads (`Thread` subclass in Java, `std::thread` in C++); barrier: `CyclicBarrier` in Java, `std::barrier` (C++20) in C++.
- `date.txt` contains F, an empty line and the 3 x 3 matrix C; the same file was used for Java and C++.
- After each execution F is compared with `expectedResult.txt` (produced by the sequential version) and written to `output.txt`.
- Only the computation is timed; `run.ps1` runs a program 10 times and prints the mean.

## 4. Test cases

10 x 10 (p = 2), 1000 x 1000 and 10000 x 10000 (p = 2, 4, 8, 16), k = 3, plus the sequential version for each size; 10 runs each, all results correct. Environment: AMD Ryzen 5 4500U (6 cores), Windows 11, Java 25, C++20 with MinGW g++ `-O3`.

## 5. Results

Mean of 10 runs, time in ms (computation only). Speedup = Tseq / Tpar.

### 5.1 Java

| Matrix size | Variant | No. threads | Execution time (ms) | Speedup |
|---|---|---|---|---|
| 10 x 10 | sequential | 1 | 0.588 | 1 |
| 10 x 10 | rows | 2 | 3.717 | 0.158 |
| 1000 x 1000 | sequential | 1 | 20.06 | 1 |
| 1000 x 1000 | rows | 2 | 27.66 | 0.725 |
| 1000 x 1000 | rows | 4 | 36.37 | 0.551 |
| 1000 x 1000 | rows | 8 | 36.06 | 0.556 |
| 1000 x 1000 | rows | 16 | 36.13 | 0.555 |
| 10000 x 10000 | sequential | 1 | 425.2 | 1 |
| 10000 x 10000 | rows | 2 | 224.7 | 1.893 |
| 10000 x 10000 | rows | 4 | 141.2 | 3.010 |
| 10000 x 10000 | rows | 8 | 114.8 | 3.703 |
| 10000 x 10000 | rows | 16 | 117.4 | 3.623 |

### 5.2 C++

| Matrix size | Allocation type | Variant | No. threads | Execution time (ms) | Speedup |
|---|---|---|---|---|---|
| 10 x 10 | dynamic | sequential | 1 | 0.0011 | 1 |
| 10 x 10 | dynamic | rows | 2 | 0.548 | 0.002 |
| 1000 x 1000 | dynamic | sequential | 1 | 3.023 | 1 |
| 1000 x 1000 | dynamic | rows | 2 | 3.069 | 0.985 |
| 1000 x 1000 | dynamic | rows | 4 | 2.406 | 1.256 |
| 1000 x 1000 | dynamic | rows | 8 | 2.017 | 1.499 |
| 1000 x 1000 | dynamic | rows | 16 | 2.649 | 1.141 |
| 10000 x 10000 | dynamic | sequential | 1 | 293.6 | 1 |
| 10000 x 10000 | dynamic | rows | 2 | 144.4 | 2.033 |
| 10000 x 10000 | dynamic | rows | 4 | 77.57 | 3.785 |
| 10000 x 10000 | dynamic | rows | 8 | 79.35 | 3.700 |
| 10000 x 10000 | dynamic | rows | 16 | 70.43 | 4.168 |

### 5.3 Best variant for each matrix size

| Matrix size | Best Java | Best C++ |
|---|---|---|
| 10 x 10 | sequential (0.588 ms) | sequential (0.0011 ms) |
| 1000 x 1000 | sequential (20.06 ms) | rows, 8 threads (2.017 ms) |
| 10000 x 10000 | rows, 8 threads (114.8 ms) | rows, 16 threads (70.43 ms) |

## 6. Results analysis

- **Small matrices** (10 x 10, and 1000 x 1000 in Java): the work is too small, so starting the threads costs more than it saves. In Java the parallel 1000 x 1000 is even slower than the sequential one, probably because each run starts a new JVM and the JIT compiler competes with the worker threads at the start.
- **10000 x 10000:** the parallel version pays off, with speedups up to 4.2 in C++ and 3.7 in Java. Above 4 - 8 threads the time stays flat, which fits the 6 cores of the machine.
- **Java against C++:** C++ is faster in every case. The gap is large for small inputs and only about 1.5x for 10000 x 10000, so most of it comes from the JVM warm-up; the rest from array bounds checks and less vectorization than g++ `-O3`.
- **Space complexity:** Lab 1 needed a result matrix, O(n · m) (400 MB for 10000 x 10000). Here the sequential version uses 2 vectors of m ints, O(m), and the parallel one 3 vectors of m ints per thread, O(p · m) (1.92 MB for p = 16), which is O(n) for a fixed p. The other variants (1f, 2b, 2f) also need O(p · m); 1b is the simplest of them.
