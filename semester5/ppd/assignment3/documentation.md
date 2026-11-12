# Lab 3 - Sum of two large numbers with MPI

## 1. Requirements analysis

Compute the sum of two large numbers read from `Number1.txt` and `Number2.txt` (N, then the digits) and write it to `Number3.txt`. A number is an array of digits with the least significant digit at position 0. Required: a sequential version and three MPI versions with p processes: standard communication (variant 1), Scatter / Gather (variant 2) and non-blocking communication (variant 3). Reading the numbers is included in the execution time.

## 2. Design

The digits are stored in the files least significant first, so process 0 can read both files chunk by chunk from the start; the shorter number is padded with 0s. The carry goes from process i to process i + 1.

**Variant 1.** Process 0 reads N / (p - 1) digits at a time and sends them to process 1, 2, ... with `MPI_Send`. A worker receives its digits, then the carry from id - 1, adds and sends the carry to id + 1 and its segment to process 0, which writes each segment as soon as it arrives. There is no cycle of blocking calls, so it also works with `MPI_Ssend`.

**Variant 2.** Process 0 reads both numbers and pads them to a multiple of p. The chunk size is sent with `MPI_Bcast`, the digits with `MPI_Scatter`; every process (0 included) adds with the carry from the previous one, and the result is collected with `MPI_Gather`. The last carry is sent to process 0 after the gather, to avoid a deadlock with it.

**Variant 3.** Same distribution as variant 1 with `MPI_Isend` / `MPI_Irecv`. Process 0 posts the receives for all segments first, so they are collected asynchronously. A worker posts the receive for the carry before receiving its digits, since the two can arrive in any order.

**Structure:**

| Component | File | Role |
|---|---|---|
| Sequential | `sequential.cpp` | sequential sum, writes `ExpectedResult.txt` |
| Variant 1 | `variant1.cpp` | `MPI_Send` / `MPI_Recv` |
| Variant 2 | `variant2.cpp` | `MPI_Bcast`, `MPI_Scatter`, `MPI_Gather` |
| Variant 3 | `variant3.cpp` | `MPI_Isend` / `MPI_Irecv` |
| InputOutput | `number_io.h` | read N, read k digits, write digits, check result |
| Generate | `generate.cpp` | random n-digit number |

## 3. Implementation details

- C++11 with MS-MPI; digits are `int` arrays sent as `MPI_INT`.
- `readDigits(file, buffer, k)` reads the next k digits, so it serves both the chunked reading (variants 1, 3) and the full reading (sequential, variant 2).
- After the timer is stopped, `checkResult` compares the result array of process 0 with `ExpectedResult.txt` (produced by the sequential version).
- `run.ps1` runs a program 10 times and prints the mean.

## 4. Test cases

16 + 16 digits (`9999 4444 4444 9999` + `9999 5555 5555 9999`), 10000 + 10000 and 100 + 100000 for variants 1 and 3 (p = 5, 9, 17), and 16 + 16, 1000 + 1000 and 100 + 100000 for variant 2 (p = 4, 8, 16), plus the sequential version for each size; 10 runs each, all results correct, also with `MPI_Ssend` / `MPI_Issend`. Environment: AMD Ryzen 5 4500U (6 cores), Windows 11, MS-MPI, C++11 with MinGW g++ `-O3`.

## 5. Results

Mean of 10 runs, time in ms (reading included). Speedup = Tseq / Tpar.

### 5.1 Variant 1

| No. digits | Variant | No. processes | Execution time (ms) | Speedup |
|---|---|---|---|---|
| 16 + 16 | sequential | 1 | 0.293 | 1 |
| 16 + 16 | standard | 5 | 2.669 | 0.110 |
| 10000 + 10000 | sequential | 1 | 0.793 | 1 |
| 10000 + 10000 | standard | 5 | 4.468 | 0.177 |
| 10000 + 10000 | standard | 9 | 7.319 | 0.108 |
| 10000 + 10000 | standard | 17 | 11.87 | 0.067 |
| 100 + 100000 | sequential | 1 | 2.937 | 1 |
| 100 + 100000 | standard | 5 | 8.907 | 0.330 |
| 100 + 100000 | standard | 9 | 11.26 | 0.261 |
| 100 + 100000 | standard | 17 | 20.63 | 0.142 |

### 5.2 Variant 2

| No. digits | Variant | No. processes | Execution time (ms) | Speedup |
|---|---|---|---|---|
| 16 + 16 | sequential | 1 | 0.293 | 1 |
| 16 + 16 | scatter / gather | 4 | 2.878 | 0.102 |
| 1000 + 1000 | sequential | 1 | 0.331 | 1 |
| 1000 + 1000 | scatter / gather | 4 | 3.090 | 0.107 |
| 1000 + 1000 | scatter / gather | 8 | 4.469 | 0.074 |
| 1000 + 1000 | scatter / gather | 16 | 10.70 | 0.031 |
| 100 + 100000 | sequential | 1 | 2.937 | 1 |
| 100 + 100000 | scatter / gather | 4 | 8.984 | 0.327 |
| 100 + 100000 | scatter / gather | 8 | 10.86 | 0.271 |
| 100 + 100000 | scatter / gather | 16 | 20.42 | 0.144 |

### 5.3 Variant 3

| No. digits | Variant | No. processes | Execution time (ms) | Speedup |
|---|---|---|---|---|
| 16 + 16 | sequential | 1 | 0.293 | 1 |
| 16 + 16 | non-blocking | 5 | 2.662 | 0.110 |
| 10000 + 10000 | sequential | 1 | 0.793 | 1 |
| 10000 + 10000 | non-blocking | 5 | 4.529 | 0.175 |
| 10000 + 10000 | non-blocking | 9 | 8.641 | 0.092 |
| 10000 + 10000 | non-blocking | 17 | 16.64 | 0.048 |
| 100 + 100000 | sequential | 1 | 2.937 | 1 |
| 100 + 100000 | non-blocking | 5 | 7.991 | 0.368 |
| 100 + 100000 | non-blocking | 9 | 10.46 | 0.281 |
| 100 + 100000 | non-blocking | 17 | 19.53 | 0.150 |

### 5.4 Best variant for each size

| No. digits | Best variant | Best parallel variant |
|---|---|---|
| 16 + 16 | sequential (0.293 ms) | non-blocking, 5 processes (2.662 ms) |
| 1000 + 1000 | sequential (0.331 ms) | scatter / gather, 4 processes (3.090 ms) |
| 10000 + 10000 | sequential (0.793 ms) | standard, 5 processes (4.468 ms) |
| 100 + 100000 | sequential (2.937 ms) | non-blocking, 5 processes (7.991 ms) |

## 6. Results analysis

- **Sequential is the fastest:** adding digits is very cheap and most of the time is reading the files, which only process 0 does in every variant. The messages and the carry chain cost more than the parallel addition saves, so the speedup stays below 1.
- **Number of processes:** the time grows with p, since each process adds messages and a link in the carry chain; with 9 - 17 processes the 6 cores are also oversubscribed.
- **Larger inputs** get closer to the sequential time (best speedup 0.37 on 100 + 100000), because the fixed MPI overhead weighs less.
- **Variants:** the times are close. Non-blocking is a bit faster on 100 + 100000, where process 0 reads the next chunk while the previous one is still being sent, but slower with many processes on 10000 + 10000. Scatter / gather is close to the standard variant, even though process 0 reads everything first.
