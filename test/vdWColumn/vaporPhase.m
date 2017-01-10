function C = gasPhase(cg_0, Tr, de, nn)

  # Initial condition
  C = zeros(nn,1);
  C(1) = cg_0; 

  for i = 2 : nn

    a = Tr / ((1.0 - C(i)/3.0)^2);

    b = 9.0 * C(i) / 4.0;
    
    f = C(i) / ( a - b );
    
    C(i) = C(i-1) - de * f;
    
  endfor

  
endfunction