#include "NfToken.h"
#include <iostream>

NfToken::NfToken(const std::string &tokenName, const std::string &hash)
    : name(tokenName), tokenHash(hash) {}

std::string NfToken::getName() const
{
    return name;
}

std::string NfToken::getTokenHash() const
{
    return tokenHash;
}

void NfToken::printTokenInfo() const
{
    std::cout << "Token Name: " << name << std::endl;
    std::cout << "Token Hash: " << tokenHash << std::endl;
}