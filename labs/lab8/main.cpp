#include "NfToken.h"
#include "ManageTokens.h"
#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <string>

// Function to demonstrate the problem with int-based tokens
void demonstrateIntTokenProblem()
{
    std::cout << "\n=== Demonstrating the problem with int-based tokens ===" << std::endl;

    // Create two wallets with int tokens
    std::vector<int> intWallet1 = {1, 2, 3};
    std::vector<int> intWallet2;

    // Print initial state
    std::cout << "Initial state:" << std::endl;
    std::cout << "Wallet 1: ";
    for (int token : intWallet1)
    {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    std::cout << "Wallet 2: ";
    for (int token : intWallet2)
    {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    // Transfer a token (copy the value, not move ownership)
    int tokenToTransfer = intWallet1[1]; // Token with value 2
    intWallet2.push_back(tokenToTransfer);

    // Original token is still in wallet1! This is the problem!

    std::cout << "\nAfter 'transfer':" << std::endl;
    std::cout << "Wallet 1: ";
    for (int token : intWallet1)
    {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    std::cout << "Wallet 2: ";
    for (int token : intWallet2)
    {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    std::cout << "Problem: The token exists in both wallets now! This breaks uniqueness." << std::endl;
}

// Function to time operations with different integer types
void compareIntegerTypes()
{
    std::cout << "\n=== Comparing Performance of Integer Types ===" << std::endl;

    const int iterations = 1000000;

    // Timing for int
    auto startInt = std::chrono::high_resolution_clock::now();
    std::vector<int> intVector;
    for (int i = 0; i < iterations; i++)
    {
        intVector.push_back(i);
    }
    auto endInt = std::chrono::high_resolution_clock::now();
    auto intDuration = std::chrono::duration_cast<std::chrono::microseconds>(endInt - startInt).count();

    // Timing for long int
    auto startLong = std::chrono::high_resolution_clock::now();
    std::vector<long int> longVector;
    for (long int i = 0; i < iterations; i++)
    {
        longVector.push_back(i);
    }
    auto endLong = std::chrono::high_resolution_clock::now();
    auto longDuration = std::chrono::duration_cast<std::chrono::microseconds>(endLong - startLong).count();

    // Simulate a "big integer" using strings
    auto startBig = std::chrono::high_resolution_clock::now();
    std::vector<std::string> bigIntVector;
    for (int i = 0; i < iterations; i++)
    {
        bigIntVector.push_back(std::to_string(i));
    }
    auto endBig = std::chrono::high_resolution_clock::now();
    auto bigDuration = std::chrono::duration_cast<std::chrono::microseconds>(endBig - startBig).count();

    // Display results
    std::cout << "Performance comparison for " << iterations << " operations:" << std::endl;
    std::cout << "int:      " << intDuration << " microseconds" << std::endl;
    std::cout << "long int: " << longDuration << " microseconds" << std::endl;
    std::cout << "big int:  " << bigDuration << " microseconds" << std::endl;
}

int main()
{
    std::cout << "=== NFT Token Management System ===" << std::endl;

    // Create token manager
    ManageTokens tokenManager;

    // Create wallets
    TokenWallet wallet1;
    TokenWallet wallet2;
    TokenWallet wallet3;

    // Register wallets with the manager
    tokenManager.registerWallet(&wallet1);
    tokenManager.registerWallet(&wallet2);
    tokenManager.registerWallet(&wallet3);

    // Mint some tokens
    tokenManager.mintToken(0, "CryptoCat", "cat12345");
    tokenManager.mintToken(0, "CryptoDog", "dog54321");
    tokenManager.mintToken(1, "CryptoFish", "fish9876");

    // Print initial wallet contents
    std::cout << "\nInitial wallet contents:" << std::endl;
    tokenManager.printWalletContents(0);
    tokenManager.printWalletContents(1);
    tokenManager.printWalletContents(2);

    // Transfer tokens
    std::cout << "\nTransferring tokens..." << std::endl;
    tokenManager.transferToken(0, 2, 0); // Transfer CryptoCat from wallet 0 to wallet 2

    // Print wallet contents after transfer
    std::cout << "\nWallet contents after transfer:" << std::endl;
    tokenManager.printWalletContents(0);
    tokenManager.printWalletContents(1);
    tokenManager.printWalletContents(2);

    // Demonstrate problem with int-based tokens
    demonstrateIntTokenProblem();

    // Compare performance of different integer types
    compareIntegerTypes();

    return 0;
}