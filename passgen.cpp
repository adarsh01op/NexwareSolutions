#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

// Function to generate a password with the specified criteria
std::string generatePassword(int length, bool includeUppercase, bool includeLowercase, bool includeNumbers, bool includeSymbols) {
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string numbers = "0123456789";
    const std::string symbols = "!@#$%^&*()";
    
    std::string characterSet;
    if (includeUppercase) characterSet += uppercase;
    if (includeLowercase) characterSet += lowercase;
    if (includeNumbers) characterSet += numbers;
    if (includeSymbols) characterSet += symbols;

    if (characterSet.empty()) {
        std::cerr << "Error: No character types selected. Cannot generate password." << std::endl;
        return "";
    }

    std::string password;
    for (int i = 0; i < length; ++i) {
        int index = rand() % characterSet.size();
        password += characterSet[index];
    }
    
    return password;
}

int main() {
    int length;
    char choice;
    bool includeUppercase, includeLowercase, includeNumbers, includeSymbols;

    std::cout << "Enter the desired length of the password: ";
    std::cin >> length;

    if (length <= 0) {
        std::cerr << "Error: Password length must be greater than 0." << std::endl;
        return 1;
    }

    // Options for password complexity
    std::cout << "Include uppercase letters? (y/n): ";
    std::cin >> choice;
    includeUppercase = (choice == 'y' || choice == 'Y');

    std::cout << "Include lowercase letters? (y/n): ";
    std::cin >> choice;
    includeLowercase = (choice == 'y' || choice == 'Y');

    std::cout << "Include numbers? (y/n): ";
    std::cin >> choice;
    includeNumbers = (choice == 'y' || choice == 'Y');

    std::cout << "Include symbols? (y/n): ";
    std::cin >> choice;
    includeSymbols = (choice == 'y' || choice == 'Y');

    srand(static_cast<unsigned int>(time(0)));  // Initialize random seed

    std::string password = generatePassword(length, includeUppercase, includeLowercase, includeNumbers, includeSymbols);
    
    if (!password.empty()) {
        std::cout << "Generated Password: " << password << std::endl;
    }

    return 0;
}
