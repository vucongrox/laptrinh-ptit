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
bool User::login(const std::string& username, const std::string& password) {
    std::string hashedInput = hashPassword(password);
    std::ifstream file(FILE_PATH);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos2 = line.find("|", line.find("|") + 1);
            size_t pos3 = line.find("|", pos2 + 1);
            std::string fileUsername = line.substr(pos2 + 1, pos3 - pos2 - 1);
            std::string filePassword = line.substr(pos3 + 1, line.find("|", pos3 + 1) - pos3 - 1);
            if (fileUsername == username && filePassword == hashedInput) {
                loadFromId(std::stoi(line.substr(0, line.find("|"))));
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}
void User::loadFromId(int id) {
    std::ifstream file(FILE_PATH);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos1 = line.find("|");
            if (pos1 != std::string::npos && std::stoi(line.substr(0, pos1)) == id) {
                size_t pos2 = line.find("|", pos1 + 1);
                size_t pos3 = line.find("|", pos2 + 1);
                size_t pos4 = line.find("|", pos3 + 1);
                size_t pos5 = line.find("|", pos4 + 1);
                size_t pos6 = line.find("|", pos5 + 1);
                size_t pos7 = line.rfind("|");
                this->id = id;
                this->accountType = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                this->username = line.substr(pos2 + 1, pos3 - pos2 - 1);
                this->hashedPassword = line.substr(pos3 + 1, pos4 - pos3 - 1);
                this->name = line.substr(pos4 + 1, pos5 - pos4 - 1);
                this->dob = line.substr(pos5 + 1, pos6 - pos5 - 1);
                this->address = line.substr(pos6 + 1, pos7 - pos6 - 1);
                this->walletId = std::stoi(line.substr(pos7 + 1));
                break;
            }
        }
        file.close();
    }
}
