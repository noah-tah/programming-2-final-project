/*
Noah Tah
4/30/2025-5/1/2025
Programming II
Evan Vaverka
Northwestern Oklahoma State University
Assignment Description:
    The final for this class is to take one of the cipher systems we talked about and make a program that encrypts and decrypts messages.
    Probably the easiest way of doing this would be to use a shift (Ceaser) cipher.
    You are welcome to make this as complex as you would like though.
    You can use either C++ or Java for this assignment. 
    When the program starts it needs to ask the user if they want to encrypt a message, decrypt a message or to show the stored message.
    For these parts to work the user will need to know if there is a key to solving the cipher and will need to enter that after selecting an option.
    (Example: If using a shift cipher the user needs to know how many spaces to shift the alphabet so it lines up correctly.)
    So this mean that you have to submit the key to me when you turn in the code.
    The stored message is, "Encryption or decryption successful. This system is ready for further testing of messages." If the user selects the option to show the stored message, after accepting the key from the user, the program should display this message in its encrypted form and in it decrypted form. 

    If you have any questions or problems, get ahold of me. I can't help you if I dont know about the problem. 
    This is due by NOON, FRIDAY, MAY 9th. I wont accept it if this is late and you have not contacted me before the due time.
*/

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <limits>
#ifdef _WIN32
#include <cstdlib> // For system()
#endif

/*
Function prototypes to make compiler happy
*/
void encryptionDemonstration();
void programIntroduction();
void mainMenu();
void encryptMessage();
void decryptMessage();
std::string getMessageToEncrypt();
std::string caesarShiftEncryption(const std::string& message, int SHIFT);
std::string caesarShiftDecryption(const std::string& message, int shift);
int createXorKey(const std::string& KEY);
std::string xorEncryption(const std::string& message, const std::string& KEY);
std::string xorDecryption(const std::string& message, const std::string& KEY);
void printBinary(const std::string& message);
void waitForInput();
void clearScreen();
void encryptMessage();
/*
End of function prototypes
*/

std::string caesarShiftEncryption(const std::string& message, int SHIFT) {
    std::string encryptedMessage = message;
    for (char& c : encryptedMessage) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + SHIFT) % 26 + base;
        }
    }
    return encryptedMessage;
}

std::string caesarShiftDecryption(const std::string& message, int shift) {
    return caesarShiftEncryption(message, 26 - shift);
}

int createXorKey(const std::string& KEY) {
    int xorKey = 0;
    for (char c : KEY) {
        xorKey += static_cast<int>(c);
    }
    return xorKey % 256;
}

std::string xorEncryption(const std::string& message, const std::string& KEY) {
    std::string encryptedMessage = message;
    int xorKey = createXorKey(KEY);
    for (size_t i = 0; i < message.size(); i++) {
        encryptedMessage[i] = static_cast<char>(static_cast<int>(message[i]) ^ xorKey);
    }
    return encryptedMessage;
}

std::string xorDecryption(const std::string& message, const std::string& KEY) {
    return xorEncryption(message, KEY);
}

void printBinary(const std::string& message) {
    for (char c : message) {
        std::cout << std::bitset<8>(static_cast<unsigned char>(c)) << " ";
    }
    std::cout << std::endl;
}

void waitForInput() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Clear the screen based on operating system
    #ifdef _WIN32
        // Windows
        std::system("cls");
    #else
        // Unix/Linux/MacOS
        std::system("clear");
        // Alternative ANSI escape code if system() doesn't work
    #endif
}

void clearScreen() {
    // Clear the screen based on operating system
    #ifdef _WIN32
        // Windows
        std::system("cls");
    #else
        // Unix/Linux/MacOS
        std::system("clear");
    #endif
}

void encryptionDemonstration() {
    clearScreen();
    std::string TEST_MESSAGE = "I can't wait to play Oblivion Remastered!";
    int SHIFT = 3;
    std::string KEY = "SWORD";

    std::cout << "\nOriginal message: " << "\"" << TEST_MESSAGE << "\"" << std::endl;

    std::cout << "\nEncrypting message..." << std::endl;
    
    std::string caesarEncryptedMessage = caesarShiftEncryption(TEST_MESSAGE, SHIFT);
    std::cout << "\nCaesar encrypted: " << "\"" << caesarEncryptedMessage << "\"" << std::endl;

    std::string finalXorEncryptedMessage = xorEncryption(caesarEncryptedMessage, KEY);
    std::cout << "\nAfter XOR: " << "\"" << finalXorEncryptedMessage << "\"" << std::endl;
    waitForInput();
    clearScreen();
    std::cout << "The following screen prints the binary representation of the XOR encrypted message." << std::endl;
    waitForInput();
    clearScreen();
    std::cout << "Binary representation of XOR encrypted message: \n\n";
    printBinary(finalXorEncryptedMessage);
    waitForInput();
    clearScreen();
    std::cout << "Now we will begin the process of decrypting the message." << std::endl;
    waitForInput();
    clearScreen();

    std::cout << "Message before decryption: " << "\"" << finalXorEncryptedMessage << "\"" << std::endl;

    std::cout << "\nDecrypting message..." << std::endl;
    std::string xorDecryptedMessage = xorDecryption(finalXorEncryptedMessage, KEY);
    std::cout << "\nAfter XOR decryption: " << "\"" <<  xorDecryptedMessage << "\"" << std::endl;

    std::string finalDecryptedMessage = caesarShiftDecryption(xorDecryptedMessage, SHIFT);
    std::cout << "\nFinal decrypted message: " << "\"" <<finalDecryptedMessage << "\"" << std::endl;
    waitForInput();
    clearScreen();
}

