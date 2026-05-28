#include <iostream>
#include <limits>
#include <string>
#include <cctype>

[[nodiscard]] bool saver() {
    if (std::cin.eof()) {
        std::cerr << "[!]DANGER. CLOSING PROGRAM FOR SAFETY.\n";
        return false;
    }

    if (std::cin.fail()) {
        std::cin.clear();
    }

    return true;
}

void bufferClear() {
    if (std::cin.fail()) {
        std::cin.clear();
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool userInput(std::string& input);
int getDiggits(const int& cardNumber);
int sumOddDiggits(const std::string& cardNumber);
int sumEvenDiggits(const std::string& cardNumber);
char getResult(const int& oddNumber, const int& evenNumber);
char getChoice();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string cardNumber;
    int result;
    bool userChoice = true;
    int resultX;
    int resultY;
    char finalStatus;
    char user;

    while (userChoice) {
        if (!userInput(cardNumber)) {
            continue;
        }
        resultX = sumOddDiggits(cardNumber);
        resultY = sumEvenDiggits(cardNumber);
        finalStatus = getResult(resultX, resultY);

        switch (finalStatus) {
            case 'V': std::cout << cardNumber << "\nIs valid number.\n"; break;
            case 'N': std::cout << cardNumber << "\nIs not valid number\n"; break;
            default: std::cout << cardNumber << "Unknown\n"; break;
        }

        user = getChoice();

        switch (user) {
            case 'C':
                continue;
            case 'E':
                std::cout << "Exiting program\n";
                userChoice = false;
                break;
            default:
                std::cout << "Input invalid\n";
                break;
        }
    }

    std::cout << "Thankyou. Have a good day\n";
    return 0;
}

bool userInput(std::string& input) {

    std::cout << "======================\n";
    std::cout << "       WELCOME TO     \n";
    std::cout << "  C++ LUHN ALGORITHM  \n";
    std::cout << "======================\n";

    std::cout << "Input card number: " << std::flush;
    if (!(std::cin >> input)) {
        if (!(saver())) return false;
        bufferClear();
        std::cerr << "Fatal error! please input normal number.\n";
        return false;
    }
    bufferClear();
    return true;
}

int getDiggits(const int& cardNumber) {
    return cardNumber % 10 + (cardNumber / 10 % 10);
}

int sumOddDiggits(const std::string& cardNumber) {
    int sum = 0;

    for (int i = cardNumber.size() - 1; i >= 0; i -= 2) {
        sum += cardNumber[i] - '0';
    }

    return sum;
}

int sumEvenDiggits(const std::string& cardNumber) {
    int sum = 0;

    for (int i = cardNumber.size() - 2; i >= 0; i -= 2) {
        sum += getDiggits((cardNumber[i] - '0') * 2);
    }

    return sum;
}

char getResult(const int& oddNumber, const int& evenNumber) {
    int result = oddNumber + evenNumber;
    
    if (result % 10 == 0) {
        return 'V';
    } else if (result % 10 != 0) {
        return 'N';
    } else {
        std::cout << "Invalid\n";
    }

    return result;
}

char getChoice() {
    char option;
    std::cout << "Choose C for continue or choose E for exit: " << std::flush;
    if (!(std::cin >> option)) {
        if (!(saver())) return 1;
        bufferClear();
        std::cerr << "Fatal error! please input normal number\n";
        return 'E';
    }
    bufferClear();
    option = std::toupper(static_cast<unsigned char>(option));

    return option;
}