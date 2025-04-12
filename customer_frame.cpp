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
bool User::isUsernameTaken(const std::string& username) {
    std::ifstream file(FILE_PATH);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos2 = line.find("|", line.find("|") + 1);
            size_t pos3 = line.find("|", pos2 + 1);
            if (line.substr(pos2 + 1, pos3 - pos2 - 1) == username) {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}
bool User::changePassword(const std::string& oldPassword, const std::string& newPassword) {
    if (hashedPassword != hashPassword(oldPassword)) {
        return false; // Mật khẩu cũ không khớp
    }

    hashedPassword = hashPassword(newPassword);
    std::ifstream file(FILE_PATH);
    std::stringstream buffer;
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && std::stoi(line.substr(0, line.find("|"))) == id) {
            buffer << id << "|" << accountType << "|" << username << "|" << hashedPassword << "|"
                   << name << "|" << dob << "|" << address << "|" << walletId << "\n";
        } else {
            buffer << line << "\n";
        }
    }
    file.close();

    std::ofstream outFile(FILE_PATH);
    if (!outFile.is_open()) {
        return false;
    }
    outFile << buffer.str();
    outFile.close();
    return true;
}

std::string User::getPersonalInfo() const {
    std::stringstream ss;
    int balance = 0;

    std::ifstream walletFile(WALLET_FILE_PATH);
    if (walletFile.is_open()) {
        std::string line;
        while (std::getline(walletFile, line)) {
            try {
                int wid = std::stoi(line.substr(0, line.find("|")));
                if (wid == walletId) {
                    balance = std::stoi(line.substr(line.find("|") + 1));
                    break;
                }
            } catch (const std::exception&) {
                continue;
            }
        }
        walletFile.close();
    } else {
        balance = -1; // Báo lỗi nếu không mở được file
    }

    ss << "ID: " << id << "\n"
       << "Username: " << username << "\n"
       << "Ten: " << name << "\n"
       << "Ngay Sinh: " << dob << "\n"
       << "Dia Chi: " << address << "\n"
       << "So Du: " << balance;
    return ss.str();
}

std::string User::getCustomerList() {
    std::ifstream file(FILE_PATH);
    std::stringstream ss;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos1 = line.find("|");
            int type = std::stoi(line.substr(pos1 + 1, line.find("|", pos1 + 1) - pos1 - 1));
            if (type == 0) { // Chỉ lấy Customer
                ss << line << "\n";
            }
        }
        file.close();
    }
    return ss.str();
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
bool User::registerAccount(const std::string& username, const std::string& password,
                           const std::string& name, const std::string& dob, const std::string& address) {
    if (isUsernameTaken(username)) return false;

    std::ofstream file(FILE_PATH, std::ios::app);
    if (!file.is_open()) return false;

    std::ofstream walletFile(WALLET_FILE_PATH, std::ios::app);
    if (!walletFile.is_open()) {
        file.close();
        return false;
    }

    try {
        int id = getMaxId() + 1;
        int newWalletId = id + 1000; // Tạo walletId duy nhất (giả sử bắt đầu từ 1001)
        std::string hashedPass = hashPassword(password);

        // Ghi thông tin tài khoản
        file << id << "|0|" << username << "|" << hashedPass << "|" << name << "|" << dob << "|" << address << "|" << newWalletId << "\n";
        file.close();

        // Ghi thông tin ví
        walletFile << newWalletId << "|0\n"; // Số dư ban đầu là 0
        walletFile.close();

        return true;
    } catch (const std::exception& e) {
        file.close();
        walletFile.close();
        return false;
    }
}
bool User::updatePersonalInfo(const std::string& name, const std::string& dob, const std::string& address, wxWindow* parent) {
    std::string otp = generateOTP();
    wxString otpMsg = wxString::Format("Ma OTP: %s\nThay doi: Ten: %s, Ngay Sinh: %s, Dia Chi: %s",
                                       otp.c_str(), name.c_str(), dob.c_str(), address.c_str());
    wxMessageBox(otpMsg, "Xac Nhan OTP", wxOK | wxICON_INFORMATION, parent);

    wxTextEntryDialog dialog(parent, "Nhap ma OTP:", "Xac Nhan Cap Nhat");
    if (dialog.ShowModal() == wxID_OK && dialog.GetValue().ToStdString() == otp) {
        this->name = name;
        this->dob = dob;
        this->address = address;

        std::ifstream file(FILE_PATH);
        std::stringstream buffer;
        if (!file.is_open()) {
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty() && std::stoi(line.substr(0, line.find("|"))) == id) {
                buffer << id << "|" << accountType << "|" << username << "|" << hashedPassword << "|"
                       << name << "|" << dob << "|" << address << "|" << walletId << "\n";
            } else {
                buffer << line << "\n";
            }
        }
        file.close();

        std::ofstream outFile(FILE_PATH);
        if (!outFile.is_open()) {
            return false;
        }
        outFile << buffer.str();
        outFile.close();
        return true;
    }
    return false;
}

std::string User::generateRandomPassword() {
    std::srand(time(0));
    std::string pass = "pass" + std::to_string(rand() % 10000);
    return pass;
}
