# Thread Race

[![CI](https://github.com/BernardoFerrazG/Corrida-threads/actions/workflows/ci.yml/badge.svg)](https://github.com/BernardoFerrazG/Corrida-threads/actions/workflows/ci.yml)

A small C program that shows the core POSIX threads synchronisation primitives through a race. **N threads** wait at the start line, start counting together, and the first one to reach the target is declared the winner. Code and output are in Portuguese; this README is in English.

```
$ ./corrida 3 2
Thread 2: 0
Thread 2: 1
Thread 2: 2
>>>>> Thread 2 venceu! <<<<<
Thread 1: 0
...
Thread vencedora: 2
```

## Concurrency concepts

| Primitive | Role in the race |
| --- | --- |
| `pthread_create` / `pthread_join` | Start one thread per runner and wait for all of them to finish |
| `pthread_barrier_t` | **Start line**: no thread starts counting until every thread has been created, so the race is fair |
| `pthread_mutex_t` | Protects the critical section that records the winner, so exactly one thread can claim the win even when several finish at the same time |

The winner is decided by the OS scheduler, so it changes from run to run. That non-determinism is the point of the exercise.

## Build and run

Requires a C11 compiler and POSIX threads (Linux or macOS).

```bash
cd src
make                 # build ./corrida
./corrida 8          # 8 threads, each counting to 99
./corrida 8 1000     # custom target
make run NTHREADS=4
make clean
```

Invalid arguments, such as a missing or non-numeric thread count, print usage instructions instead of crashing.

## Tests

```bash
make -C src test
```

[`src/test.sh`](src/test.sh) runs the race with 1, 4, 16 and 64 threads and checks the invariants on every run:

- there is exactly one winner;
- every thread counts all the way to the target;
- the announced winner is a valid thread id;
- invalid input is rejected.

CI also builds with `-Werror` and runs the suite under **ThreadSanitizer** to detect data races.

## Changes from the original version

- Arguments are validated. Before, running the program without arguments crashed with a segmentation fault (`argv[1]` was read unchecked).
- The thread function now returns a value; falling off the end of a non-`void` function is undefined behaviour.
- `pthread_create` failures are reported, and thread arrays are heap-allocated, so large thread counts no longer risk overflowing the stack.
- Compiled binaries were removed from the repository, and a `.gitignore` was added.
