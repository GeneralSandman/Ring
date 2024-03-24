This directory contains all Redis dependencies, except for the libc that
should be provided by the operating system.

* **linenoise** is a readline replacement. It is developed by the same authors of Redis but is managed as a separated project and updated as needed.

How to upgrade the above dependencies
===


Linenoise
---

Linenoise is rarely upgraded as needed. The upgrade process is trivial since
Redis uses a non modified version of linenoise, so to upgrade just do the
following:

1. Remove the linenoise directory.
2. Substitute it with the new linenoise source tree.
3. Format by clang-format.
4. Compile and try to delete commpile warning.
   - 1. `new` is a keyword in cpp, not used to identifier.
   - 2. The type of return value from `malloc()` `realloc()` is `void*`, need to convert by `(char*)malloc()`.




Clipp
---

https://github.com/muellan/clip