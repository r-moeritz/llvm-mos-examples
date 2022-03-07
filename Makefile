# Paths
SRCDIR := src
OBJDIR := build
SRC := $(wildcard $(SRCDIR)/*.c)
CALC_SIM_PRG := $(OBJDIR)/calc-sim.prg
CALC_C64_PRG := $(OBJDIR)/calc-c64.prg

# Commands
MKPRG_SIM = mos-sim-clang -Os -o $@ -Iinclude
MKPRG_C64 = mos-c64-clang -Os -o $@ -Iinclude
RM := rm -rf
MKDIR := mkdir -p

# Targets
.PHONY: all calc-sim calc-c64 run-calc-sim run-calc-vice clean

all: $(CALC_SIM_PRG) $(CALC_C64_PRG)

$(CALC_SIM_PRG): $(SRCDIR)/calc.c $(SRCDIR)/util.c
	$(MKPRG_SIM) $(SRCDIR)/calc.c $(SRCDIR)/util.c

$(CALC_C64_PRG): $(SRCDIR)/calc.c $(SRCDIR)/util.c
	$(MKPRG_C64) $(SRCDIR)/calc.c $(SRCDIR)/util.c

calc-sim: $(CALC_SIM_PRG)
calc-c64: $(CALC_C64_PRG)

run-calc-sim: $(CALC_SIM_PRG)
	mos-sim $(CALC_SIM_PRG)

run-calc-vice: $(CALC_C64_PRG)
	x64sc $(CALC_C64_PRG)

$(SRC): | $(OBJDIR)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

clean:
	$(RM) $(OBJDIR)
