# Lab 1 - Applying a convolution matrix with threads

## 1. Requirements analysis

Given an n x m matrix F and a k x k convolution matrix C (k odd), compute the n x m matrix V in which every element is the sum of the products between C and the neighborhood of the same element in F, with the nearest border element used outside F. The computation is done sequentially and in parallel with p threads, by blocks of rows or blocks of columns, in Java and in C++ (static and dynamic allocation), and the performance of the variants is compared.

## 2. Design

**Data.** F, C and V are `int[][]` in Java, `int[N][M]` in C++ static (sizes fixed at compile time, so it is rebuilt for each test case) and a flat `int*` in C++ dynamic.

**Distribution.** Each thread gets a block of consecutive rows (or columns): L / p each, and the first L % p threads get one more. Threads write different parts of V, so only `join` is needed.

**Structure** (same in Java and C++):

| Component | Java | C++ | Role |
|---|---|---|---|
| Main | `Main` | `main.cpp` | arguments, timing |
| Convolution | `Convolution`, `MyThreadOne`, `MyThreadTwo` | `Convolution.cpp` | sequential, rows and columns versions |
| InputOutput | `InputOutput` | `InputOutput.cpp` | read input, check result, write `output.txt` |
| GenerateAndWriteMatrices | `GenerateAndWriteMatrices` | `GenerateAndWriteMatrices.cpp` | random inputs and `expectedResult.txt` |
| FileManager, RandomNumberGenerator | same names | `common/` | matrix files, random numbers |

## 3. Implementation details

- Explicit threads only: `Thread` subclasses in Java, `std::thread` in C++, started and joined in `applyConvolutionParallelRows` / `applyConvolutionParallelCols`.
- The inputs are read from `MatrixF.txt` and `ConvolutionM.txt`. After each execution the result is compared in memory with `expectedResult.txt` (produced by the sequential version) and then written to `output.txt`.
- Only the computation is timed (`System.nanoTime()` / `std::chrono`); `run.ps1` runs a program 10 times and prints the mean.

## 4. Test cases

The 5 cases of the assignment, each with the sequential, rows and columns versions, 10 runs each, on the same input files for Java, C++ static and C++ dynamic. Environment: AMD Ryzen 5 4500U (6 cores), Windows, Java 25, C++20 with MinGW g++ `-O3`.

## 5. Results

Mean of 10 runs, time in ms (computation only). Speedup = Tseq / Tpar for the same language, allocation type and matrix size.

### 5.1 Java

| Matrix size | Variant | No. threads | Execution time (ms) | Speedup |
|---|---|---|---|---|
| 10 x 10, k=3 | sequential | 1 | 0.061 | 1 |
| 10 x 10, k=3 | rows | 4 | 2.382 | 0.026 |
| 10 x 10, k=3 | columns | 4 | 1.965 | 0.031 |
| 1000 x 1000, k=3 | sequential | 1 | 49.7 | 1 |
| 1000 x 1000, k=3 | rows | 2 | 40.4 | 1.232 |
| 1000 x 1000, k=3 | columns | 2 | 52.8 | 0.942 |
| 1000 x 1000, k=3 | rows | 4 | 26.7 | 1.863 |
| 1000 x 1000, k=3 | columns | 4 | 58.7 | 0.847 |
| 1000 x 1000, k=3 | rows | 8 | 29.9 | 1.663 |
| 1000 x 1000, k=3 | columns | 8 | 65.2 | 0.763 |
| 1000 x 1000, k=3 | rows | 16 | 29.3 | 1.697 |
| 1000 x 1000, k=3 | columns | 16 | 78.6 | 0.633 |
| 10 x 10000, k=5 | sequential | 1 | 19.4 | 1 |
| 10 x 10000, k=5 | rows | 2 | 47.2 | 0.412 |
| 10 x 10000, k=5 | columns | 2 | 39.9 | 0.487 |
| 10 x 10000, k=5 | rows | 4 | 73.9 | 0.263 |
| 10 x 10000, k=5 | columns | 4 | 50.8 | 0.382 |
| 10 x 10000, k=5 | rows | 8 | 80.6 | 0.241 |
| 10 x 10000, k=5 | columns | 8 | 83.5 | 0.233 |
| 10 x 10000, k=5 | rows | 16 | 65.2 | 0.298 |
| 10 x 10000, k=5 | columns | 16 | 91.2 | 0.213 |
| 10000 x 10, k=5 | sequential | 1 | 19.5 | 1 |
| 10000 x 10, k=5 | rows | 2 | 20.6 | 0.949 |
| 10000 x 10, k=5 | columns | 2 | 61.4 | 0.318 |
| 10000 x 10, k=5 | rows | 4 | 26.7 | 0.729 |
| 10000 x 10, k=5 | columns | 4 | 46.0 | 0.424 |
| 10000 x 10, k=5 | rows | 8 | 44.5 | 0.438 |
| 10000 x 10, k=5 | columns | 8 | 57.0 | 0.342 |
| 10000 x 10, k=5 | rows | 16 | 56.9 | 0.343 |
| 10000 x 10, k=5 | columns | 16 | 63.6 | 0.307 |
| 10000 x 10000, k=5 | sequential | 1 | 6816.0 | 1 |
| 10000 x 10000, k=5 | rows | 2 | 4204.7 | 1.621 |
| 10000 x 10000, k=5 | columns | 2 | 9729.9 | 0.701 |
| 10000 x 10000, k=5 | rows | 4 | 2443.8 | 2.789 |
| 10000 x 10000, k=5 | columns | 4 | 5240.3 | 1.301 |
| 10000 x 10000, k=5 | rows | 8 | 2852.5 | 2.389 |
| 10000 x 10000, k=5 | columns | 8 | 4182.8 | 1.630 |
| 10000 x 10000, k=5 | rows | 16 | 1597.2 | 4.267 |
| 10000 x 10000, k=5 | columns | 16 | 3967.9 | 1.718 |

