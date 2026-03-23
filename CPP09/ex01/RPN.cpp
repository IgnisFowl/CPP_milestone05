#include "RPN.hpp"

#include <sstream>
#include <stdexcept>

// ─── Orthodox Canonical Form ─────────────────────────────────────────────────

RPN::RPN() {}
RPN::RPN(const RPN& src) : _stack(src._stack) {}
RPN& RPN::operator=(const RPN& src)
{
    if (this != &src)
        _stack = src._stack;
    return *this;
}
RPN::~RPN() {}

// ─── Evaluate ─────────────────────────────────────────────────────────────────

int RPN::evaluate(const std::string& expr)
{
    // Clear stack from any previous use
    while (!_stack.empty())
        _stack.pop();

    std::istringstream iss(expr);
    std::string token;

    while (iss >> token)
    {
        if (token.size() == 1 && (token[0] == '+' || token[0] == '-' ||
                                   token[0] == '*' || token[0] == '/'))
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Error");

            int b = _stack.top(); _stack.pop();
            int a = _stack.top(); _stack.pop();

            if (token[0] == '+') _stack.push(a + b);
            else if (token[0] == '-') _stack.push(a - b);
            else if (token[0] == '*') _stack.push(a * b);
            else
            {
                if (b == 0)
                    throw std::runtime_error("Error: division by zero.");
                _stack.push(a / b);
            }
        }
        else if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
        {
            _stack.push(token[0] - '0');
        }
        else
        {
            // Multi-digit numbers or invalid tokens are errors
            throw std::runtime_error("Error");
        }
    }

    if (_stack.size() != 1)
        throw std::runtime_error("Error");

    return _stack.top();
}
