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
#include <sstream>
#ifdef _WIN32
#include <cstdlib> // For system()
#endif

/*
Function prototypes to make compiler happy
*/
void encryptionDemonstration();
void programIntroduction();
void mainMenu();
void displayStoredMessage(const std::string& storedMessage);
std::string decryptMessage();
std::string getMessageToEncrypt();
std::string caesarShiftEncryption(const std::string& message, int SHIFT);
std::string caesarShiftDecryption(const std::string& message, int shift);
int createXorKey(const std::string& KEY);
std::string xorEncryption(const std::string& message, const std::string& KEY);
std::string xorDecryption(const std::string& message, const std::string& KEY);
void printBinary(const std::string& message);
void waitForInput();
void clearScreen();
std::string encryptMessage();
std::string binaryStringToBytes(const std::string& binaryString);
/*
End of function prototypes
*/

// Had to put this in global scope to make it accessible in all functions
std::string storedMessage = "I can't wait to play Oblivion Remastered!";

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
    // Normalize shift to handle large or negative values
    int normalizedShift = shift % 26;
    if (normalizedShift < 0) normalizedShift += 26;
    
    // The proper inverse shift is (26 - normalized shift) % 26
    return caesarShiftEncryption(message, (26 - normalizedShift) % 26);
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
    std::cout << "Binary representation:" << std::endl;
    for (char c : message) {
        std::cout << std::bitset<8>(static_cast<unsigned char>(c)) << " ";
    }
    std::cout << std::endl << std::endl;
    
    // Add ASCII representation for copy-pasting
    std::cout << "Copy-pastable ASCII binary sequence:" << std::endl;
    for (char c : message) {
        std::bitset<8> bits(static_cast<unsigned char>(c));
        std::string bitString = bits.to_string();
        for (char bit : bitString) {
            std::cout << bit;
        }
        std::cout << " ";
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
    std::cout << "The following screen shows both the binary representation and a copy-pastable ASCII version of the encrypted message." << std::endl;
    waitForInput();
    clearScreen();
    std::cout << "Binary and ASCII representation of XOR encrypted message: \n\n";
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
    std::cout << "Welcome to Noah Tah's Encryption and Decryption Program!" << std::endl;
    std::cout << "This program demonstrates a simple encryption and decryption process." << std::endl;
    std::cout << "It uses Caesar Shift and XOR encryption methods." << std::endl;
    waitForInput();
    clearScreen();
}