void programIntroduction() {
    std::cout << "Welcome to the Encryption Demonstration Program!" << std::endl;
    std::cout << "This program demonstrates a simple encryption and decryption process." << std::endl;
    std::cout << "It uses Caesar Shift and XOR encryption methods." << std::endl;
    waitForInput();
    clearScreen();
    std::cout << "The program will now demonstrate the encryption and decryption process." << std::endl;
    std::cout << "\nYou will see the original message before any encryption occurs." << std::endl;
    std::cout << "\nThen, the message will be encrypted using the Caesar Shift method." << std::endl;
    std::cout << "\nNext, the encrypted message will be further encrypted using XOR encryption." << std::endl;
    waitForInput();
    clearScreen();
}

void mainMenu() {
    std::cout << "1. Replay Encryption Demonstration (Stored Message)" << std::endl;
    std::cout << "2. Enter a message to encrypt" << std::endl;
    std::cout << "3. Enter a message to decrypt" << std::endl;
    std::cout << "Please select an option: ";
    int choice;
    std:: cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    switch (choice) {
        case 1:
            encryptionDemonstration();
            break;
        case 2: {
            encryptMessage();
            break;
        }
        case 3: {
            decryptMessage();
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

std::string getMessageToEncrypt() {
    std::string message;
    std::cout << "Enter the message to encrypt: ";
    std::getline(std::cin, message);
    return message;
}



void encryptMessage() {
    std::cout << "Would you like you use your own KEY? (Y/N): " << std::endl;
    char choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    std::string KEY;
    if (choice == 'Y' || choice == 'y') {
        std::cout << "Enter your KEY: ";
        std::getline(std::cin, KEY);
        std::cout << "Your KEY is: " << KEY << std::endl;
    } else {
        std::cout << "Using default KEY: SWORD" << std::endl;
        KEY = "SWORD";
    }

    std::cout << "Would you like to use your own SHIFT? (Y/N): " << std::endl;
    char choice2;
    std::cin >> choice2;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    int SHIFT;
    if (choice2 == 'Y' || choice2 == 'y') {
        std::cout << "Enter your SHIFT: ";
        std::cin >> SHIFT;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        std::cout << "Your SHIFT is: " << SHIFT << std::endl;
    } else {
        std::cout << "Using default SHIFT: 3" << std::endl;
        SHIFT = 3;
    }

    std::string message;

    std::string messageToEncrypt = getMessageToEncrypt();
    std::cout << "\nOriginal message: " << "\"" << messageToEncrypt << "\"" << std::endl;

    std::cout << "\nEncrypting message..." << std::endl;

    std::string caesarEncryptedMessage = caesarShiftEncryption(messageToEncrypt, SHIFT);
    std::cout << "\nCaesar encrypted: " << "\"" << caesarEncryptedMessage << "\"" << std::endl;
    std::string finalXorEncryptedMessage = xorEncryption(caesarEncryptedMessage, KEY);
    std::cout << "\nAfter XOR: " << "\"" << finalXorEncryptedMessage << "\"" << std::endl;
    waitForInput();
    clearScreen();
    std::cout << "The following screen prints the binary representation of the XOR encrypted message." << std::endl;
    waitForInput();
    clearScreen();
    std::cout << "Binary representation of XOR encrypted message: \n\n";
    printBinary(finalXorEncryptedMessage);
    waitForInput();
    clearScreen();

}

void decryptMessage() {
    std::cout << "Would you like you use your own KEY? (Y/N): " << std::endl;
    char choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    std::string KEY;
    if (choice == 'Y' || choice == 'y') {
        std::cout << "Enter your KEY: ";
        std::getline(std::cin, KEY);
        std::cout << "Your KEY is: " << KEY << std::endl;
    } else {
        std::cout << "Using default KEY: SWORD" << std::endl;
        KEY = "SWORD";
    }

    std::cout << "Would you like to use your own SHIFT? (Y/N): " << std::endl;
    char choice2;
    std::cin >> choice2;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    int SHIFT; // Declare SHIFT outside the conditional block
    if (choice2 == 'Y' || choice2 == 'y') {
        std::cout << "Enter your SHIFT: ";
        std::cin >> SHIFT;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        std::cout << "Your SHIFT is: " << SHIFT << std::endl;
    } else {
        std::cout << "Using default SHIFT: 3" << std::endl;
        SHIFT = 3;
    }

    std::string message;

    std::string messageToDecrypt = getMessageToEncrypt();
    std::cout << "\nOriginal message: " << "\"" << messageToDecrypt << "\"" << std::endl;

    std::cout << "\nDecrypting message..." << std::endl;

    std::string xorDecryptedMessage = xorDecryption(messageToDecrypt, KEY);
    std::cout << "\nAfter XOR decryption: " << "\"" <<  xorDecryptedMessage << "\"" << std::endl;

    std::string finalDecryptedMessage = caesarShiftDecryption(xorDecryptedMessage, SHIFT);
    std::cout << "\nFinal decrypted message: " << "\"" <<finalDecryptedMessage << "\"" << std::endl;
}

int main() {
    programIntroduction();
    encryptionDemonstration();
    mainMenu();
    
    return 0;
}