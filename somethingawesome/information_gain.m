function G = information_gain(x)
    top_plus = x(1);
    top_minus = x(2);
    left_plus = x(3);
    left_minus = x(4);
    right_plus = x(5);
    right_minus = x(6);
    
    root_entropy = entropy(top_plus, top_minus);
    right_entropy = entropy(right_plus, right_minus);
    left_entropy = entropy(left_plus, left_minus);
    
    totalMembers = top_plus + top_minus;
    totalRight = right_plus + right_minus;
    totalLeft = left_plus + left_minus;
    
    right_weight = totalRight / totalMembers;
    left_weight = totalLeft / totalMembers;
    
    G = root_entropy - (right_weight * right_entropy) - (left_weight * left_entropy);