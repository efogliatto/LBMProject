function [Er,C,Int] = liquidPhase(cl_0, Tr, de, nn)

  
  # Initial condition

  C = zeros(nn,1);
  Er = zeros(nn,1);
  Int = zeros(nn,1);  
  C(nn) = cl_0;
  


  # Integrate differential equation
  
  for i = (nn-1) : -1 : 1
    
    a = Tr / ((1.0 - C(i+1)/3.0)^2);

    b = 9.0 * C(i+1) / 4.0;
    
    f = C(i+1) / ( a - b );
    
    C(i) = C(i+1) + de * f;

    Er(i) = Er(i+1) - de;
    
  endfor



  # Integrate density profile (inverse order)

  for i = 2 : nn

    Int(i) = Int(i-1) + 0.5 * (C(nn - i + 2) + C(nn - i + 1)) * de;
    
  endfor
  
  
endfunction