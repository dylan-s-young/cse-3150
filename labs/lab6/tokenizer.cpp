#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

class Tokenizer
{
private:
    std::unordered_map<std::string, int> wordToToken;
    std::vector<std::string> tokenToWord;
    int nextTokenId;

public:
    // Constructor
    Tokenizer() : nextTokenId(0) {}

    // Process a file and tokenize all words
    bool processFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file)
        {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return false;
        }

        std::string word;
        while (file >> word)
        {
            // Add word to our dictionary if it's not already there
            if (wordToToken.find(word) == wordToToken.end())
            {
                wordToToken[word] = nextTokenId;
                tokenToWord.push_back(word);
                nextTokenId++;
            }
        }

        file.close();
        return true;
    }

    // Get token ID for a word
    int getTokenId(const std::string &word) const
    {
        auto it = wordToToken.find(word);
        if (it != wordToToken.end())
        {
            return it->second;
        }
        return -1; // Return -1 if word not found
    }

    // Get word for a token ID
    std::string getWord(int tokenId) const
    {
        if (tokenId >= 0 && tokenId < static_cast<int>(tokenToWord.size()))
        {
            return tokenToWord[tokenId];
        }
        return ""; // Return empty string if token ID not found
    }

    // Print all words and their token IDs
    void printDictionary() const
    {
        std::cout << "Dictionary Contents:" << std::endl;
        std::cout << "-------------------" << std::endl;
        std::cout << "Token ID | Word" << std::endl;
        std::cout << "-------------------" << std::endl;

        for (const auto &entry : wordToToken)
        {
            std::cout << entry.second << " | " << entry.first << std::endl;
        }
        std::cout << "-------------------" << std::endl;
        std::cout << "Total unique words: " << wordToToken.size() << std::endl;
    }

    // Return the total number of unique tokens
    int size() const
    {
        return static_cast<int>(wordToToken.size());
    }
};

// Example main function to demonstrate usage
int main()
{
    Tokenizer tokenizer;

    // Process a file
    std::string filename;
    std::cout << "Enter the filename to process: ";
    std::cin >> filename;

    if (!tokenizer.processFile(filename))
    {
        return 1;
    }

    // Print the dictionary
    tokenizer.printDictionary();

    // Demonstration of looking up tokens and words
    std::string wordToLookup;
    std::cout << "\nEnter a word to look up its token ID: ";
    std::cin >> wordToLookup;

    int tokenId = tokenizer.getTokenId(wordToLookup);
    if (tokenId != -1)
    {
        std::cout << "Token ID for '" << wordToLookup << "' is: " << tokenId << std::endl;
    }
    else
    {
        std::cout << "Word '" << wordToLookup << "' not found in dictionary." << std::endl;
    }

    int idToLookup;
    std::cout << "\nEnter a token ID to look up its word: ";
    std::cin >> idToLookup;

    std::string word = tokenizer.getWord(idToLookup);
    if (!word.empty())
    {
        std::cout << "Word for token ID " << idToLookup << " is: '" << word << "'" << std::endl;
    }
    else
    {
        std::cout << "Token ID " << idToLookup << " not found in dictionary." << std::endl;
    }

    return 0;
}