### 5.2 C++

| Matrix size | Allocation type | Variant | No. threads | Execution time (ms) | Speedup |
|---|---|---|---|---|---|
| 10 x 10, k=3 | static | sequential | 1 | 0.002 | 1 |
| 10 x 10, k=3 | static | rows | 4 | 1.593 | 0.001 |
| 10 x 10, k=3 | static | columns | 4 | 0.705 | 0.003 |
| 10 x 10, k=3 | dynamic | sequential | 1 | 0.003 | 1 |
| 10 x 10, k=3 | dynamic | rows | 4 | 1.239 | 0.002 |
| 10 x 10, k=3 | dynamic | columns | 4 | 0.843 | 0.004 |
| 1000 x 1000, k=3 | static | sequential | 1 | 11.1 | 1 |
| 1000 x 1000, k=3 | static | rows | 2 | 6.211 | 1.785 |
| 1000 x 1000, k=3 | static | columns | 2 | 5.892 | 1.882 |
| 1000 x 1000, k=3 | static | rows | 4 | 3.887 | 2.852 |
| 1000 x 1000, k=3 | static | columns | 4 | 4.730 | 2.344 |
| 1000 x 1000, k=3 | static | rows | 8 | 3.399 | 3.262 |
| 1000 x 1000, k=3 | static | columns | 8 | 8.697 | 1.275 |
| 1000 x 1000, k=3 | static | rows | 16 | 3.291 | 3.369 |
| 1000 x 1000, k=3 | static | columns | 16 | 7.334 | 1.512 |
| 1000 x 1000, k=3 | dynamic | sequential | 1 | 21.9 | 1 |
| 1000 x 1000, k=3 | dynamic | rows | 2 | 8.108 | 2.704 |
| 1000 x 1000, k=3 | dynamic | columns | 2 | 8.416 | 2.605 |
| 1000 x 1000, k=3 | dynamic | rows | 4 | 5.110 | 4.290 |
| 1000 x 1000, k=3 | dynamic | columns | 4 | 5.279 | 4.152 |
| 1000 x 1000, k=3 | dynamic | rows | 8 | 4.453 | 4.923 |
| 1000 x 1000, k=3 | dynamic | columns | 8 | 4.763 | 4.602 |
| 1000 x 1000, k=3 | dynamic | rows | 16 | 3.915 | 5.599 |
| 1000 x 1000, k=3 | dynamic | columns | 16 | 4.412 | 4.968 |
| 10 x 10000, k=5 | static | sequential | 1 | 1.830 | 1 |
| 10 x 10000, k=5 | static | rows | 2 | 1.928 | 0.949 |
| 10 x 10000, k=5 | static | columns | 2 | 1.768 | 1.035 |
| 10 x 10000, k=5 | static | rows | 4 | 1.281 | 1.429 |
| 10 x 10000, k=5 | static | columns | 4 | 1.301 | 1.407 |
| 10 x 10000, k=5 | static | rows | 8 | 1.379 | 1.327 |
| 10 x 10000, k=5 | static | columns | 8 | 1.539 | 1.189 |
| 10 x 10000, k=5 | static | rows | 16 | 1.493 | 1.226 |
| 10 x 10000, k=5 | static | columns | 16 | 1.883 | 0.972 |
| 10 x 10000, k=5 | dynamic | sequential | 1 | 3.095 | 1 |
| 10 x 10000, k=5 | dynamic | rows | 2 | 2.731 | 1.133 |
| 10 x 10000, k=5 | dynamic | columns | 2 | 2.614 | 1.184 |
| 10 x 10000, k=5 | dynamic | rows | 4 | 1.983 | 1.561 |
| 10 x 10000, k=5 | dynamic | columns | 4 | 2.065 | 1.499 |
| 10 x 10000, k=5 | dynamic | rows | 8 | 1.773 | 1.746 |
| 10 x 10000, k=5 | dynamic | columns | 8 | 1.609 | 1.924 |
| 10 x 10000, k=5 | dynamic | rows | 16 | 1.708 | 1.812 |
| 10 x 10000, k=5 | dynamic | columns | 16 | 1.806 | 1.714 |
| 10000 x 10, k=5 | static | sequential | 1 | 1.836 | 1 |
| 10000 x 10, k=5 | static | rows | 2 | 2.016 | 0.911 |
| 10000 x 10, k=5 | static | columns | 2 | 1.731 | 1.061 |
| 10000 x 10, k=5 | static | rows | 4 | 1.600 | 1.147 |
| 10000 x 10, k=5 | static | columns | 4 | 1.389 | 1.322 |
| 10000 x 10, k=5 | static | rows | 8 | 1.448 | 1.268 |
| 10000 x 10, k=5 | static | columns | 8 | 1.169 | 1.571 |
| 10000 x 10, k=5 | static | rows | 16 | 1.726 | 1.064 |
| 10000 x 10, k=5 | static | columns | 16 | 1.482 | 1.239 |
| 10000 x 10, k=5 | dynamic | sequential | 1 | 2.991 | 1 |
| 10000 x 10, k=5 | dynamic | rows | 2 | 2.605 | 1.148 |
| 10000 x 10, k=5 | dynamic | columns | 2 | 2.321 | 1.289 |
| 10000 x 10, k=5 | dynamic | rows | 4 | 2.059 | 1.453 |
| 10000 x 10, k=5 | dynamic | columns | 4 | 2.066 | 1.448 |
| 10000 x 10, k=5 | dynamic | rows | 8 | 1.552 | 1.927 |
| 10000 x 10, k=5 | dynamic | columns | 8 | 1.891 | 1.582 |
| 10000 x 10, k=5 | dynamic | rows | 16 | 2.095 | 1.428 |
| 10000 x 10, k=5 | dynamic | columns | 16 | 1.719 | 1.740 |
| 10000 x 10000, k=5 | static | sequential | 1 | 1816.8 | 1 |
| 10000 x 10000, k=5 | static | rows | 2 | 945.7 | 1.921 |
| 10000 x 10000, k=5 | static | columns | 2 | 5214.2 | 0.348 |
| 10000 x 10000, k=5 | static | rows | 4 | 476.0 | 3.817 |
| 10000 x 10000, k=5 | static | columns | 4 | 4403.3 | 0.413 |
| 10000 x 10000, k=5 | static | rows | 8 | 350.0 | 5.191 |
| 10000 x 10000, k=5 | static | columns | 8 | 3067.0 | 0.592 |
| 10000 x 10000, k=5 | static | rows | 16 | 351.9 | 5.162 |
| 10000 x 10000, k=5 | static | columns | 16 | 3063.9 | 0.593 |
| 10000 x 10000, k=5 | dynamic | sequential | 1 | 3123.1 | 1 |
| 10000 x 10000, k=5 | dynamic | rows | 2 | 1554.7 | 2.009 |
| 10000 x 10000, k=5 | dynamic | columns | 2 | 7093.4 | 0.440 |
| 10000 x 10000, k=5 | dynamic | rows | 4 | 823.3 | 3.793 |
| 10000 x 10000, k=5 | dynamic | columns | 4 | 4400.8 | 0.710 |
| 10000 x 10000, k=5 | dynamic | rows | 8 | 585.6 | 5.333 |
| 10000 x 10000, k=5 | dynamic | columns | 8 | 3635.9 | 0.859 |
| 10000 x 10000, k=5 | dynamic | rows | 16 | 631.1 | 4.948 |
| 10000 x 10000, k=5 | dynamic | columns | 16 | 3588.7 | 0.870 |


