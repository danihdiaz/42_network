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

```bash
./codexion 4 1000 200 200 200 2 100 fifo
```

---

## ⛔ Blocking cases handled

This implementation explicitly manages classic problems in concurrent systems:

* **Deadlock and Coffman Conditions Prevention:**
  * **Mutual Exclusion:** Access to each individual dongle is protected by its own mutex (`pthread_mutex_t`).
  * **Hold and Wait:** Coders acquire dongles via a structured priority queue, avoiding indefinite blockings while holding partial resources.
  * **No Preemption:** Dongle release is voluntary upon finishing the work phase.
  * **Circular Wait:** Resource allocation is centralized through a priority queue (Min-Heap) strictly ordered by arrival time (FIFO) or closeness to *burnout* (EDF), guaranteeing a total order of acquisition.
* **Starvation Prevention:**
  * The **EDF** (*Earliest Deadline First*) scheduler dynamically prioritizes coders in the Min-Heap whose *burnout* deadline is closest.
  * The **FIFO** scheduler guarantees that first-come, first-served order is strictly maintained.
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
  * **Coder State Mutex:** Synchronizes reading and writing of the last meal/completion timestamp between the *coder* threads and the *monitor* thread.
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
