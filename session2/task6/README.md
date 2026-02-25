# Task 6: Dynamic Analysis of C Programs

## Address Sanitizer (ASan)

1. This directory contains several small demo programs:

   - `noleak.c`
   - `leak.c`
   - `use_after.c`
   - `heap_over.c`
   - `stack_over.c`

   For each of these programs, use the provided makefile to compile the
   program, then run it. For example, to compile `leak.c`, enter

       make leak

   You should find that all of them compile without warnings.

   You should also find that first three programs run without any visible
   run-time error. You may see run-time errors from `stack_over`, `heap_over`
   or both, depending on where you are doing this task.

2. Edit `Makefile` and remove the `#` from the definition of the `CFLAGS`
   variable, so that it looks like this:

       CFLAGS = -g -fsanitize=address -fno-omit-frame-pointer

3. Remove all the executables and then recompile the `noleak` and `leak`
   programs, using this sequence of commands:

       make clean
       make noleak
       make leak

   Both should compile without issue.

   If you try running `noleak`, its behaviour should be unchanged. However,
   if you now try running `leak`, ASan should abort the program and display
   detailed diagnostic information in the terminal.

   Notice how this diagnostic information identifies the problem clearly
   as a memory leak. Notice also how it displays the amount of leaked memory
   (100 bytes).

4. Now compile and run `use_after`. This time, ASan should report the problem
   as `heap-use-after-free` and identify the address stored in the pointer
   that the program was trying to use.

5. Compile and run `heap_over`. ASan will abort the program. Study the first
   few lines of diagnostics that it has produced. You should see from this
   that it has detected an attempt to write 4 bytes beyond the bounds of
   allocated heap memory.

   If you scroll down through the diagnostics, you should come to a section
   heading "Shadow bytes around the buggy address". Beneath this is a
   simplified map of memory usage around the location of the issue. Each of
   the 'shadow bytes' displayed in the map represents 8 bytes of actual memory
   used by the program.

   Part of the memory map will look like this:

       fa fa 00 00 00 00 00 [fa] fa fa

   The shadow bytes labelled `fa` belong to the 'red zone' that is monitored
   by ASan. The sequence of 5 shadow bytes labelled `00` correspond to the
   40 bytes allocated to the array `data`. The shadow byte immediately after
   this is enclosed in square brackets to indicate that the problematic
   access to memory happened here.

6. Compile and run `stack_over`. ASan will abort the program and display
   diagnostics similar to those for `heap_over`, except that this time, the
   issue is an attempt to write 4 bytes beyond the bounds of an array
   allocated on the stack.

   If you scroll down to look at the memory map, you will see a sequence
   of shadow bytes like this:

       f1 f1 f1 00 00 00 00 00 [f3] f3 f3

   Here, `f1` and `f3` are red zones occurring just before and after the
   allocated memory, which is once again shown as 5 shadow bytes labelled as
   `00`. Once again, the square brackets identify the location of the
   problematic access to memory.

7. As a final example, consider the `testlogin` program from Task 3.
   Compile this with ASan using

       make testlogin

   Try running with these inputs:

       penguin
       xxxxxxx
       xxxxxxxxxx

   The first and second of these should give you "Login succeeded" and
   "Login failed" messages, as before. The third should trigger ASan and
   display diagnostic information in the terminal.

## Valgrind