### 5.3 Best variant for each matrix size

| Matrix size | Best Java | Best C++ |
|---|---|---|
| 10 x 10, k=3 | sequential (0.061 ms) | static, sequential (0.002 ms) |
| 1000 x 1000, k=3 | rows, 4 threads (26.7 ms) | static, rows, 16 threads (3.291 ms) |
| 10 x 10000, k=5 | sequential (19.4 ms) | static, rows, 4 threads (1.281 ms) |
| 10000 x 10, k=5 | sequential (19.5 ms) | static, columns, 8 threads (1.169 ms) |
| 10000 x 10000, k=5 | rows, 16 threads (1597.2 ms) | static, rows, 8 threads (350.0 ms) |

## 6. Results analysis

- **Small matrices** (10 x 10, and the thin 10 x 10000 and 10000 x 10): the work is too small, so the parallel versions are slower than the sequential one or only slightly faster, because starting threads costs more than the computation.
- **Rows against columns:** the horizontal split is better. Matrices are stored row by row, so a thread that walks down columns has many cache misses; on 10000 x 10000 the column split in C++ is even slower than the sequential version.
- **Number of threads:** the time decreases up to 4 to 8 threads and then stays flat, which fits the 6 cores of the machine. The best speedups are about 5.3 in C++ and 4.3 in Java, on 10000 x 10000 with the rows version.
- **Java against C++:** C++ is faster (for example 1817 ms against 6816 ms sequential on 10000 x 10000), probably because of the array bounds checks, the array of arrays and the JIT warm-up in Java.
- **Static against dynamic (C++):** the static version is faster in absolute time (for example 11 ms against 22 ms on 1000 x 1000), probably because the compiler knows the array dimensions. The speedups of the dynamic version look higher because its sequential time is slower.
