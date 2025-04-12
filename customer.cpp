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
bool Customer::transferPoints(const std::string& receiverUsername, int points, wxWindow* parent) {
    // 1. Tìm và mở ví A (ví của người gửi)
    Wallet* senderWallet = Wallet::loadFromFile(this->walletId);
    if (!senderWallet) {
        wxMessageBox("Khong tim thay vi cua nguoi gui!", "Loi", wxOK | wxICON_ERROR, parent);
        return false;
    }

    // 2. Tìm và mở ví B (ví của người nhận)
    int receiverWalletId = -1;
    std::ifstream userFile(User::FILE_PATH);
    if (userFile.is_open()) {
        std::string line;
        while (std::getline(userFile, line)) {
            size_t pos2 = line.find("|", line.find("|") + 1);
            size_t pos3 = line.find("|", pos2 + 1);
            std::string fileUsername = line.substr(pos2 + 1, pos3 - pos2 - 1);
            if (fileUsername == receiverUsername) {
                receiverWalletId = std::stoi(line.substr(line.rfind("|") + 1));
                break;
            }
        }
        userFile.close();
    }

    Wallet* receiverWallet = Wallet::loadFromFile(receiverWalletId);
    if (!receiverWallet) {
        wxMessageBox("Khong tim thay vi dich!", "Loi", wxOK | wxICON_ERROR, parent);
        delete senderWallet;
        return false;
    }

    // OTP xác nhận
    std::string otp = User::generateOTP();
    wxString otpMsg = wxString::Format("Ma OTP: %s\nChuyen %d diem den %s", 
                                       otp.c_str(), points, receiverUsername.c_str());
    wxMessageBox(otpMsg, "Xac Nhan OTP", wxOK | wxICON_INFORMATION, parent);

    wxTextEntryDialog dialog(parent, "Nhap ma OTP:", "Xac Nhan Giao Dich");
    if (dialog.ShowModal() != wxID_OK || dialog.GetValue().ToStdString() != otp) {
        wxMessageBox("OTP khong hop le!", "Loi", wxOK | wxICON_ERROR, parent);
        delete senderWallet;
        delete receiverWallet;
        return false;
    }

    // 3. Giao dịch atomic
    int senderBalanceBefore = senderWallet->getBalance();
    int receiverBalanceBefore = receiverWallet->getBalance();

    try {
        // 3.1 Kiểm tra và trừ điểm ví A
        if (senderWallet->getBalance() >= points) {
            senderWallet->deductPoints(points);
        } else {
            wxMessageBox("So du khong du!", "Loi", wxOK | wxICON_ERROR, parent);
            delete senderWallet;
            delete receiverWallet;
            return false;
        }

        // 3.2 Cộng điểm ví B
        receiverWallet->addPoints(points);

        // Ghi log giao dịch
        std::ofstream logFile("E:/tai_lieu/c++/transactions.txt", std::ios::app);
        if (logFile.is_open()) {
            time_t now = time(0);
            std::string timestamp = std::ctime(&now);
            timestamp.pop_back(); // Xóa ký tự xuống dòng
            logFile << this->walletId << "|" << receiverWalletId << "|" << points << "|" << timestamp << "|success\n";
            logFile.close();
        }
    } catch (const std::exception& e) {
        // Phục hồi nếu lỗi
        senderWallet->deductPoints(-points); // Hoàn lại điểm cho A
        receiverWallet->addPoints(-points);  // Hoàn lại điểm cho B
        wxMessageBox("Giao dich that bai: " + std::string(e.what()), "Loi", wxOK | wxICON_ERROR, parent);
        delete senderWallet;
        delete receiverWallet;
        return false;
    }

    // 4. Kết thúc
    delete senderWallet;
    delete receiverWallet;
    return true;
}
    }
    return ss.str();
}
