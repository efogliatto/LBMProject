function [Er,C] = liquidPhase(cl_0, Tr, de, nn)

  # Initial condition
  C = zeros(nn,1);
  Er = zeros(nn,1);  
  C(nn) = cl_0;
  Er(nn) = 0;

  for i = (nn-1) : -1 : 1
    
    a = Tr / ((1.0 - C(i+1)/3.0)^2);

    b = 9.0 * C(i+1) / 4.0;
    
    f = C(i+1) / ( a - b );
    
    C(i) = C(i+1) + de * f;

    Er(i) = Er(i+1) - de;
    
  endfor

  
endfunction