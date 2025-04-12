#include "manager.h"
#include <sstream>
#include "transaction.h"
#include "wallet.h"

Manager::Manager() : User() { 
    accountType = 1; 
    walletId = 0; // Ví tổng hoặc ví riêng cho Manager
}

Manager::Manager(int id, const std::string& username, const std::string& password,
                 const std::string& name, const std::string& dob, const std::string& address, int walletId)
    : User(id, 1, username, password, name, dob, address, walletId) {}

std::string Manager::getUserList() {
    std::ifstream file(FILE_PATH);
    std::stringstream ss;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            ss << line << "\n";
        }
        file.close();
    }
    return ss.str();
}
