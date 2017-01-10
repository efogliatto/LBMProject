function p = P_sat_r(cg, cl)
  
  p = cg * cl * (3.0 - (cg + cl));
  
endfunction