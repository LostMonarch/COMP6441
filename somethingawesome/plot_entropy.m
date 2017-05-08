test_vals = [0:0.01:1];
entropies = [];
for n = 1:length(test_vals)
    entropies(n) = entropy(test_vals(n), 1 - test_vals(n));
end
plot(entropies)