void mainMenu() {
    std::cout << "1. Play Encryption Demonstration" << std::endl;
    std::cout << "2. Enter a message to encrypt" << std::endl;
    std::cout << "3. Enter a message to decrypt" << std::endl;
    std::cout << "4. Print the stored message" << std::endl;
    std::cout << "Please select an option: ";
    int choice;
    std:: cin >> choice; 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    switch (choice) {
        case 1:
            encryptionDemonstration();
            std::cout << "Returning to the main menu..." << std::endl;
            waitForInput();
            clearScreen();
            mainMenu();
        case 2: {
            storedMessage = encryptMessage();
            std::cout << "Returning to the main menu..." << std::endl;
            waitForInput();
            clearScreen();
            mainMenu();
        }
        case 3: {
            storedMessage = decryptMessage();
            std::cout << "Returning to the main menu..." << std::endl;
            waitForInput();
            clearScreen();
            mainMenu();
        }
        case 4:
            displayStoredMessage(storedMessage);
            std::cout << "Returning to the main menu..." << std::endl;
            waitForInput();
            clearScreen();
            mainMenu();
        default:
            break;
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

void displayStoredMessage(const std::string& storedMessage) {
    std::string KEY;
    int SHIFT;

    std::cout << "In order to decrypt the stored message, you will need the same KEY and SHIFT used to encrypt it." << std::endl;

    std::cout << "\nStored message: " << "\"" << storedMessage << "\"" << std::endl;

    std::cout << "\nOn the next screen, you will be prompted to enter the KEY and SHIFT used to encrypt the message." << std::endl;
    waitForInput();
    clearScreen();

    std::cout << "Please enter the KEY used to encrypt the message: ";
    std::getline(std::cin, KEY);
    std::cout << "Please enter the SHIFT used to encrypt the message: ";
    std::cin >> SHIFT;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    std::cout << "\nDecrypting stored message..." << std::endl;

    std::string xorDecryptedMessage = xorDecryption(storedMessage, KEY);
    std::cout << "\nAfter removing XOR decryption: " << "\"" <<  xorDecryptedMessage << "\"" << std::endl;

    std::string finalDecryptedMessage = caesarShiftDecryption(xorDecryptedMessage, SHIFT);
    std::cout << "\nAfter removing Caesar encryption: " << "\"" <<finalDecryptedMessage << "\"" << std::endl;

    waitForInput();
    clearScreen();
    std::cout << "Decryption complete!" << std::endl;
    std::cout << "Press Enter to return to the main menu." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    clearScreen();
    mainMenu();

}

std::string getMessageToEncrypt() {
    std::string message;
    std::cout << "Enter the message to encrypt: ";
    std::getline(std::cin, message);
    return message;
}



std::string encryptMessage() {
    std::cout << "Would you like you use your own KEY? (Y/N): ";
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

    std::cout << "Would you like to use your own SHIFT? (Y/N): ";
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
    std::cout << "\nOn the next screen, you will be prompted to enter a message to encrypt." << std::endl;
    waitForInput();
    clearScreen();
    std::string messageToEncrypt = getMessageToEncrypt();
    std::cout << "\nOriginal message: " << "\"" << messageToEncrypt << "\"" << std::endl;

    std::cout << "\nEncrypting message..." << std::endl;

    std::string caesarEncryptedMessage = caesarShiftEncryption(messageToEncrypt, SHIFT);
    std::cout << "\nCaesar encrypted: " << "\"" << caesarEncryptedMessage << "\"" << std::endl;
    std::string finalXorEncryptedMessage = xorEncryption(caesarEncryptedMessage, KEY);
    std::cout << "\nAfter XOR: " << "\"" << finalXorEncryptedMessage << "\"" << std::endl;
    storedMessage = finalXorEncryptedMessage;
    waitForInput();
    clearScreen();
    std::cout << "The following screen shows both the binary representation and a copy-pastable ASCII version of the encrypted message." << std::endl;
    waitForInput();
    clearScreen();
    std::cout << "Binary and ASCII representation of XOR encrypted message: \n\n";
    printBinary(finalXorEncryptedMessage);
    waitForInput();
    clearScreen();

    std::cout << "The message has been encrypted successfully! " << std::endl;

    std::cout << "\nWhat would you like to do with this encrypted message?\n";
    std::cout << "1. Decrypt the message now" << std::endl;
    std::cout << "2. Store the message for later access" << std::endl;
    std::cout << "Enter your choice (1 or 2): ";
    
    char choice3;
    std::cin >> choice3;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    
    if (choice3 == '1') {
        std::cout << "\nNow we will begin the process of decrypting the message." << std::endl;
        waitForInput();
        clearScreen();
        std::cout << "Message before decryption: " << "\"" << finalXorEncryptedMessage << "\"" << std::endl;
        std::cout << "\nDecrypting message..." << std::endl;
        std::string xorDecryptedMessage = xorDecryption(finalXorEncryptedMessage, KEY);
        std::cout << "\nAfter XOR decryption: " << "\"" <<  xorDecryptedMessage << "\"" << std::endl;
        std::string finalDecryptedMessage = caesarShiftDecryption(xorDecryptedMessage, SHIFT);
        std::cout << "\nAfter Caesar decryption: " << "\"" <<finalDecryptedMessage << "\"" << std::endl;
        waitForInput();
        clearScreen();
        std::cout << "Decryption complete!" << std::endl;
    } 
    else if (choice3 == '2') {
        // Store the encrypted message along with its encryption parameters
        storedMessage = finalXorEncryptedMessage;
        std::cout << "\nThe encrypted message has been stored for later access." << std::endl;
        std::cout << "You can access it from the main menu by selecting 'Print the stored message'." << std::endl;
        std::cout << "Remember that you will need the same KEY (\"" << KEY << "\") and SHIFT (" << SHIFT << ") to decrypt it." << std::endl;
        waitForInput();
        clearScreen();
        return storedMessage;
    }
    else {
        std::cout << "Invalid choice. The encrypted message will not be stored." << std::endl;
    }
    return storedMessage;

}

std::string getMessageToDecrypt() {
    std::string message;
    std::cout << "Enter the message to decrypt: ";
    std::getline(std::cin, message);
    return message;
}

std::string decryptMessage() {
    std::string KEY;
    std::cout << "In order to decrypt the message, you will need the same KEY and SHIFT used to encrypt it." << std::endl;
    std::cout << "\nOn the next screen, you will be prompted to enter the KEY and SHIFT used to encrypt the message." << std::endl;
    waitForInput();
    clearScreen();
    std::cout << "Enter the KEY used for encrpytion: ";
    std::getline(std::cin, KEY);
    std::cout << "Using KEY: " << KEY;
    std::cout << "\nEnter the SHIFT used for encryption: ";
    int SHIFT;
    std::cin >> SHIFT;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    std::cout << "Using SHIFT: " << SHIFT << std::endl;

    std::cout << "\nOn the next screen, you will be prompted to enter a message to decrypt." << std::endl;
    std::cout << "\nYou can enter either an encrypted message or a binary representation (e.g., \"10101010 11001100\")." << std::endl;
    waitForInput();
    clearScreen();

    std::string messageToDecrypt = getMessageToDecrypt();
    std::cout << "\nOriginal message: " << "\"" << messageToDecrypt << "\"" << std::endl;

    // Check if the input appears to be binary (only 0s, 1s, and spaces)
    bool isBinary = true;
    for (char c : messageToDecrypt) {
        if (c != '0' && c != '1' && c != ' ') {
            isBinary = false;
            break;
        }
    }

    // If it's binary, convert it first
    if (isBinary) {
        messageToDecrypt = binaryStringToBytes(messageToDecrypt);
        std::cout << "\nDetected binary input, converted to binary data for decryption." << std::endl;
    }

    std::cout << "\nDecrypting message..." << std::endl;

    std::string xorDecryptedMessage = xorDecryption(messageToDecrypt, KEY);
    std::cout << "\nAfter removing XOR decryption: " << "\"" << xorDecryptedMessage << "\"" << std::endl;

    std::string finalDecryptedMessage = caesarShiftDecryption(xorDecryptedMessage, SHIFT);
    std::cout << "\nAfter removing Caesar encryption: " << "\"" << finalDecryptedMessage << "\"" << std::endl;

    waitForInput();
    clearScreen();

    return finalDecryptedMessage;
}

// Add this function to convert text binary representation to actual binary data
std::string binaryStringToBytes(const std::string& binaryString) {
    std::string result;
    std::istringstream stream(binaryString);
    std::string byteString;
    
    // Read each byte representation (separated by spaces)
    while (stream >> byteString) {
        if (byteString.length() != 8) {
            // Skip invalid binary sequences
            continue;
        }
        
        // Convert the binary string to an actual byte
        char byte = 0;
        for (char bit : byteString) {
            byte = (byte << 1) | (bit == '1' ? 1 : 0);
        }
        result += byte;
    }
    
    return result;
}

int main() {
    programIntroduction();
    mainMenu();
    
    return 0;

}

