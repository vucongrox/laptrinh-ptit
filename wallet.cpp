#include "wallet.h"
#include <fstream>
#include <sstream>

// Định nghĩa đường dẫn tệp lưu trữ thông tin ví.
const std::string Wallet::FILE_PATH = "E:/tai_lieu/c++/wallets.txt";

// Constructor, khởi tạo ví với ID và số dư ban đầu.
// Input: id (mã ví), initialBalance (số dư ban đầu).
// Output: Một đối tượng Wallet với các thuộc tính được thiết lập.
Wallet::Wallet(int id, int initialBalance) : walletId(id), balance(initialBalance) {}

// Thêm điểm vào số dư ví.
// Input: points (số điểm cần thêm).
// Output: Không có, số dư ví được cập nhật và lưu vào tệp.
void Wallet::addPoints(int points) {
    // Tăng số dư ví.
    balance += points;
    // Lưu thay đổi vào tệp wallets.txt.
    saveToFile();
}

// Trừ điểm từ số dư ví.
// Input: points (số điểm cần trừ).
// Output: Không có, số dư ví được cập nhật và lưu vào tệp.
void Wallet::deductPoints(int points) {
    // Giảm số dư ví.
    balance -= points;
    // Lưu thay đổi vào tệp wallets.txt.
    saveToFile();
}

// Lưu thông tin ví vào tệp wallets.txt.
// Input: Không có (dùng walletId và balance của đối tượng hiện tại).
// Output: true nếu lưu thành công, false nếu thất bại.
bool Wallet::saveToFile() const {
    // Mở tệp wallets.txt để đọc.
    std::ifstream inFile(FILE_PATH);
    std::stringstream buffer;
    bool found = false;

    if (inFile.is_open()) {
        std::string line;
        // Đọc từng dòng, tìm và cập nhật ví hiện tại.
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

    // Mở tệp để ghi (overwrite nếu đã tìm thấy, append nếu chưa).
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

// Tải thông tin ví từ tệp wallets.txt dựa trên walletId.
// Input: walletId (mã ví cần tải).
// Output: Con trỏ đến đối tượng Wallet nếu tìm thấy, nullptr nếu không.
Wallet* Wallet::loadFromFile(int walletId) {
    // Mở tệp wallets.txt để đọc.
    std::ifstream file(FILE_PATH);
    if (file.is_open()) {
        std::string line;
        // Đọc từng dòng, tìm ví có walletId khớp.
        while (std::getline(file, line)) {
            int id = std::stoi(line.substr(0, line.find("|")));
            if (id == walletId) {
                int balance = std::stoi(line.substr(line.find("|") + 1));
                file.close();
                // Trả về đối tượng Wallet mới với thông tin từ tệp.
                return new Wallet(walletId, balance);
            }
        }
        file.close();
    }
    return nullptr;
}

// Tìm walletId lớn nhất trong tệp wallets.txt để tạo ID mới.
// Input: Không có.
// Output: walletId lớn nhất hiện có trong tệp, hoặc 1 nếu tệp rỗng.
int Wallet::getMaxWalletId() {
    // Mở tệp wallets.txt để đọc.
    std::ifstream file(FILE_PATH);
    int maxId = 1; // Giả sử bắt đầu từ 1 nếu tệp rỗng.
    if (file.is_open()) {
        std::string line;
        // Đọc từng dòng, tìm walletId lớn nhất.
        while (std::getline(file, line)) {
            int id = std::stoi(line.substr(0, line.find("|")));
            if (id > maxId) maxId = id;
        }
        file.close();
    }
    return maxId;
}
