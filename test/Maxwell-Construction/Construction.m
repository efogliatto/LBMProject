clear all;

# Vector de densidad
rho = logspace(-4, 0, 10);

# Vector de presion
P_eos = zeros(size(rho,2),1);

for i = 1 : size(rho,2)
  P_eos(i) = CS_EOS(rho(i),0.0325);
end

plot(rho, P_eos);

