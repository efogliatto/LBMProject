clear all;
clc;

# Reduced temperature
Tr = 0.7;

# Reduced temperature initial conditions (Tr cl cg)
initialTr = [0.99 1.1 0.8 ;
	     0.95 1.3 0.5 ;
	     0.90 1.5 0.3 ;
	     0.70 1.9 0.1 ;
	     0.60 2.2 0.05 ;
	     0.50 2.4 0.025 ;
	     0.45 2.5 0.0125 ;
	     0.40 2.7 1.5625e-03];

# Average reduced concentration
c_bar = 1;

# # Plot and write flags
# plot_profile = false;
# write_profile = true;
# write_vfrac = false;

# # Concentration information. Tr, cl, cg, phi_f
# Result = [];




# Equilibrium densities. Use linear interpolation to determine initial densities
init_cl = interp1( initialTr(:,1), initialTr(:,2), Tr );
init_cg = interp1( initialTr(:,1), initialTr(:,3), Tr );
[c,fval,info] = fsolve(@(x) redConFunction(x,Tr), [init_cl;init_cg], optimset("TolX", 1e-10, "TolFun", 1e-10));


printf("\nAdjusting sigma for Tr = %.3f\n\n",Tr);
  


 


