I created this repository to experiment with creating "real world" programs for
MOS 6502 platforms using
[llvm-mos](https://github.com/llvm-mos/llvm-mos-sdk). Right now it contains the
following:

| Source     | Description                     |
|------------|---------------------------------|
| src/calc.c | A simple interactive calculator |

## Building

### Compile for llvm-mos 6502 simulator

    make

### Compile for and start llvm-mos 6502 simulator

    make run-calc-sim

### Compile for C64

    make c64

### Compile for C64 and launch VICE emulator

    make run-calc-vice

## License

[GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html)
