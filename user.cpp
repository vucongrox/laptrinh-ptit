#include "user.h"
#include <sstream>
#include <wx/textdlg.h>
#include <functional> 
#include <iomanip>    
#include "wallet.h"

const std::string User::FILE_PATH = "E:/tai_lieu/c++/taikhoan.txt";
const std::string User::WALLET_FILE_PATH = "E:/tai_lieu/c++/wallets.txt";

User::User() : id(0), accountType(0), walletId(0) {}
User::User(int id, int type, const std::string& username, const std::string& password,
           const std::string& name, const std::string& dob, const std::string& address, int walletId)
    : id(id), accountType(type), username(username), hashedPassword(hashPassword(password)),
      name(name), dob(dob), address(address), walletId(walletId) {}

User::~User() {
}

int User::getMaxId() {
    std::ifstream file(FILE_PATH);
    int maxId = 0;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            try {
                if (!line.empty()) {
                    int id = std::stoi(line.substr(0, line.find("|")));
                    if (id > maxId) maxId = id;
                }
            } catch (const std::exception&) {
                continue; // Bỏ qua dòng lỗi
            }
        }
        file.close();
    }
    return maxId;
}

std::string User::hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    size_t hashValue = hasher(password);
    std::stringstream ss;
    ss << std::hex << hashValue;
    return ss.str();
}
