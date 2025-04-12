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
bool Manager::createUser(const std::string& username, const std::string& password,
                         const std::string& name, const std::string& dob, const std::string& address) {
    return User::registerAccount(username, password, name, dob, address);
}

bool Manager::updateUserInfo(int userId, const std::string& name, const std::string& dob, 
                             const std::string& address, wxWindow* parent) {
    std::string otp = generateOTP();
    wxString otpMsg = wxString::Format("Ma OTP: %s\nThay doi thong tin ID %d: Ngay Sinh: %s, Dia Chi: %s", 
                                       otp.c_str(), userId, dob.c_str(), address.c_str());
    wxMessageBox(otpMsg, "Xac Nhan OTP", wxOK | wxICON_INFORMATION, parent);

    wxTextEntryDialog dialog(parent, "Nhap ma OTP:", "Xac Nhan Cap Nhat");
    if (dialog.ShowModal() != wxID_OK || dialog.GetValue().ToStdString() != otp) {
        wxMessageBox("OTP khong hop le!", "Loi", wxOK | wxICON_ERROR, parent);
        return false;
    }

    std::ifstream file(FILE_PATH);
    std::stringstream buffer;
    if (!file.is_open()) {
        wxMessageBox("Khong the mo file taikhoan.txt!", "Loi", wxOK | wxICON_ERROR, parent);
        return false;
    }

    bool found = false;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && std::stoi(line.substr(0, line.find("|"))) == userId) {
            size_t pos1 = line.find("|");
            size_t pos2 = line.find("|", pos1 + 1);
            size_t pos3 = line.find("|", pos2 + 1);
            size_t pos4 = line.find("|", pos3 + 1);
            size_t pos5 = line.find("|", pos4 + 1);
            size_t pos6 = line.find("|", pos5 + 1);
            int walletId = std::stoi(line.substr(line.rfind("|") + 1));
            std::string currentDob = line.substr(pos5 + 1, pos6 - pos5 - 1);
            std::string currentAddress = line.substr(pos6 + 1, line.rfind("|") - pos6 - 1);
            buffer << userId << "|" << line.substr(pos1 + 1, pos3 - pos1 - 1) << "|" 
                   << (dob.empty() ? currentDob : dob) << "|" 
                   << (address.empty() ? currentAddress : address) << "|" << walletId << "\n";
            found = true;
        } else {
            buffer << line << "\n";
        }
    }
    file.close();

    if (!found) {
        wxMessageBox("Khong tim thay nguoi dung voi ID nay!", "Loi", wxOK | wxICON_ERROR, parent);
        return false;
    }

    std::ofstream outFile(FILE_PATH);
    if (!outFile.is_open()) {
        wxMessageBox("Khong the ghi file taikhoan.txt!", "Loi", wxOK | wxICON_ERROR, parent);
        return false;
    }
    outFile << buffer.str();
    outFile.close();
    return true;
}

std::string Manager::getTransactionHistory() {
    std::ifstream file("E:/tai_lieu/c++/transactions.txt");
    std::stringstream ss;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            ss << line << "\n"; // Manager thấy tất cả giao dịch
        }
        file.close();
    }
    return ss.str();
}
