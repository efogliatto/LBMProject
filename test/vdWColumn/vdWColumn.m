clear all;
clc;

# Integration parameters
de = 1e-08;
Ef = 1e-05;

# Reduced temperature
Tr_min = 0.5;
Tr_max = 0.5;

# Reduced temperature initial conditions (Tr cl cg)
initialTr = [0.99 1.1 0.8 ;
	     0.95 1.3 0.5 ;
	     0.90 1.5 0.3 ;
	     0.70 1.9 0.1 ;
	     0.60 2.1 0.05 ;
	     0.50 2.4 0.025 ;
	     0.45 2.5 0.0125 ;
	     0.40 2.7 1.5625e-03];

# Reduced gravitational energy
Er_max = 3.3e-06;

# Average reduced concentration
c_bar = 0;

# Plot and write flags
plot_profile = false;
write_profile = false;




# Move over reduced temperatures

for Tr = Tr_min : 0.1 : Tr_max 

  

  # Equilibrium densities. Use linear interpolation to determine initial densities
  init_cl = interp1( initialTr(:,1), initialTr(:,2), Tr );
  init_cg = interp1( initialTr(:,1), initialTr(:,3), Tr );
  [c,fval,info] = fsolve(@(x) redConFunction(x,Tr), [init_cl;init_cg], optimset("TolX", 1e-10, "TolFun", 1e-10));




  # Compute profiles only if fsolve is converged
  if(info == 1)

    # Print information on screen
    printf("\n");
    printf("Reduced temperature: %f\n", Tr);
    printf("Liquid phase reduced concentration: %f\n", c(1));
    printf("Vapor phase reduced concentration: %f\n", c(2));
    printf("\n");

  
    # Compute vapor phase
    [Er_g,Cg,IntCg] = vaporPhase(c(2),Tr,de,floor(Ef/de));

    # Compute liquid phase
    [Er_f,Cf,IntCf] = liquidPhase(c(1),Tr,de,floor(Ef/de));



  
    # Volume fraction estimation

    if(  (Er_max * c_bar ) > 0  )
      
      # Maximum number of steps
      ner = floor( Er_max/de );
    
      # Mass conservation
      Mass = zeros(ner,1);

      Er_0 = 0;

    
      # Move over all indices
      for i = 1 : ner
      
	Mass(i) = IntCg(ner - i + 1)  +  IntCf(i)  -  c_bar * Er_max;

	if(  (i != 1)  &&  (Mass(i)*Mass(i-1) < 0)  )

	  Er_0 = zerocrossing([i-1;i],[Mass(i-1);Mass(i)]) * de;

	endif

      endfor


      printf("Liquid phase volume fraction: %f\n", Er_0 / Er_max);
      printf("Vapor phase volume fraction: %f\n", 1.0 - Er_0 / Er_max);
      printf("\n");
    
    
    endif


  
  

    # Save profiles
  
    if(write_profile == true)
  
      fname = sprintf("Tr_%.3f.dat",Tr);
      file = fopen(fname,"w");
      for i = 1 : size(Er_f,1)
	fprintf(file,"%f %f %f %f\n",Er_f(i),Cf(i),Er_g(i),Cg(i));
      endfor
      fclose(file);

    endif


  
    # Plot density profiles
  
    if(plot_profile == true)
  
      plot(Er_g,Cg,";vapor;","linewidth", 5, Er_f,Cf,";liquid;","linewidth", 5);
      set(gca,"fontsize", 18);
      # xlim([-0.6 0.6]);

      h = legend ({"vapor","liquid"});
      set (h, "fontsize", 18)

    endif




  
  else

    printf("\n");
    printf("  [ERROR]  Unable to compute concentrations for Tr = %f\n",Tr);
    printf("\n");
  
  endif




endfor