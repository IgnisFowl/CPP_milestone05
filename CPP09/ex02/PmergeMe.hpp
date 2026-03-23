#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe& src);
    PmergeMe& operator=(const PmergeMe& src);
    ~PmergeMe();

    // Sort using each container and print timing
    void run(int argc, char* argv[]);

private:
    // Ford-Johnson for vector
    void fordJohnsonVector(std::vector<int>& v);
    void insertionSortVector(std::vector<int>& chain, const std::vector<int>& pending);
    int  binarySearchVector(const std::vector<int>& v, int target, int hi) const;

    // Ford-Johnson for deque
    void fordJohnsonDeque(std::deque<int>& d);
    void insertionSortDeque(std::deque<int>& chain, const std::deque<int>& pending);
    int  binarySearchDeque(const std::deque<int>& d, int target, int hi) const;

    // Jacobsthal sequence helper
    static std::vector<int> jacobsthalSequence(int n);
};

#endif
