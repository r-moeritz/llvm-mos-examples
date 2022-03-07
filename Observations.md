- `printf` is *huge* (around 40 blocks or 10 KiB!) and should be avoided like
  the plague -- use `puts` instead.
- Memory is initialized with zeroes. This can lead to bugs when using string
  manipulation functions like `strcpy`!
