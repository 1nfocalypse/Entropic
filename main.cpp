#include <iostream>
#include <map>
#include <fstream>
#include <random>

/*
 *     ______      __                   _
 *    / ____/___  / /__________  ____  (_)____
 *   / __/ / __ \/ __/ ___/ __ \/ __ \/ / ___/
 *  / /___/ / / / /_/ /  / /_/ / /_/ / / /__
 * /_____/_/ /_/\__/_/   \____/ .___/_/\___/
 *                           /_/
 ***********************************************************************************************************************
 * Entropic is a means of encrypting encoded character data via a Viginere Cipher. It is largely to be used as an
 * educational toy. It is licensed under GPLv3. For more information on the license, please see the included
 * license in the directory. For more information on the cryptographic scheme, please check out the writeup I wrote
 * on mathematical cryptography at: https://github.com/1nfocalypse/CryptoWriteup?tab=readme-ov-file#vigen%C3%A8re-cipher.
 * For more information on usage, please check out the included README.
 * Have fun!
 * Project music recommendation: Hawawa - Camera Obscura (Breakcore) - https://www.youtube.com/watch?v=idqeaQyFwDE
 ***********************************************************************************************************************
 */

// forward declarations
void printMenu() noexcept;
void encryptHandler();
void decryptHandler();
std::string customKey();
std::string generatedKey();
std::string encrypt(std::string, std::string &encPath);
void save(std::string &text);

// Main Function
// PRE: NONE
// POST: Return 0 if execution succeeds, 1 if failed.
// WARNINGS: Strongly exception safe. Halts if invalid input is detected and not initially caught.
// STATUS: Completed.
int main() {
    size_t menChoice;
    size_t repeat = 1;
    do {
        printMenu();
        std::cin >> menChoice;
        while (menChoice > 3 || menChoice <= 0) {
            std::cout << "Invalid option selected.\n";
            printMenu();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> menChoice;
        }
        switch (menChoice) {
            case 1:
                encryptHandler();
                break;
            case 2:
                decryptHandler();
                break;
            case 3:
                return 0;
            default:
                std::cout << "Invalid input detected. Halting...\n";
                return 1;
        }
        std::cout << "Would you like to run Entropic again?\n";
        std::cout << "1. Yes\n";
        std::cout << "2. No\n";
        std::cin >> repeat;
        while (repeat > 2) {
            std::cout << "Invalid option selected.\n";
            std::cout << "Would you like to run Entropic again?\n";
            std::cout << "1. Yes\n";
            std::cout << "2. No\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> repeat;
        }
    } while (repeat != 2);
    return 0;
}

// encryptHandler()
// PRE: User prompts encrypt option.
// POST: Provided cleartext has been outputted as ciphertext with the key.
// WARNINGS: Strongly exception safe. Halts if invalid input is detected and not initially caught.
// STATUS: Completed.
void encryptHandler() {
    size_t encChoice;
    size_t saveChoice;
    std::cout << "Please select an option below.\n";
    std::cout << "1. Use a custom key\n";
    std::cout << "2. Use a pseudorandomly generated Vernam-like key\n";
    std::cin >> encChoice;
    while (encChoice > 2) {
        std::cout << "Invalid option selected.\n";
        std::cout << "Please select an option below.\n";
        std::cout << "1. Use a custom key\n";
        std::cout << "2. Use a pseudorandomly generated Vernam-like key\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> encChoice;
    }
    std::string ciphertext;
    switch (encChoice) {
        case 1:
            ciphertext = customKey();
            break;
        case 2:
            ciphertext = generatedKey();
            break;
        default:
            std::cout << "Invalid input detected. Halting...\n";
            exit(1);
    }
    if (ciphertext.empty()) {
        std::cout << "Encryption failed. Halting...\n";
        exit(1);
    }
    std::cout << ciphertext + "\n-------------------------------------\n";
    std::cout << "Would you like to save your ciphertext to a file?\n";
    std::cout << "1. Yes\n";
    std::cout << "2. No\n";
    std::cin >> saveChoice;
    while (saveChoice > 2) {
        std::cout << "Invalid option selected.\n";
        std::cout << "Would you like to save your ciphertext to a file?\n";
        std::cout << "1. Yes\n";
        std::cout << "2. No\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> encChoice;
    }
    if (saveChoice == 1) {
        save(ciphertext);
    }
}

// customKey()
// PRE: custom key selected by user
// POST: ciphertext encrypted with custom key returned
// WARNINGS: Strongly exception safe. May return a blank string in case of encryption failure.
// STATUS: Completed.
std::string customKey() {
    std::string key;
    std::string encPath;
    std::cout << "Please enter your key: ";
    std::cin >> key;
    std::cout << "Your key is: " + key + "\nMake sure to record your key; it is necessary for decryption.\n";
    std::cout << "Please provide the path to the encryption target (include extension): ";
    std::cin >> encPath;
    return encrypt(key, encPath);
}

// generatedKey()
// PRE: generated key selected by user
// POST: ciphertext encrypted with generated key returned
// WARNINGS: Strongly exception safe. May return a blank string in case of encryption failure.
// STATUS: Completed.
std::string generatedKey() {
    std::string key;
    std::string encPath;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(32, 126); // define the range
    std::cout << "Please provide the path to the encryption target (include extension): ";
    std::cin >> encPath;
    std::ifstream rawFile;
    rawFile.open(encPath.c_str());
    size_t inputLen = 0;
    if (rawFile.good()) {
        auto out = std::string();
        auto buf = std::string(100, '\0');
        while (rawFile.read(&buf[0], 100)) {
            out.append(buf, 0, rawFile.gcount());
        }
        out.append(buf, 0, rawFile.gcount());
        inputLen = out.length();
    }
    rawFile.close();
    for (size_t i = 0; i < inputLen; ++i) {
        key += static_cast<char>(distr(gen));
    }
    std::cout << "Your key is: " + key + "\nMake sure to record your key; it is necessary for decryption.\n";
    return encrypt(key, encPath);
}

