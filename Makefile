# Makefile for DPI-C with Eigen Demo

# Variables
gpp       := g++
vcs       := vcs
CFLAGS    := -std=c++11 -O2 -fPIC -I/usr/include/eigen3
LDFLAGS   := -shared
SVFLAGS   := -sverilog
SIM       := simv
TARGET_LIB:= libgauss.so

# Sources
CPP_SRCS  := gaussian_elimination.cpp gaussian_dpi.cpp
SV_SRCS   := tb_gaussian_elim.sv

.PHONY: all clean run

all: $(TARGET_LIB) $(SIM)

# Build shared library
$(TARGET_LIB): $(CPP_SRCS)
	$(gpp) $(CFLAGS) $(CPP_SRCS) $(LDFLAGS) -o $(TARGET_LIB)

# Compile SystemVerilog testbench and link library
$(SIM): $(SV_SRCS) $(TARGET_LIB)
	$(vcs) $(SVFLAGS) -CFLAGS "-I/usr/include/eigen3" -LDFLAGS "-L. -lgauss -Wl,-rpath,." $(SV_SRCS) -o $(SIM)

# Run simulation
run: all
	./$(SIM) +libext+.so | tee sim.log

clean:
	rm -f $(TARGET_LIB) $(SIM) $(SIM).daidir ucli.key vc_hdrs.h sim.log dpi_log.txt