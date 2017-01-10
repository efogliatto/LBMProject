clear all;
clc;

# Integration parameters
de = 0.001;
Ef = 1;

# Equilibrium densities
[c,fval,info] = fsolve(@redConFunction, [1.2;0.75], optimset("TolX", 1e-10, "TolFun", 1e-10))












# # Reduced temperature
# Tr = 0.99;

# # Equilibrium densities
# [cg,cl] = redConc(Tr)

# # Compute vapor phase
# [Er_g,Cg] = vaporPhase(cg,Tr,de,Ef/de);

# # Compute liquid phase
# [Er_f,Cf] = liquidPhase(cl,Tr,de,Ef/de);

# # Plot density profiles
# plot(Er_g,Cg,";vapor;",Er_f,Cf,";liquid;");