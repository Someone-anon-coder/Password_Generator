#include "password_generator.hpp"
#include "hash_util.hpp"
#include <fstream>
#include <random>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <cctype>

PasswordGenerator::PasswordGenerator(const std::string& wordlistPath) {
    loadWordlist(wordlistPath);
}

void PasswordGenerator::loadWordlist(const std::string& path) {
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error("Unable to open wordlist file");

    std::string word; // Temporary variable to hold each word
    while (std::getline(file, word)) {
        if (!word.empty())
            words.emplace_back(word);
    }

    if (words.size() < 100000)
        throw std::runtime_error("Wordlist must contain a large number of entries (> 100000)");
}

std::string PasswordGenerator::capitalize(const std::string& word) {
    if (word.empty()) return word;
    
    std::string result = word; // Copy the word to a new string
    result[0] = std::toupper(result[0]);
    
    return result;
}

std::string PasswordGenerator::generate(
    const std::string& name, 
    const std::string& lastname,
    const std::string& service, 
    const std::string& secretKey
) {
    std::ostringstream combined; // Use ostringstream for efficient string concatenation
    combined << name << ":" << lastname << ":" << service << ":" << secretKey << ":STATIC_SALT_v1";

    std::uint64_t seed = hash_seed(combined.str()); // Hash the combined string to get a seed
    std::mt19937_64 rng(seed); // Initialize the random number generator with the seed

    std::uniform_int_distribution<size_t> wordDist(0, words.size() - 1); // Distribution for selecting words
    std::uniform_int_distribution<size_t> specialDist(0, specialChars.size() - 1); // Distribution for selecting special characters
    std::uniform_int_distribution<int> digitDist(0, 9); // Distribution for selecting digits

    std::ostringstream password; // Use ostringstream for efficient string concatenation
    for (int i = 0; i < 4; ++i) {
        std::string word = capitalize(words[wordDist(rng)]); // Capitalize the first letter of the word
        password << word;
    }

    password << specialChars[specialDist(rng)];
    password << digitDist(rng);

    return password.str();
}
