function y = redConFunction(x,Tr)

  # Variables
  # x(1) = cl
  # x(2) = cg

  # # Reduced temperature
  # Tr = 0.50;

  # Function evaluations
  y = zeros(2,1);

  # Maxwell rule
  y(1) = 8.0 * Tr * log( (3.0/x(2) - 1.0) / (3.0/x(1) - 1.0) )   +   9.0 * (x(2) - x(1))  -  3.0 * P_sat_r(x(2),x(1)) * (1.0/x(2) - 1.0/x(1)); 

  # vdW equation
  y(2) = 8.0 * Tr - (x(2)+x(1)) * (3.0-x(1)) * (3.0-x(2));
  
endfunction