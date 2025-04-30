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

class MessageObject {
private:
    std::string message1;
    std::string message2;

public:
    // Constructor to initialize the messages
    MessageObject() 
        : message1("Encryption or decryption successful"), 
          message2("This system is ready for further testing of messages") {}

    // Method to get the first message
    std::string getMessage1() const {
        return message1;
    }

    // Method to get the second message
    std::string getMessage2() const {
        return message2;
    }

    // Method to display both messages
    void displayMessages() const {
        std::cout << "Message 1: " << message1 << std::endl;
        std::cout << "Message 2: " << message2 << std::endl;
    }
};

int main() {
    // Create an instance of MessageObject
    MessageObject messages;

    // Display the stored messages
    messages.displayMessages();

    return 0;
}