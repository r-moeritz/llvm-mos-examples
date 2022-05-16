# Paths
SRCDIR := src
OBJDIR := build
SRC := $(wildcard $(SRCDIR)/*.c)
CALC_SIM_PRG := $(OBJDIR)/calc-sim.prg
CALC_C64_PRG := $(OBJDIR)/calc-c64.prg
RASTER_C64_PRG := $(OBJDIR)/raster-c64.prg

# Flags
CXXFLAGS = -Wno-deprecated

# Commands
CC_SIM = mos-sim-clang -Os -o $@ -Iinclude
CC_C64 = mos-c64-clang -Os -o $@ -Iinclude
CXX_SIM = mos-sim-clang++ $(CXXFLAGS) -Os -o $@ -Iinclude
CXX_C64 = mos-c64-clang++ $(CXXFLAGS) -Os -o $@ -Iinclude
RM := rm -rf
MKDIR := mkdir -p

# Targets
.PHONY: all calc-sim calc-c64 raster-c64 run-calc-sim run-calc-vice run-raster-vice clean

all: $(CALC_SIM_PRG) $(CALC_C64_PRG) $(RASTER_C64_PRG)

$(CALC_SIM_PRG): $(SRCDIR)/examples/calc.cc $(SRCDIR)/util.c
	$(CXX_SIM) $(SRCDIR)/examples/calc.cc $(SRCDIR)/util.c

$(CALC_C64_PRG): $(SRCDIR)/examples/calc.cc $(SRCDIR)/util.c
	$(CXX_C64) $(SRCDIR)/examples/calc.cc $(SRCDIR)/util.c

$(RASTER_C64_PRG): $(SRCDIR)/raster-c64.c
	$(CC_C64) $(SRCDIR)/raster-c64.c

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
