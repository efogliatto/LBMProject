clear all;
clc;

# Reduced temperature
Tr = 0.99;

# Equilibrium densities
[cg,cl] = redConc(Tr);

# Compute vapor phase
C = vaporPhase();