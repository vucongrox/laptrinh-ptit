#include "customer.h"
#include <sstream>
#include "transaction.h"
Customer::Customer() : User() {}

Customer::Customer(int id, const std::string& username, const std::string& password,
                   const std::string& name, const std::string& dob, const std::string& address, int points)
    : User(id, 0, username, password, name, dob, address, points) {}
bool Customer::findCustomerByUsername(const std::string& username, std::string& output) {
    std::ifstream file(FILE_PATH);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos2 = line.find("|", line.find("|") + 1);
            size_t pos3 = line.find("|", pos2 + 1);
            if (line.substr(pos2 + 1, pos3 - pos2 - 1) == username) {
                output = "ID: " + line.substr(0, line.find("|")) + "\n" +
                         "Username: " + username + "\n" +
                         "Ten: " + line.substr(pos3 + 1, line.find("|", pos3 + 1) - pos3 - 1) + "\n" +
                         "Ngay Sinh: " + line.substr(line.find("|", pos3 + 1) + 1, line.find("|", line.find("|", pos3 + 1) + 1) - line.find("|", pos3 + 1) - 1) + "\n" +
                         "Dia Chi: " + line.substr(line.rfind("|", line.rfind("|") - 1) + 1, line.rfind("|") - line.rfind("|", line.rfind("|") - 1) - 1);
                file.close();
                return true;
            }
        }
        file.close();
    }
    output = "Khong tim thay khach hang voi username nay!";
    return false;
}

std::string Customer::getTransactionHistory() const {
    std::ifstream file("E:/tai_lieu/c++/transactions.txt");
    std::stringstream ss;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos1 = line.find("|");
            int senderId = std::stoi(line.substr(0, pos1));
            size_t pos2 = line.find("|", pos1 + 1);
            int receiverId = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            size_t pos3 = line.find("|", pos2 + 1);
            int points = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            std::string timestamp = line.substr(pos3 + 1, line.find("|", pos3 + 1) - pos3 - 1);
            std::string status = line.substr(line.rfind("|") + 1);

            if (senderId == this->walletId) {
                ss << "Gui " << points << " diem den vi " << receiverId << " luc " << timestamp << " (" << status << ")\n";
            } else if (receiverId == this->walletId) {
                ss << "Nhan " << points << " diem tu vi " << senderId << " luc " << timestamp << " (" << status << ")\n";
            }
        }
        file.close();
    }
    return ss.str();
}
