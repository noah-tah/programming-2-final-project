#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <limits>
#ifdef _WIN32
#include <cstdlib> // For system()
#endif

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

    std::cout << "Decrypting message..." << std::endl;
    
    std::cout << "\nMessage before decryption: " << "\"" << finalXorEncryptedMessage << "\"" << std::endl;

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

int main() {
    programIntroduction();

    encryptionDemonstration();
    
    return 0;
}