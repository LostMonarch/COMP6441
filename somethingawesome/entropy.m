function H = entropy(positive, negative)
    if (positive == 0) || (negative == 0)
        H = 0;
    else
        totalMembers = positive + negative;
        p_plus = positive / totalMembers;
        p_minus = negative / totalMembers;
        optionA = (-1 * p_plus * log2(p_plus));
        optionB = (-1 * p_minus * log2(p_minus));
        H = optionA + optionB;
    end