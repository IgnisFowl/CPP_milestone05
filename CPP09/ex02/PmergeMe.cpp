#include "PmergeMe.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <sys/time.h>

// ─── Orthodox Canonical Form ─────────────────────────────────────────────────

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& src) { (void)src; }
PmergeMe& PmergeMe::operator=(const PmergeMe& src) { (void)src; return *this; }
PmergeMe::~PmergeMe() {}

// ─── Jacobsthal helper ───────────────────────────────────────────────────────
// Returns Jacobsthal indices up to n terms: 0,1,1,3,5,11,21,...
// We use these to determine the insertion order of pending elements.

std::vector<int> PmergeMe::jacobsthalSequence(int n)
{
    std::vector<int> jac;
    jac.push_back(0);
    jac.push_back(1);
    while (jac.back() < n)
    {
        int sz = static_cast<int>(jac.size());
        jac.push_back(jac[sz - 1] + 2 * jac[sz - 2]);
    }
    return jac;
}

// ─── VECTOR implementation ───────────────────────────────────────────────────

// Binary search: find insertion position for target in v[0..hi) 
int PmergeMe::binarySearchVector(const std::vector<int>& v, int target, int hi) const
{
    int lo = 0;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        if (v[mid] <= target)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

void PmergeMe::insertionSortVector(std::vector<int>& chain, const std::vector<int>& pending)
{
    int pSize = static_cast<int>(pending.size());
    std::vector<int> jac = jacobsthalSequence(pSize);

    // Build insertion order using Jacobsthal sequence
    std::vector<bool> inserted(pSize, false);
    std::vector<int> order;

    for (int idx = 2; idx < static_cast<int>(jac.size()); ++idx)
    {
        int curr = jac[idx] - 1; // 0-based index into pending
        if (curr >= pSize) curr = pSize - 1;

        // Insert from curr down to jac[idx-1] (filling backwards)
        for (int k = curr; k >= jac[idx - 1] && k >= 0 && k < pSize; --k)
        {
            if (!inserted[k])
            {
                order.push_back(k);
                inserted[k] = true;
            }
        }
    }
    // Insert any remaining
    for (int k = 0; k < pSize; ++k)
        if (!inserted[k])
            order.push_back(k);

    // Insert each pending element at its correct position in chain
    for (int i = 0; i < static_cast<int>(order.size()); ++i)
    {
        int val = pending[order[i]];
        // The upper bound for binary search: the paired element in chain
        // (pending[j] is paired with chain[j+1] for j < pSize, since chain has
        //  one extra element at front if odd). The paired chain element is at
        //  index order[i]+1 (but chain grows as we insert, so use chain.size()).
        int hi = static_cast<int>(chain.size());
        // paired chain partner is at position order[i]+1 in original chain
        // but we must not search past it
        int partner = order[i] + 1; // 1-indexed in chain
        if (partner < hi) hi = partner;
        int pos = binarySearchVector(chain, val, hi);
        chain.insert(chain.begin() + pos, val);
    }
}

void PmergeMe::fordJohnsonVector(std::vector<int>& v)
{
    int n = static_cast<int>(v.size());
    if (n <= 1)
        return;

    // 1. Pair up elements; make larger first within each pair
    bool hasOdd = (n % 2 != 0);
    int straggler = hasOdd ? v[n - 1] : 0;

    std::vector<int> larger;
    std::vector<int> smaller;
    for (int i = 0; i + 1 < n - (hasOdd ? 1 : 0); i += 2)
    {
        if (v[i] > v[i + 1])
        {
            larger.push_back(v[i]);
            smaller.push_back(v[i + 1]);
        }
        else
        {
            larger.push_back(v[i + 1]);
            smaller.push_back(v[i]);
        }
    }

    // 2. Recursively sort larger elements
    fordJohnsonVector(larger);

    // 3. Build main chain: first element of smaller followed by sorted larger
    std::vector<int> chain;
    chain.push_back(smaller[0]);
    for (int i = 0; i < static_cast<int>(larger.size()); ++i)
        chain.push_back(larger[i]);

    // 4. Pending = rest of smaller (indices 1..end), plus straggler
    std::vector<int> pending;
    for (int i = 1; i < static_cast<int>(smaller.size()); ++i)
        pending.push_back(smaller[i]);
    if (hasOdd)
        pending.push_back(straggler);

    // 5. Insert pending into chain using optimal order
    insertionSortVector(chain, pending);

    v = chain;
}

// ─── DEQUE implementation ────────────────────────────────────────────────────

int PmergeMe::binarySearchDeque(const std::deque<int>& d, int target, int hi) const
{
    int lo = 0;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        if (d[mid] <= target)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

void PmergeMe::insertionSortDeque(std::deque<int>& chain, const std::deque<int>& pending)
{
    int pSize = static_cast<int>(pending.size());
    std::vector<int> jac = jacobsthalSequence(pSize);

    std::vector<bool> inserted(pSize, false);
    std::deque<int> order;

    for (int idx = 2; idx < static_cast<int>(jac.size()); ++idx)
    {
        int curr = jac[idx] - 1;
        if (curr >= pSize) curr = pSize - 1;
        for (int k = curr; k >= jac[idx - 1] && k >= 0 && k < pSize; --k)
        {
            if (!inserted[k])
            {
                order.push_back(k);
                inserted[k] = true;
            }
        }
    }
    for (int k = 0; k < pSize; ++k)
        if (!inserted[k])
            order.push_back(k);

    for (int i = 0; i < static_cast<int>(order.size()); ++i)
    {
        int val = pending[order[i]];
        int hi = static_cast<int>(chain.size());
        int partner = order[i] + 1;
        if (partner < hi) hi = partner;
        int pos = binarySearchDeque(chain, val, hi);
        chain.insert(chain.begin() + pos, val);
    }
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& d)
{
    int n = static_cast<int>(d.size());
    if (n <= 1)
        return;

    bool hasOdd = (n % 2 != 0);
    int straggler = hasOdd ? d[n - 1] : 0;

    std::deque<int> larger;
    std::deque<int> smaller;
    for (int i = 0; i + 1 < n - (hasOdd ? 1 : 0); i += 2)
    {
        if (d[i] > d[i + 1])
        {
            larger.push_back(d[i]);
            smaller.push_back(d[i + 1]);
        }
        else
        {
            larger.push_back(d[i + 1]);
            smaller.push_back(d[i]);
        }
    }

    fordJohnsonDeque(larger);

    std::deque<int> chain;
    chain.push_back(smaller[0]);
    for (int i = 0; i < static_cast<int>(larger.size()); ++i)
        chain.push_back(larger[i]);

    std::deque<int> pending;
    for (int i = 1; i < static_cast<int>(smaller.size()); ++i)
        pending.push_back(smaller[i]);
    if (hasOdd)
        pending.push_back(straggler);

    insertionSortDeque(chain, pending);

    d = chain;
}

// ─── Public run ──────────────────────────────────────────────────────────────

static long getUsec()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000L + tv.tv_usec;
}

void PmergeMe::run(int argc, char* argv[])
{
    std::vector<int> vec;
    std::deque<int>  deq;

    for (int i = 1; i < argc; ++i)
    {
        std::istringstream iss(argv[i]);
        int val;
        if (!(iss >> val) || val <= 0)
            throw std::runtime_error("Error");
        std::string rest;
        if (iss >> rest)
            throw std::runtime_error("Error");
        vec.push_back(val);
        deq.push_back(val);
    }

    if (vec.empty())
        throw std::runtime_error("Error");

    // Print before
    std::cout << "Before:";
    for (int i = 0; i < static_cast<int>(vec.size()); ++i)
        std::cout << " " << vec[i];
    std::cout << std::endl;

    // Sort vector
    long t0 = getUsec();
    fordJohnsonVector(vec);
    long t1 = getUsec();

    // Sort deque
    long t2 = getUsec();
    fordJohnsonDeque(deq);
    long t3 = getUsec();

    // Print after
    std::cout << "After:";
    for (int i = 0; i < static_cast<int>(vec.size()); ++i)
        std::cout << " " << vec[i];
    std::cout << std::endl;

    int n = static_cast<int>(vec.size());
    std::cout << "Time to process a range of " << n
              << " elements with std::vector : "
              << (t1 - t0) << " us" << std::endl;
    std::cout << "Time to process a range of " << n
              << " elements with std::deque  : "
              << (t3 - t2) << " us" << std::endl;
}
