clear all;
clc;

# Integration parameters
de = 0.001;
Ef = 1;

# Reduced temperature
Tr = 0.99;

# Equilibrium densities
[c,fval,info] = fsolve(@(x) redConFunction(x,Tr), [1.1;0.8], optimset("TolX", 1e-10, "TolFun", 1e-10));


# Compute profiles only if fsolve converged
if(info == 1)

  # Print information on screen
  printf("\n");
  printf("Reduced temperature: %f\n", Tr);
  printf("Liquid phase reduced concentration: %f\n", c(1));
  printf("Vapor phase reduced concentration: %f\n", c(2));
  printf("\n");
  
  # Compute vapor phase
  [Er_g,Cg] = vaporPhase(c(2),Tr,de,Ef/de);

  # Compute liquid phase
  [Er_f,Cf] = liquidPhase(c(1),Tr,de,Ef/de);

  # Plot density profiles
  plot(Er_g,Cg,";vapor;","linewidth", 5, Er_f,Cf,";liquid;","linewidth", 5);
  set(gca,"fontsize", 18);
  xlim([-0.6 0.6]);

  h = legend ({"vapor","liquid"});
  set (h, "fontsize", 18) 


else

  printf("\n");
  printf("  [ERROR]  Unable to compute concentrations for Tr = %f\n",Tr);
  printf("\n");
  
endif