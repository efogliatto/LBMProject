# Carnahan - Starling

function [p_eos] = CS_EOS(rho, T)

  a = 0.5;

  b = 4;

  R = 1;

  alpha = b * rho / 4;
  
  p_eos = rho * R * T * (1 + alpha + alpha^2 - alpha^3) / (1-alpha)^3 - a * rho^2;
  
endfunction


