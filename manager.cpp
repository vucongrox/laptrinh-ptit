#include "manager.h"
#include <sstream>
#include "transaction.h"
#include "wallet.h"

// Constructor mặc định, khởi tạo một Manager rỗng kế thừa từ User.
// Đặt accountType là 1 (Manager) và walletId là 0 (ví tổng).
Manager::Manager() : User() { 
    accountType = 1; 
    walletId = 0; // Ví tổng hoặc ví riêng cho Manager
}

// Constructor có tham số, khởi tạo Manager với thông tin cụ thể.
// Input: id (mã người dùng), username, password, name, dob (ngày sinh), address (địa chỉ), walletId (mã ví).
// Output: Một đối tượng Manager với các thuộc tính được thiết lập.
Manager::Manager(int id, const std::string& username, const std::string& password,
                 const std::string& name, const std::string& dob, const std::string& address, int walletId)
    : User(id, 1, username, password, name, dob, address, walletId) {}

// Lấy danh sách tất cả người dùng từ tệp taikhoan.txt.
// Input: Không có.
// Output: Chuỗi chứa danh sách người dùng (mỗi dòng là một người dùng).
std::string Manager::getUserList() {
    // Mở tệp taikhoan.txt để đọc.
    std::ifstream file(FILE_PATH);
    std::stringstream ss;
    if (file.is_open()) {
        std::string line;
        // Đọc từng dòng và thêm vào chuỗi đầu ra.
        while (std::getline(file, line)) {
            ss << line << "\n";
        }
        file.close();
    }
    return ss.str();
}

// Tạo tài khoản mới cho người dùng.
// Input: username, password, name, dob (ngày sinh), address (địa chỉ).
// Output: true nếu tạo thành công, false nếu thất bại (thiếu thông tin hoặc username đã tồn tại).
bool Manager::createUser(const std::string& username, const std::string& password,
                         const std::string& name, const std::string& dob, const std::string& address) {
    // Kiểm tra dữ liệu đầu vào, trả về false nếu thiếu thông tin.
    if (username.empty() || password.empty() || name.empty() || dob.empty() || address.empty()) {
        return false;
    }

    // Gọi hàm registerAccount từ lớp cha User để tạo tài khoản.
    return User::registerAccount(username, password, name, dob, address);
}

// Cập nhật thông tin người dùng theo userId.
// Input: userId (mã người dùng), name, dob (ngày sinh), address (địa chỉ), parent (cửa sổ cha để hiển thị thông báo).
// Output: true nếu cập nhật thành công, false nếu thất bại (OTP sai, hết hạn, hoặc không tìm thấy người dùng).
bool Manager::updateUserInfo(int userId, const std::string& name, const std::string& dob, 
                             const std::string& address, wxWindow* parent) {
    // Sinh mã OTP để xác thực thao tác.
    std::string otp = generateOTP();
    time_t otpTime = getOtpGeneratedTime();
    wxString otpMsg = wxString::Format("Ma OTP: %s\nThay doi thong tin ID %d: Ten: %s, Ngay Sinh: %s, Dia Chi: %s", 
                                       otp.c_str(), userId, name.c_str(), dob.c_str(), address.c_str());
    wxMessageBox(otpMsg, "Xac Nhan OTP", wxOK | wxICON_INFORMATION, parent);

    // Yêu cầu người dùng nhập mã OTP.
    wxTextEntryDialog dialog(parent, "Nhap ma OTP:", "Xac Nhan Cap Nhat");
    if (dialog.ShowModal() != wxID_OK) {
        wxMessageBox("Huy bo thao tac!", "Thong Bao", wxOK | wxICON_INFORMATION, parent);
        return false;
    }

    std::string userOtp = dialog.GetValue().ToStdString();

    // Kiểm tra thời gian hết hạn của OTP (30 giây).
    time_t currentTime = time(nullptr);
    if (currentTime - otpTime > 30) {
        wxMessageBox("OTP da het han!", "Loi", wxOK | wxICON_ERROR, parent);
        return false;
    }

    // Kiểm tra tính hợp lệ của OTP.
    if (userOtp != otp) {
        wxMessageBox("OTP khong hop le!", "Loi", wxOK | wxICON_ERROR, parent);
        return false;
    }

    // Mở tệp taikhoan.txt để đọc và cập nhật.
    std::ifstream file(FILE_PATH);
    std::stringstream buffer;
    if (!file.is_open()) {
        wxMessageBox("Khong the mo file taikhoan.txt!", "Loi", wxOK | wxICON_ERROR, parent);
        return false;
    }

    bool found = false;
    std::string line;
    while (std::getline(file, line)) {
        try {
            // Phân tách dòng thành các trường bằng dấu "|".
            size_t pos1 = line.find("|");
            if (pos1 == std::string::npos || line.empty()) {
                buffer << line << "\n";
                continue;
            }
            int currentId = std::stoi(line.substr(0, pos1));
            if (currentId == userId) {
                // Tìm thấy người dùng, cập nhật thông tin (giữ nguyên nếu trường rỗng).
                size_t pos2 = line.find("|", pos1 + 1);
                if (pos2 == std::string::npos) continue;
                size_t pos3 = line.find("|", pos2 + 1);
                if (pos3 == std::string::npos) continue;
                size_t pos4 = line.find("|", pos3 + 1);
                if (pos4 == std::string::npos) continue;
                size_t pos5 = line.find("|", pos4 + 1);
                if (pos5 == std::string::npos) continue;
                size_t pos6 = line.find("|", pos5 + 1);
                if (pos6 == std::string::npos) continue;
                size_t pos7 = line.rfind("|");
                if (pos7 == std::string::npos) continue;
                std::string currentName = line.substr(pos4 + 1, pos5 - pos4 - 1);
                std::string currentDob = line.substr(pos5 + 1, pos6 - pos5 - 1);
                std::string currentAddress = line.substr(pos6 + 1, pos7 - pos6 - 1);
                int walletId = std::stoi(line.substr(pos7 + 1));
                buffer << userId << "|" << line.substr(pos1 + 1, pos4 - pos1 - 1) << "|" 
                       << (name.empty() ? currentName : name) << "|"
                       << (dob.empty() ? currentDob : dob) << "|" 
                       << (address.empty() ? currentAddress : address) << "|" << walletId << "\n";
                found = true;
            } else {
                buffer << line << "\n";
            }
        } catch (const std::exception& e) {
            buffer << line << "\n"; 
            continue;
        }
    }
    file.close();

    // Nếu không tìm thấy người dùng, trả về false.
    if (!found) {
        wxMessageBox("Khong tim thay nguoi dung voi ID nay!", "Loi", wxOK | wxICON_ERROR, parent);
        return false;
    }

    // Ghi lại thông tin đã cập nhật vào tệp.
    std::ofstream outFile(FILE_PATH);
    if (!outFile.is_open()) {
        wxMessageBox("Khong the ghi file taikhoan.txt!", "Loi", wxOK | wxICON_ERROR, parent);
        return false;
    }
    outFile << buffer.str();
    outFile.close();
    return true;
}

