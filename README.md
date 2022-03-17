I created this repository to experiment with creating "real world" programs for
MOS 6502 platforms using
[llvm-mos](https://github.com/llvm-mos/llvm-mos-sdk). Right now it contains the
following:

| Source           | Description                            |
|------------------|----------------------------------------|
| src/calc.c       | A simple interactive calculator        |
| src/raster-c64.c | A raster IRQ demo for the Commodore 64 |

## Building

### Compile for all targets

    make

### Compile raster IRQ example for C64

    make raster-c64

### Compile raster IRQ example for C64 and launch in VICE emulator

    make run-raster-vice

### Compile calculator example for 6502 simulator

    make calc-sim
    
### Compile calculator example for C64

    make calc-c64

### Compile calculator for 6502 and launch simulator

    make run-calc-sim

### Compile calculator for C64 and launch VICE emulator

    make run-calc-vice

## License

[GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html)
