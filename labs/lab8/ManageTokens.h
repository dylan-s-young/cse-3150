#ifndef MANAGE_TOKENS_H
#define MANAGE_TOKENS_H

#include "NfToken.h"
#include <string>
#include <vector>
#include <memory>

class ManageTokens
{
private:
    // Vector of wallets
    std::vector<TokenWallet *> wallets;

    // Generate SHA-256 hash for a string
    std::string generateHash(const std::string &input);

public:
    // Constructor
    ManageTokens();

    // Destructor
    ~ManageTokens();

    // Register a wallet to be managed
    void registerWallet(TokenWallet *wallet);

    // Mint a new token and add it to the specified wallet
    bool mintToken(int walletIndex, const std::string &tokenName, const std::string &assetString);

    // Transfer a token from one wallet to another
    bool transferToken(int fromWalletIndex, int toWalletIndex, int tokenIndex);

    // Print all tokens in a wallet
    void printWalletContents(int walletIndex);

    // Count the number of wallets
    int getWalletCount() const;
};

#endif // MANAGE_TOKENS_H