function [cg, cl] = redConc(Tr)

  # Initial condition
  cl     = 1;
  cg     = 1;
  cl_old = 1e+06;
  cg_old = 1e+06;
  error = 1e+06;
  

  while(error >= 1e-10)
    
    cl_old = cl;
    cg_old = cg;
    
    cl = Cl_from_Tr(cg,cl,Tr);
    cg = Cg_from_Maxwell(cg,cl,Tr);

    error = abs( 0.5 * (cl - cl_old) / cl + 0.5 * (cg - cg_old) / cg );

  endwhile

  
  if(cl < cg)

    aux = cl;
    cl = cg;
    cg = aux;
    
  endif
  
endfunction