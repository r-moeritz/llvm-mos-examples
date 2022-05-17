# Paths
SRCDIR := src
OBJDIR := build
SRC := $(wildcard $(SRCDIR)/examples/*.c ) $(wildcard $(SRCDIR)/examples/*.cc)
UTIL_SIM_OBJ := $(OBJDIR)/util-sim.o
UTIL_C64_OBJ := $(OBJDIR)/util-c64.o
CALC_SIM_OBJ := $(OBJDIR)/calc-sim.o
CALC_C64_OBJ := $(OBJDIR)/calc-c64.o
RASTER_C64_OBJ := $(OBJDIR)/raster-c64.o
CALC_SIM_PRG := $(OBJDIR)/calc-sim.prg
CALC_C64_PRG := $(OBJDIR)/calc-c64.prg
RASTER_C64_PRG := $(OBJDIR)/raster-c64.prg

# Flags
CFLAGS = -c -Os -Iinclude -o $@
LDFLAGS = -Os -o $@

# Commands
CC_SIM = mos-sim-clang
CC_C64 = mos-c64-clang
CXX_SIM = mos-sim-clang++
CXX_C64 = mos-c64-clang++
RM := rm -rf
MKDIR := mkdir -p

# Targets
.PHONY: all calc-sim calc-c64 raster-c64 run-calc-sim run-calc-vice run-raster-vice clean

all: $(CALC_SIM_PRG) $(CALC_C64_PRG) $(RASTER_C64_PRG)

# Calculator
$(CALC_SIM_PRG): $(CALC_SIM_OBJ) $(UTIL_SIM_OBJ)
	$(CXX_SIM) $(LDFLAGS) $(CALC_SIM_OBJ) $(UTIL_SIM_OBJ)

$(CALC_SIM_OBJ): $(SRCDIR)/examples/calc.cc
	$(CXX_SIM) $(CFLAGS) $(SRCDIR)/examples/calc.cc

$(UTIL_SIM_OBJ): $(SRCDIR)/util.c
	$(CC_SIM) $(CFLAGS) $(SRCDIR)/util.c

$(CALC_C64_PRG): $(CALC_C64_OBJ) $(UTIL_C64_OBJ)
	$(CXX_C64) $(LDFLAGS) $(CALC_C64_OBJ) $(UTIL_C64_OBJ)

$(CALC_C64_OBJ): $(SRCDIR)/examples/calc.cc
	$(CXX_C64) $(CFLAGS) $(SRCDIR)/examples/calc.cc

$(UTIL_C64_OBJ): $(SRCDIR)/util.c
	$(CC_C64) $(CFLAGS) $(SRCDIR)/util.c

# Raster
$(RASTER_C64_PRG): $(RASTER_C64_OBJ)
	$(CC_C64) $(LDFLAGS) $(RASTER_C64_OBJ)

$(RASTER_C64_OBJ): $(SRCDIR)/examples/raster-c64.c
	$(CC_C64) $(CFLAGS) $(SRCDIR)/examples/raster-c64.c

calc-sim: $(CALC_SIM_PRG)
calc-c64: $(CALC_C64_PRG)
raster-c64: $(RASTER_C64_PRG)

run-calc-sim: $(CALC_SIM_PRG)
	mos-sim $(CALC_SIM_PRG)

run-calc-vice: $(CALC_C64_PRG)
	x64sc $(CALC_C64_PRG)

run-raster-vice: $(RASTER_C64_PRG)
	x64sc $(RASTER_C64_PRG)

$(SRC): | $(OBJDIR)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

clean:
	$(RM) $(OBJDIR)
