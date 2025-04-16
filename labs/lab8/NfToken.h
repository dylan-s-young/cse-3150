#ifndef NFTOKEN_H
#define NFTOKEN_H

#include <string>
#include <vector>
#include <memory>

class NfToken
{
private:
    std::string name;
    std::string tokenHash;

public:
    // Constructor
    NfToken(const std::string &tokenName, const std::string &hash);

    // Getters
    std::string getName() const;
    std::string getTokenHash() const;

    // Print token information
    void printTokenInfo() const;
};

// Type definition for a wallet of tokens
using TokenWallet = std::vector<std::unique_ptr<NfToken>>;

#endif // NFTOKEN_H