// Lấy toàn bộ lịch sử giao dịch từ transactions.txt (Manager thấy tất cả giao dịch).
// Input: Không có.
// Output: Chuỗi chứa danh sách tất cả giao dịch, mỗi dòng là một giao dịch.
std::string Manager::getTransactionHistory() {
    // Mở tệp transactions.txt để đọc.
    std::ifstream file("E:/tai_lieu/c++/transactions.txt");
    std::stringstream ss;
    if (file.is_open()) {
        std::string line;
        // Đọc từng dòng và thêm vào chuỗi đầu ra.
        while (std::getline(file, line)) {
            ss << line << "\n";
        }
        file.close();
    }
    return ss.str();
}

// Thêm điểm vào ví của người dùng từ ví tổng.
// Input: userWalletId (mã ví người dùng), points (số điểm thêm).
// Output: true nếu thêm điểm thành công, false nếu thất bại (không đủ điểm trong ví tổng, điểm âm).
bool Manager::addPointsToUser(int userWalletId, int points) {
    // Kiểm tra số điểm phải dương.
    if (points <= 0) {
        return false;
    }

    // Tải ví tổng (walletId = 0).
    Wallet* totalWallet = Wallet::loadFromFile(0);
    if (!totalWallet || totalWallet->getBalance() < points) {
        delete totalWallet;
        return false;
    }

    // Tải ví của người dùng.
    Wallet* userWallet = Wallet::loadFromFile(userWalletId);
    if (!userWallet) {
        delete totalWallet;
        return false;
    }

    try {
        // Trừ điểm từ ví tổng và thêm điểm vào ví người dùng.
        totalWallet->deductPoints(points);
        userWallet->addPoints(points);

        // Ghi lịch sử giao dịch vào transactions.txt.
        std::ofstream logFile("E:/tai_lieu/c++/transactions.txt", std::ios::app);
        if (logFile.is_open()) {
            time_t now = time(0);
            std::string timestamp = std::ctime(&now);
            timestamp.pop_back();
            logFile << 0 << "|" << userWalletId << "|" << points << "|" << timestamp << "|success\n";
            logFile.close();
        }
    } catch (const std::exception& e) {
        delete totalWallet;
        delete userWallet;
        return false;
    }

    // Giải phóng bộ nhớ và trả về kết quả.
    delete totalWallet;
    delete userWallet;
    return true;
}
