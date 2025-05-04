#include "password_generator.hpp"
#include <iostream>

int main() {
    std::string firstName, lastName, service, secretKey; // Declare variables for user input

    std::cout << "Enter First Name: ";
    std::getline(std::cin, firstName);
    
    std::cout << "Enter Last Name: ";
    std::getline(std::cin, lastName);
    
    std::cout << "Enter Service Name (e.g., twitter.com): ";
    std::getline(std::cin, service);
    
    std::cout << "Enter Secret Key (6 words separated by space): ";
    std::getline(std::cin, secretKey);

    const std::string wordlistFile = "Wordlists/default_wordlist.txt";
    try {
        PasswordGenerator generator(wordlistFile); // Initialize the password generator with the wordlist file
        
        std::string password = generator.generate(firstName, lastName, service, secretKey); // Generate the password
        std::cout << "Generated Password: " << password << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
