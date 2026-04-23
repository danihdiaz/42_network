*Este proyecto ha sido creado como parte del currículo de 42 por dhontani.*

<div align="center">

```
 ██████╗ ███╗   ██╗██╗
██╔════╝ ████╗  ██║██║
██║  ███╗██╔██╗ ██║██║
██║   ██║██║╚██╗██║██║
╚██████╔╝██║ ╚████║███████╗
 ╚═════╝ ╚═╝  ╚═══╝╚══════╝
```

**get_next_line** — Read a file, one line at a time. No more, no less.

![42 Badge](https://img.shields.io/badge/42-Project-black?style=for-the-badge&logo=42&logoColor=white)
![Language](https://img.shields.io/badge/C-Language-blue?style=for-the-badge&logo=c&logoColor=white)
![Norm](https://img.shields.io/badge/Norminette-passing-brightgreen?style=for-the-badge)

</div>

---

## 📖 Description

`get_next_line` is a function that reads a file descriptor line by line, returning each line on successive calls — including the trailing `\n` when present.

At its core, this project is about two things: **static variables** and **buffer management**. You learn how to maintain state between function calls without global variables, how to handle reading from multiple file descriptors simultaneously, and how dynamic memory interacts with persistent data.

It sounds simple. It isn't. Edge cases will hunt you down.

### What it does

- Returns the next line from a file descriptor on each call
- Works with files, standard input, and anything else behind a `fd`
- Handles multiple file descriptors at the same time (bonus)
- Returns `NULL` when there's nothing left to read or on error

### Function signature

```c
char *get_next_line(int fd);
```

---

## ⚙️ Algorithm — The Static Buffer Approach

The central challenge is: **reads don't align with lines**. A single `read()` call might bring in half a line, three lines, or a line and a half. We need to stitch that together correctly.

### Core idea

We use a **static variable** (`stash`) to persist unprocessed data between calls. Each call to `get_next_line` works like this:

```
 ┌──────────────┐
 │  stash has   │──► search for '\n' in stash
 │  leftover?   │
 └──────┬───────┘
        │ NO                        YES
        ▼                           ▼
   read() into             extract line up to '\n'
   buffer, append          update stash with remainder
   to stash                return line
        │
        ▼
   repeat until '\n'
   found or EOF
```

### Why this algorithm?

Alternative approaches exist — reading char by char, mapping the whole file — but the **static stash + chunked read** approach is the right tradeoff for this project:

| Approach | Pros | Cons |
|---|---|---|
| Read char by char | Simple logic | Extremely slow, one syscall per character |
| Read entire file | Fast | Breaks with stdin, huge memory use on big files |
| **Static stash + BUFFER_SIZE reads** ✅ | Efficient, handles all fd types | Slightly more complex logic |

The `BUFFER_SIZE` is defined at compile time, so performance can be tuned without changing code. The static variable (or a static array indexed by `fd` for the bonus) is what makes the whole thing work — it's the memory between calls.

### Bonus: multiple file descriptors

The bonus replaces the single static `char *stash` with a `char *stash[OPEN_MAX]` (or a fixed-size array), indexed by `fd`. Each descriptor gets its own independent reading state. Simple extension, elegant result.

---

## 🛠️ Instructions

### Compilation

The project compiles as part of your own program. It is **not** a standalone binary.

```bash
# Basic usage — include gnl in your project
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

You can set `BUFFER_SIZE` at compile time to any positive integer:

```bash
cc ... -D BUFFER_SIZE=1      # Stress test: one byte at a time
cc ... -D BUFFER_SIZE=9999   # Large buffer
```

### Files

```
get_next_line/
├── get_next_line.c          # Core function
├── get_next_line.h          # Header with prototype and BUFFER_SIZE guard
├── get_next_line_utils.c    # Helper functions (ft_strlen, ft_strjoin, etc.)
├── bonus/
│   ├── get_next_line_bonus.c
│   ├── get_next_line_bonus.h
│   └── get_next_line_utils_bonus.c
└── README.md
```

### Usage example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Testing

```bash
# Quick smoke test
echo -e "line one\nline two\nline three" > test.txt
cc -Wall -Wextra -Werror -D BUFFER_SIZE=5 get_next_line.c get_next_line_utils.c main.c -o test
./test
```

---

## 📚 Resources

### Documentation & References

- [Linux `read()` man page](https://man7.org/linux/man-pages/man2/read.2.html) — Understanding the syscall that powers everything here
- [C static variables — cppreference](https://en.cppreference.com/w/c/language/storage_duration) — Lifetime and linkage of static storage
- [42 Norm](https://github.com/42School/norminette) — Code style rules enforced by Norminette
- [GNU C Library — File I/O](https://www.gnu.org/software/libc/manual/html_node/I_002fO-on-Streams.html) — Deeper reference on buffered vs unbuffered I/O

### Recommended testers

- [gnlTester by Tripouille](https://github.com/Tripouille/gnlTester)
- [42TESTERS-GNL by Mazoise](https://github.com/Mazoise/42TESTERS-GNL)

### AI usage

Claude (Anthropic) was used during this project in the following ways:

- **Debugging logic**: Discussing edge cases around `BUFFER_SIZE = 1`, empty files, and files without a trailing newline
- **Explaining concepts**: Clarifying how static variables persist across function calls and their interaction with the stack/heap
- **README drafting**: This very document was written with Claude's assistance

No code was generated directly by AI. All implementations were written and understood by the author.

---

<div align="center">
  <sub>Made with ☕ and existential dread at 42</sub>
</div>
