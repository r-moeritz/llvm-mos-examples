## General

- `printf` is *huge* (around 40 blocks or 10 KiB!) and should be avoided like
  the plague -- use `puts` instead.
- Memory is initialized with zeroes. This can lead to bugs when using string
  manipulation functions like `strcpy`!

## C64

- A *lot* of inline Assembly is still required when writing an interrupt
  handler. Given the time-contraints faced when handling interrupts, and the
  amount of _your_ time and effort needed to ensure your C code is transformed
  into correct, efficient ML, it makes more sense IMO to just code your
  interrupt handlers in Assembly.
