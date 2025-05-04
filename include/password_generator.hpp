#pragma once
#include <string>
#include <vector>

/// @brief Class to generate passwords based on a wordlist and user input.
class PasswordGenerator {
public:

    /// @brief Constructor that initializes the password generator with a wordlist.
    /// @param wordlistPath Path to the wordlist file.
    explicit PasswordGenerator(const std::string& wordlistPath);
    
    /// @brief Generates a password based on the user's name, last name, service, and secret key.
    /// @param name User's first name.
    /// @param lastname User's last name.
    /// @param service Service name (e.g., twitter.com).
    /// @param secretKey Secret key (6 words separated by space).
    /// @return Generated password.
    std::string generate(
        const std::string& name, 
        const std::string& lastname,
        const std::string& service, 
        const std::string& secretKey
    );

private:
    std::vector<std::string> words; // List of words from the wordlist file.
    std::vector<char> specialChars = {'!', '@', '#', '$', '%', '^', '&', '*', '-', '+'}; // Special characters to be used in the password.

    /// @brief Splits a string into words based on spaces.
    /// @param str The string to be split.
    /// @return A vector of words.
    void loadWordlist(const std::string& path);
    
    /// @brief Capitalizes the first letter of a word.
    /// @param word The word to be capitalized.
    /// @return The capitalized word.
    std::string capitalize(const std::string& word);
};