// encrypt(std::string key, std::string &encPath)
// PRE: key selected or generated
// POST: ciphertext or blank returned
// WARNINGS: Strongly exception safe. May return a blank string in case of encryption failure.
// STATUS: Completed.
std::string encrypt(std::string key, std::string &encPath) {
    std::map<char, int> translator;
    // populate with valid ASCII characters (not magic numbers)
    for (size_t i = 32; i < 127; ++i) {
        translator.insert({static_cast<char>(i), i-32});
    }
    // open target file
    std::ifstream rawFile;
    rawFile.open(encPath.c_str());
    std::string ciphertext;
    if (rawFile.good()) {
        auto out = std::string();
        auto buf = std::string(100, '\0');
        while (rawFile.read(&buf[0], 100)) {
            out.append(buf, 0, rawFile.gcount());
        }
        out.append(buf, 0, rawFile.gcount());
        ciphertext = out;
        std::string cipherBuffer;
        for (size_t i = 0; i < out.length(); ++i) {
            char clearChar = out[i];
            size_t charVal = translator[clearChar];
            size_t keyVal = translator[key[i % key.length()]];
            size_t result_val = ((keyVal + charVal) % 96) + 32;
            cipherBuffer += static_cast<char>(result_val);
        }
        std::swap(ciphertext, cipherBuffer);
        return ciphertext;
    } else {
        std::cout << "Valid file not found.\n";
        return "";
    }
}

// decryptHandler()
// PRE: User prompts decrypt option.
// POST: Provided ciphertext has been outputted as cleartext.
// WARNINGS: Strongly exception safe. May return a blank string in case of encryption failure.
// STATUS: Completed.
void decryptHandler() {
    std::string decPath;
    std::string key;
    size_t saveChoice;
    std::map<char, int> translator;
    // populate with valid ASCII characters (not magic numbers)
    for (size_t i = 32; i < 127; ++i) {
        translator.insert({static_cast<char>(i), i-32});
    }
    std::cout << "Please provide the path to the file to decrypt: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, decPath);
    std::cout << "Please provide the decryption key: ";
    std::getline(std::cin, key);
    std::ifstream rawFile;
    rawFile.open(decPath.c_str());
    std::string cleartext;
    if (rawFile.good()) {
        auto out = std::string();
        auto buf = std::string(100, '\0');
        while (rawFile.read(&buf[0], 100)) {
            out.append(buf, 0, rawFile.gcount());
        }
        out.append(buf, 0, rawFile.gcount());
        std::string cleartextBuffer;
        for (size_t i = 0; i < out.length(); ++i) {
            int encChar = static_cast<int>(out[i]);
            encChar = encChar - 32;
            int subChar = encChar - static_cast<int>(translator[key[i % key.length()]]);
            if (subChar < 0) {
                subChar = 96 + subChar;
            }
            subChar += 32;
            cleartextBuffer += static_cast<char>(subChar);
        }
        std::swap(cleartextBuffer, cleartext);
    } else {
        std::cout << "Valid file not found.\n";
        main();
    }
    if (cleartext.empty()) {
        std::cout << "Decryption failed. Halting...\n";
        exit(1);
    }
    std::cout << cleartext + "\n-------------------------------------\n";
    std::cout << "Would you like to save your cleartext to a file?\n";
    std::cout << "1. Yes\n";
    std::cout << "2. No\n";
    std::cin >> saveChoice;
    while (saveChoice > 2) {
        std::cout << "Invalid option selected.\n";
        std::cout << "Would you like to save your cleartext to a file?\n";
        std::cout << "1. Yes\n";
        std::cout << "2. No\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> saveChoice;
    }
    if (saveChoice == 1) {
        save(cleartext);
    }
}

// save()
// PRE: User chooses to save text.
// POST: Text saved.
// WARNINGS: Basic exception safety, dependent on file availability.
// STATUS: Completed, not tested.
void save(std::string &text) {
    std::string outfilename;
    std::cout << "Please enter the name of the desired output file (with extension).\n";
    std::cin >> outfilename;
    std::ofstream outfile;
    outfile.open(outfilename);
    outfile << text;
    outfile.close();
    std::cout << "Text saved.\n";
}

// printMenu()
// PRE: None
// POST: Menu printed.
// WARNINGS: None. Nothrow guarantee.
// STATUS: Tested.
void printMenu() noexcept {
    std::cout << "     ______      __                   _\n";
    std::cout << "    / ____/___  / /__________  ____  (_)____\n";
    std::cout << "   / __/ / __ \\/ __/ ___/ __ \\/ __ \\/ / ___/\n";
    std::cout << "  / /___/ / / / /_/ /  / /_/ / /_/ / / /__\n";
    std::cout << " /_____/_/ /_/\\__/_/   \\____/ .___/_/\\___/\n";
    std::cout << "                             /_/\n";
    std::cout << "--------------------------------------------------------------------------------------\n";
    std::cout << "WARNING: Viginere Ciphers are breakable. For more information, please view the README.\n";
    std::cout << "Written by 1nfocalypse: https://github.com/1nfocalypse\n\n\n";
    std::cout << "Please select an option below.\n";
    std::cout << "1. Encrypt\n";
    std::cout << "2. Decrypt\n";
    std::cout << "3. Quit\n";
    std::cout << "---------------------------------\n";
}
