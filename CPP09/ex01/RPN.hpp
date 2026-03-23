#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>

class RPN
{
public:
    RPN();
    RPN(const RPN& src);
    RPN& operator=(const RPN& src);
    ~RPN();

    // Returns result; throws std::runtime_error on invalid expression.
    int evaluate(const std::string& expr);

private:
    std::stack<int> _stack;
};

#endif
