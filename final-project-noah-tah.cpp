/*
Noah Tah
4/30/2025
Programming II
Evan Vaverka
Northwestern Oklahoma State University
Assignment Description:
    Final Project
    - Make a program that encrypts and decrypts a message using a key.
    - Ask the user if they want to encrypt a message, decrypt a message, or show the stored message.
    - The user will need to know the key to decrypt the message.
    - (If using a shift cipher the user needs to know how many spaces to shift the alphabet..)
    - This means submit the key with the program.
    - The stored message will be:
        "Encryption or decryption successful"
        "This system is ready for further testing of messages"
    - If the user selects the option to show the stored message,
    after accepting the key from the user, the program should display this message in its encrypted form
    and in its decrypted form.
 */

#include <iostream>
#include <string>
#include <vector>


// Caesar Shift Encryption Function
std::string caesarShiftEncryption(const std::string& message, int SHIFT) {      // Shift value as a parameter makes this function more flexible
    std::string encryptedMessage = message;
    for (char& c : encryptedMessage) {
        if (isalpha(c)) {                                                       // Check if the character is an alphabet letter
            char base = islower(c) ? 'a' : 'A';                                 // Check if the character is lowercase or uppercase, and set the base accordingly
            c = (c - base + SHIFT) % 26 + base;                                 // Shift the character and wrap around using modulo 26 
        }
    }
    return encryptedMessage;
}

// Caesar Shift Decryption Function
std::string caesarShiftDecryption(const std::string& message, int shift) {      
    return caesarShiftEncryption(message, 26 - shift);                          // Decrypting is just shifting back by the same amount
}


// XOR Encryption Function
std::string xorEncryption(const std::string& message, const std::string& key) {


}

 int main() {
    std::string TEST_MESSAGE = "I can't wait to play Oblivion Remastered!";     // This will be used to store an example message 
    int SHIFT = 3;                                                              // This is how much we want to shift the message by
    std::string caesarEncryptedMessage = caesarShiftEncryption(TEST_MESSAGE, SHIFT);
    std::cout << "Encrypted message: " << caesarEncryptedMessage << std::endl;  // This will show the encrypted message
    std::cout << "Decrypted message: " << caesarShiftDecryption(caesarEncryptedMessage, SHIFT) << std::endl; // This will show the decrypted message

    return 0;
 }