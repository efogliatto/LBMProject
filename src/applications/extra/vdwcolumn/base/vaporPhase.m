function [Er,C,Int] = vaporPhase(cg_0, Tr, de, nn)

  
  # Initial condition

  C = zeros(nn,1);
  Er = zeros(nn,1);
  Int = zeros(nn,1);
  C(1) = cg_0;


  
  # Integrate differential equation
  
  for i = 2 : nn

    a = Tr / ((1.0 - C(i-1)/3.0)^2);

    b = 9.0 * C(i-1) / 4.0;
    
    f = C(i-1) / ( a - b );
    
    C(i) = C(i-1) - de * f;

    Er(i) = Er(i-1) + de;
    
  endfor



  # Integrate density profile

  for i = 2 : nn

    Int(i) = Int(i-1) + 0.5 * (C(i) + C(i-1)) * de;
    
  endfor

  
endfunction