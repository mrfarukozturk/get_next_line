*This project has been created as part of the 42 curriculum by fozturk.*

# Description

This project implements the `get_next_line` function in C. The goal is to read a file line by line without loading the entire file into memory at once.

The function is designed to handle input streams efficiently while preserving the unread remainder between successive calls. This is a classic buffered I/O problem and a common exercise in low-level C programming.

The core idea is to continuously read data from a file descriptor into a fixed-size buffer, append it to the remaining content, and extract exactly one line when a newline character is encountered.

# Instructions

## Compilation

To compile the project:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test
```

## Usage

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

# Algorithm

The implementation uses a buffer-based reading strategy.

1. Read a fixed-size chunk from the file descriptor using `read()`.
2. Append the chunk to the previously stored remainder.
3. Search the accumulated string for the first newline character.
4. If a newline is found, split the string into:
   - the current line to return,
   - the remaining content to keep for the next call.
5. If no newline is found, keep reading until EOF or until a full line is formed.

This approach is efficient because it avoids reading the whole file at once, and it keeps the state between calls using static storage associated with the file descriptor.

This strategy was chosen because it matches the project requirement: read one line at a time while preserving all unread content. It is also simple, memory-safe, and portable to C 98 constraints.

# Resources

## References

- The GNU C Library manual on file descriptors and `read()`.
- POSIX documentation for `open()`, `read()`, and file I/O.
- C tutorials covering dynamic memory allocation, strings, and buffer management.
- Common examples of line-oriented input handling in C.

## AI Usage

AI tools were used for:
- understanding the root requirements of the project,
- checking the logic of buffered reading and line extraction,
- reviewing the memory-management flow for correctness,
- validating the final README structure and wording for clarity.

The AI was not used to replace algorithm design; it was used to support debugging, validation, and documentation clarity.

# Notes

This project is a low-level C exercise focused on file input, static state retention, memory allocation, and clean handling of partial reads.
# get_next_line
