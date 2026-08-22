*This project was created as part of the 42 curriculum by dhontani.*

# CODEXION

> Master the race for resources before the deadline masters you.

---

## 📝 Description

**Codexion** is a C multi-threaded concurrency programming project within the 42 curriculum. Its goal is to simulate a dynamic environment where multiple programmers (*coders*) compete for a limited number of hardware devices (*dongles*) to advance through their workflow phases: **Compiling**, **Debugging**, and **Refactoring**.

The main objective of the project is to master thread synchronization, prevent classic concurrency issues (such as *deadlocks* or *data races*), implement a dynamic priority ordering algorithm using an efficient data structure (**Min-Heap**), and handle precise failure detection (*burnout*) within a strict time window ($\le 10	ext{ ms}$).

---

## 🛠️ Instructions

### Prerequisites

* C compiler (`cc`, `gcc`, or `clang`)
* `make` build tool
* POSIX Threads library (`pthread`)

### Compilation

The project includes a `Makefile` with the standard rules required by 42:

```bash
make        # Compiles the 'codexion' executable
make clean  # Removes object files (.o)
make fclean # Removes object files and the 'codexion' executable
make re     # Cleans and recompiles everything from scratch
```

### Execution

The program accepts the following command-line arguments:

```bash
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles required> <dongle_cooldown> <scheduler>
```

#### Parameters:
* `number_of_coders`: Total number of coder threads.
* `time_to_burnout`: Maximum time in milliseconds a coder can go without completing a cycle before suffering *burnout*.
* `time_to_compile`: Time in ms spent in the compilation phase.
* `time_to_debug`: Time in ms spent in the debugging phase.
* `time_to_refactor`: Time in ms spent in the refactoring phase.
* `number of compiles required`: Total number of compiles per coder needed to end the simulation.
* `dongle_cooldown`: Cooldown period in ms a dongle must undergo before being reused.
* `scheduler`: Scheduling algorithm (`fifo` or `edf`).

#### Example Usage:

### 1. Standard case — clean completion

Coders alternate dongle usage comfortably and finish their required compilations without anyone starving.

```bash
./codexion 4 700 100 100 100 2 50 fifo
```

### 2. Forced burnout

`time_to_burnout` is shorter than a full compile-debug-refactor cycle, so any coder left waiting too long for a shared dongle starves before reaching their next compilation.

```bash
./codexion 4 150 100 100 100 3 50 fifo
```

### 3. Boundary condition

With 3 coders sharing dongles in a circle, only one can compile at a time, forcing strict sequential turns. This sets an exact mathematical survival threshold: `750ms` per full rotation + `1ms` margin = `751ms`. Because that 1ms margin is on the same order as normal thread-scheduling jitter, occasional burnouts can occur at exactly 751ms depending on OS timing. `752ms` gives a small safety margin and survives reliably.

```bash
./codexion 3 752 50 50 50 4 200 fifo
```

### 4. High-concurrency stress test

100 threads competing for 100 shared dongles under heavy lock contention, without deadlocks or data races, and with `time_to_burnout` generous enough for the compilation "wave" to reach every coder.

```bash
./codexion 100 2000 20 20 20 5 0 fifo
```
---

## ⛔ Blocking cases handled

This implementation explicitly manages classic problems in concurrent systems:

* **Deadlock and Coffman Conditions Prevention:**
  * **Mutual Exclusion:** Access to each individual dongle is protected by its own mutex (`pthread_mutex_t`).
  * **Hold and Wait:** Coders acquire dongles via a structured priority queue, avoiding indefinite blockings while holding partial resources.
  * **No Preemption:** Dongle release is voluntary upon finishing the work phase.
  * **Circular Wait:** Each coder always acquires their two dongles in a fixed, consistent order — comparing pointer addresses (`person->left < person->right`) to decide which one to request first, regardless of the coder's position in the circle. This guarantees that no two coders can ever be waiting on each other in a cycle, since every coder follows the same global ordering rule.
* **Starvation Prevention:**
  * Within each dongle's individual waiting queue, a **Min-Heap** orders competing coders either by arrival time (**FIFO**) or by closeness to *burnout* (**EDF**), guaranteeing fair and deterministic access once the dongle becomes available.
* **Cooldown Management:**
  * Each dongle maintains an availability timestamp. No coder can acquire a dongle that is currently in its cooldown period, coordinated via condition variables (`pthread_cond_t`).
* **Accurate Burnout Detection:**
  * A dedicated monitor thread continuously checks the coders' status. The check runs with strict precision to notify and stop the simulation within a time margin of no more than $\le 10	ext{ ms}$ from when the *burnout* occurs.
* **Log Serialization:**
  * Console output calls are fully protected by a dedicated logging mutex (`log_lock`). This prevents interleaved or messy output across threads and guarantees chronologically sorted logs.

---

## 🔄 Thread synchronization mechanisms

The project utilizes POSIX primitives to guarantee a thread-safe environment:

* **`pthread_mutex_t`:**
  * **Logging Mutex (`log_lock`):** Ensures that printing to stdout is atomic and threads do not interleave output lines.
  * **Dongle Mutex (`dongle.lock`):** Protects the individual structures of each dongle and access to its waiting queue / Min-Heap.
  * **Coder State Mutex:** Synchronizes reading and writing of the last compilation timestamp (`last_compile`) between the *coder* threads and the *monitor* thread.
* **`pthread_cond_t`:**
  * **Dongle Condition Variable (`dongle.av_cond`):** Notifies waiting threads when a dongle has finished its cooldown period and becomes available again.
* **Thread-Safe Coder-Monitor Communication:**
  * The monitor thread atomically reads the state and timestamps of each coder using short-scoped mutex locks to avoid stalling work phases. If it detects a coder exceeding `time_to_burnout`, the monitor updates the global simulation state and halts execution before logging the burnout message.
* **Data Race Prevention:**
  * All access to shared variables (including static color lookup tables or pointer arrays) is performed under mutex protection or using clean immutable data structures. Verified 100% error-free using **Helgrind**.

---

## 📚 Resources

### Documentation and References
* **POSIX Threads Programming:** IEEE standard specification and tutorials on `pthread_mutex_t`, `pthread_cond_t`, and thread management.
* **Operating System Concepts (Silberschatz, Galvin, Gagne):** Chapters on process synchronization, classical concurrency problems, and resource scheduling.
* **Data Structures - Binary Min-Heap:** Theoretical documentation on priority queues and heap implementation using dynamic arrays.
* **Beej's Guide to C Programming:** Theoretical documentation on pretty much everything regarding C programming language.

### AI Usage Declaration
In accordance with project regulations, the use of AI tools during development is detailed below:
* **Refactoring and Concurrency Debugging:** Assistance in diagnosing data race errors detected by Helgrind in helper functions (`log_utils.c`) and identifying index errors when destroying mutexes in cleanup loops (`clean_utils.c`).
* **Makefile Design and Documentation:** Assistance with technical explanations of compilation phases (`.o`, `-c`, pattern substitution) and in writing this `README.md` file following the structure required by the evaluation sheet.
