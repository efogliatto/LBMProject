function c = Cl_from_Tr(cg, cl, Tr)
  
  c = 8.0 * Tr / ( (3.0 - cg) * (3.0 - cl) )  -  cg;
  
endfunction