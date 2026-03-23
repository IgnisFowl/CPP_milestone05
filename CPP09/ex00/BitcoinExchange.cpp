#include "BitcoinExchange.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

// ─── Orthodox Canonical Form ─────────────────────────────────────────────────

BitcoinExchange::BitcoinExchange(const std::string& dbFile)
{
    loadDatabase(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src) : _db(src._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src)
{
    if (this != &src)
        _db = src._db;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// ─── Private helpers ──────────────────────────────────────────────────────────

void BitcoinExchange::loadDatabase(const std::string& dbFile)
{
    std::ifstream f(dbFile.c_str());
    if (!f.is_open())
        throw std::runtime_error("Error: could not open database file.");

    std::string line;
    std::getline(f, line); // skip header "date,exchange_rate"

    while (std::getline(f, line))
    {
        if (line.empty())
            continue;
        std::size_t comma = line.find(',');
        if (comma == std::string::npos)
            continue;
        std::string date  = line.substr(0, comma);
        std::string price = line.substr(comma + 1);
        _db[date] = static_cast<float>(std::atof(price.c_str()));
    }
}

// Returns true if YYYY-MM-DD has valid ranges.
// We do a basic structural + range check; exact day-per-month is not enforced
// (the subject doesn't ask for full calendar validation).
bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());
    if (month < 1 || month > 12) return false;
    if (day   < 1 || day   > 31) return false;
    return true;
}

// Parses token into float; returns false on error.
bool BitcoinExchange::isValidValue(const std::string& token, float& out) const
{
    if (token.empty()) return false;

    // Check format: optional leading spaces stripped by caller, 
    // must be numeric (digits, optional single dot, optional leading '-')
    std::string s = token;
    // trim leading spaces
    std::size_t start = s.find_first_not_of(" \t");
    if (start == std::string::npos) return false;
    s = s.substr(start);

    bool hasDot  = false;
    std::size_t begin = 0;
    if (s[0] == '-') begin = 1;

    for (std::size_t i = begin; i < s.size(); ++i)
    {
        if (s[i] == '.')
        {
            if (hasDot) return false;
            hasDot = true;
        }
        else if (s[i] < '0' || s[i] > '9')
            return false;
    }

    out = static_cast<float>(std::atof(s.c_str()));
    return true;
}

// ─── Public interface ─────────────────────────────────────────────────────────

void BitcoinExchange::processInput(const std::string& inputFile) const
{
    std::ifstream f(inputFile.c_str());
    if (!f.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(f, line); // skip header "date | value"

    while (std::getline(f, line))
    {
        if (line.empty())
            continue;

        // Split on " | "
        std::size_t sep = line.find(" | ");
        if (sep == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date  = line.substr(0, sep);
        std::string valStr = line.substr(sep + 3);

        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        float value;
        if (!isValidValue(valStr, value))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        // Find the closest date <= date in the DB
        std::map<std::string, float>::const_iterator it = _db.lower_bound(date);
        if (it == _db.end() || it->first != date)
        {
            // lower_bound returns first key >= date, so go back one step
            if (it == _db.begin())
            {
                std::cerr << "Error: bad input => " << date << std::endl;
                continue;
            }
            --it;
        }

        std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
    }
}
