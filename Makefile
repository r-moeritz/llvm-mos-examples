# Paths
SRCDIR := src
OBJDIR := build
SRC := $(wildcard $(SRCDIR)/*.c)

# Commands
MKPRG = mos-sim-clang -Os -o $@ -Iinclude
RM := rm -rf
MKDIR := mkdir -p

# Rules
$(OBJDIR)/calc.prg: $(SRCDIR)/calc.c $(SRCDIR)/util.c
	$(MKPRG) $(SRCDIR)/calc.c $(SRCDIR)/util.c

# Targets
.PHONY: all run-calc-sim c64 run-calc-vice clean

all: $(OBJDIR)/calc.prg

run-calc-sim: $(OBJDIR)/calc.prg
	mos-sim $(OBJDIR)/calc.prg

c64: MKPRG = mos-c64-clang -Os -o $@ -Iinclude
c64: $(OBJDIR)/calc.prg

run-calc-vice: c64
	x64sc $(OBJDIR)/calc.prg

$(SRC): | $(OBJDIR)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

clean:
	$(RM) $(OBJDIR)
