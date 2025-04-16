#include "ManageTokens.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

ManageTokens::ManageTokens() {}

ManageTokens::~ManageTokens() {}

void ManageTokens::registerWallet(TokenWallet *wallet)
{
    wallets.push_back(wallet);
}

std::string ManageTokens::generateHash(const std::string &input)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

bool ManageTokens::mintToken(int walletIndex, const std::string &tokenName, const std::string &assetString)
{
    if (walletIndex < 0 || walletIndex >= wallets.size())
    {
        std::cout << "Invalid wallet index." << std::endl;
        return false;
    }

    // Generate unique hash for the token
    std::string tokenHash = generateHash(assetString);

    // Create a new token
    std::unique_ptr<NfToken> newToken = std::make_unique<NfToken>(tokenName, tokenHash);

    // Add token to the specified wallet
    wallets[walletIndex]->push_back(std::move(newToken));

    std::cout << "Token " << tokenName << " minted and added to wallet " << walletIndex << std::endl;
    return true;
}

bool ManageTokens::transferToken(int fromWalletIndex, int toWalletIndex, int tokenIndex)
{
    // Check if wallet indices are valid
    if (fromWalletIndex < 0 || fromWalletIndex >= wallets.size() ||
        toWalletIndex < 0 || toWalletIndex >= wallets.size())
    {
        std::cout << "Invalid wallet index." << std::endl;
        return false;
    }

    // Check if token index is valid
    if (tokenIndex < 0 || tokenIndex >= wallets[fromWalletIndex]->size())
    {
        std::cout << "Invalid token index." << std::endl;
        return false;
    }

    // Transfer token from source wallet to destination wallet
    // This is where unique_ptr shines - we can move ownership
    wallets[toWalletIndex]->push_back(std::move((*wallets[fromWalletIndex])[tokenIndex]));

    // Remove the (now null) pointer from the source wallet
    wallets[fromWalletIndex]->erase(wallets[fromWalletIndex]->begin() + tokenIndex);

    std::cout << "Token transferred from wallet " << fromWalletIndex
              << " to wallet " << toWalletIndex << std::endl;
    return true;
}

void ManageTokens::printWalletContents(int walletIndex)
{
    if (walletIndex < 0 || walletIndex >= wallets.size())
    {
        std::cout << "Invalid wallet index." << std::endl;
        return;
    }

    std::cout << "Wallet " << walletIndex << " contents:" << std::endl;
    if (wallets[walletIndex]->empty())
    {
        std::cout << "  (empty)" << std::endl;
        return;
    }

    for (size_t i = 0; i < wallets[walletIndex]->size(); i++)
    {
        std::cout << "Token " << i << ":" << std::endl;
        (*wallets[walletIndex])[i]->printTokenInfo();
        std::cout << std::endl;
    }
}

int ManageTokens::getWalletCount() const
{
    return wallets.size();
}