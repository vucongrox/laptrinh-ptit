#include "wallet.h"
#include <fstream>
#include <sstream>

const std::string Wallet::FILE_PATH = "E:/tai_lieu/c++/wallets.txt";

Wallet::Wallet(int id, int initialBalance) : walletId(id), balance(initialBalance) {}

void Wallet::addPoints(int points) {
    balance += points;
    saveToFile();
}

void Wallet::deductPoints(int points) {
    balance -= points;
    saveToFile();
}

bool Wallet::saveToFile() const {
    std::ifstream inFile(FILE_PATH);
    std::stringstream buffer;
    bool found = false;

    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            int id = std::stoi(line.substr(0, line.find("|")));
            if (id == walletId) {
                buffer << walletId << "|" << balance << "\n";
                found = true;
            } else {
                buffer << line << "\n";
            }
        }
        inFile.close();
    }

    std::ofstream outFile(FILE_PATH, found ? std::ios::out : std::ios::app);
    if (!outFile.is_open()) return false;
    if (found) {
        outFile << buffer.str();
    } else {
        outFile << walletId << "|" << balance << "\n";
    }
    outFile.close();
    return true;
}

Wallet* Wallet::loadFromFile(int walletId) {
    std::ifstream file(FILE_PATH);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            int id = std::stoi(line.substr(0, line.find("|")));
            if (id == walletId) {
                int balance = std::stoi(line.substr(line.find("|") + 1));
                file.close();
                return new Wallet(walletId, balance);
            }
        }
        file.close();
    }
    return nullptr;
}

int Wallet::getMaxWalletId() {
    std::ifstream file(FILE_PATH);
    int maxId = 1; // Giả sử bắt đầu từ 1001
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            int id = std::stoi(line.substr(0, line.find("|")));
            if (id > maxId) maxId = id;
        }
        file.close();
    }
    return maxId;
}
