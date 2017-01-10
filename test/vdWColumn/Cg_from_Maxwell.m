function c = Cg_from_Maxwell(cg, cl, Tr)
  
  # a = log( (3.0/cg - 1.0) / (3.0/cl - 1.0) );

  # b = 3.0 / (3.0 - cl)  +  3.0 / (3.0 - cg);

  # c = cl  -  a * (cl + cg) / b ;


  a = log( (3.0/cg - 1.0) / (3.0/cl - 1.0) );

  c = cl + ( 3.0 * P_sat_r(cg,cl) * (1.0/cg - 1.0/cl)  -  8.0 * Tr * a ) / 9.0;
  
endfunction