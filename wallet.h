#ifndef WALLET_H
#define WALLET_H

#include <string>

class Wallet {
private:
    int walletId;
    int balance;
    static const std::string FILE_PATH; // "wallets.txt"

public:
    Wallet(int id, int initialBalance = 0);
    int getBalance() const { return balance; }
    void addPoints(int points);
    void deductPoints(int points);
    bool saveToFile() const;
    static Wallet* loadFromFile(int walletId);
    static int getMaxWalletId();
};

#endif
