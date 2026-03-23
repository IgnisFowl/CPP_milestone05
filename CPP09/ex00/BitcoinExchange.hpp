#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
public:
    BitcoinExchange(const std::string& dbFile);
    BitcoinExchange(const BitcoinExchange& src);
    BitcoinExchange& operator=(const BitcoinExchange& src);
    ~BitcoinExchange();

    void processInput(const std::string& inputFile) const;

private:
    BitcoinExchange(); // no default construction without DB

    std::map<std::string, float> _db;

    void        loadDatabase(const std::string& dbFile);
    bool        isValidDate(const std::string& date) const;
    bool        isValidValue(const std::string& token, float& out) const;
};

#endif
