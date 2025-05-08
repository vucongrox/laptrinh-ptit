#include "customer.h"
#include <sstream>
#include "transaction.h"

// Constructor mặc định, khởi tạo một Customer rỗng kế thừa từ User.
Customer::Customer() : User() {}

// Constructor có tham số, khởi tạo Customer với thông tin cụ thể.
// Input: id (mã người dùng), username, password, name, dob (ngày sinh), address (địa chỉ), points (số điểm ban đầu).
// Output: Một đối tượng Customer với các thuộc tính được thiết lập.
Customer::Customer(int id, const std::string& username, const std::string& password,
                   const std::string& name, const std::string& dob, const std::string& address, int points)
    : User(id, 0, username, password, name, dob, address, points) {}

// Chuyển điểm từ ví của người gửi (Customer hiện tại) sang ví của người nhận.
// Input: receiverUsername (tên đăng nhập người nhận), points (số điểm chuyển), parent (cửa sổ cha để hiển thị thông báo).
// Output: true nếu chuyển điểm thành công, false nếu thất bại (ví dụ: không đủ điểm, OTP sai).
bool Customer::transferPoints(const std::string& receiverUsername, int points, wxWindow* parent) {
    // Tải ví của người gửi từ tệp wallets.txt.
    Wallet* senderWallet = Wallet::loadFromFile(this->walletId);
    if (!senderWallet) {
        wxMessageBox("Khong tim thay vi cua nguoi gui!", "Loi", wxOK | wxICON_ERROR, parent);
        return false;
    }

    // Tìm walletId của người nhận từ tệp taikhoan.txt dựa trên username.
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

    // Tải ví của người nhận từ tệp wallets.txt.
    Wallet* receiverWallet = Wallet::loadFromFile(receiverWalletId);
    if (!receiverWallet) {
        wxMessageBox("Khong tim thay vi dich!", "Loi", wxOK | wxICON_ERROR, parent);
        delete senderWallet;
        return false;
    }

    // Sinh mã OTP để xác thực giao dịch.
    std::string otp = User::generateOTP();
    time_t otpTime = getOtpGeneratedTime();
    wxString otpMsg = wxString::Format("Ma OTP: %s\nChuyen %d diem den %s", 
                                       otp.c_str(), points, receiverUsername.c_str());
    wxMessageBox(otpMsg, "Xac Nhan OTP", wxOK | wxICON_INFORMATION, parent);

    // Yêu cầu người dùng nhập mã OTP.
    wxTextEntryDialog dialog(parent, "Nhap ma OTP:", "Xac Nhan Giao Dich");
    if (dialog.ShowModal() != wxID_OK) {
        delete senderWallet;
        delete receiverWallet;
        return false;
    }

    std::string userOtp = dialog.GetValue().ToStdString();

    // Kiểm tra thời gian hết hạn của OTP (30 giây).
    time_t currentTime = time(nullptr);
    if (currentTime - otpTime > 30) {
        wxMessageBox("OTP da het han!", "Loi", wxOK | wxICON_ERROR, parent);
        delete senderWallet;
        delete receiverWallet;
        return false;
    }

    // Kiểm tra tính hợp lệ của OTP.
    if (userOtp != otp) {
        wxMessageBox("OTP khong hop le!", "Loi", wxOK | wxICON_ERROR, parent);
        delete senderWallet;
        delete receiverWallet;
        return false;
    }

    try {
        // Kiểm tra số dư ví người gửi.
        if (senderWallet->getBalance() >= points) {
            senderWallet->deductPoints(points);
        } else {
            wxMessageBox("So du khong du!", "Loi", wxOK | wxICON_ERROR, parent);
            delete senderWallet;
            delete receiverWallet;
            return false;
        }

        // Thêm điểm vào ví người nhận.
        receiverWallet->addPoints(points);

        // Ghi lịch sử giao dịch vào transactions.txt.
        std::ofstream logFile("E:/tai_lieu/c++/transactions.txt", std::ios::app);
        if (logFile.is_open()) {
            time_t now = time(0);
            std::string timestamp = std::ctime(&now);
            timestamp.pop_back();
            logFile << this->walletId << "|" << receiverWalletId << "|" << points << "|" << timestamp << "|success\n";
            logFile.close();
        }
    } catch (const std::exception& e) {
        // Nếu có lỗi, hoàn tác giao dịch.
        senderWallet->deductPoints(-points);
        receiverWallet->addPoints(-points);
        wxMessageBox("Giao dich that bai: " + std::string(e.what()), "Loi", wxOK | wxICON_ERROR, parent);
        delete senderWallet;
        delete receiverWallet;
        return false;
    }

    // Giải phóng bộ nhớ và trả về kết quả thành công.
    delete senderWallet;
    delete receiverWallet;
    return true;
}

// Tìm thông tin khách hàng dựa trên tên đăng nhập.
// Input: username (tên đăng nhập cần tìm), output (chuỗi lưu thông tin khách hàng).
// Output: true nếu tìm thấy, false nếu không; chuỗi output chứa thông tin khách hàng hoặc thông báo lỗi.
bool Customer::findCustomerByUsername(const std::string& username, std::string& output) {
    // Mở tệp taikhoan.txt để đọc thông tin người dùng.
    std::ifstream file(FILE_PATH);
    if (!file.is_open()) {
        output = "Khong the mo file taikhoan.txt!";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        try {
            // Phân tách dòng thành các trường bằng dấu "|".
            size_t pos1 = line.find("|");
            if (pos1 == std::string::npos) continue;
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

            // Kiểm tra username trong dòng hiện tại.
            std::string fileUsername = line.substr(pos2 + 1, pos3 - pos2 - 1);
            if (fileUsername == username) {
                // Trích xuất thông tin khách hàng.
                std::string id = line.substr(0, pos1);
                std::string name = line.substr(pos4 + 1, pos5 - pos4 - 1);
                std::string dob = line.substr(pos5 + 1, pos6 - pos5 - 1);
                std::string address = line.substr(pos6 + 1, pos7 - pos6 - 1);
                int walletId = std::stoi(line.substr(pos7 + 1));

                // Tạo chuỗi output chứa thông tin khách hàng.
                output = "ID: " + id + "\n" +
                         "Username: " + username + "\n" +
                         "Ten: " + name + "\n" +
                         "Ngay Sinh: " + dob + "\n" +
                         "Dia Chi: " + address + "\n";
                file.close();
                return true;
            }
        } catch (const std::exception& e) {
            continue; // Bỏ qua dòng lỗi
        }
    }
    file.close();
    output = "Khong tim thay khach hang voi username nay!";
    return false;
}

// Lấy lịch sử giao dịch của Customer hiện tại từ transactions.txt.
// Input: Không có (dùng walletId của Customer hiện tại).
// Output: Chuỗi chứa danh sách giao dịch (gửi và nhận) hoặc thông báo nếu không có giao dịch.
std::string Customer::getTransactionHistory() const {
    // Mở tệp transactions.txt để đọc lịch sử giao dịch.
    std::ifstream file("E:/tai_lieu/c++/transactions.txt");
    std::stringstream ss;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Phân tách dòng giao dịch bằng dấu "|".
            size_t pos1 = line.find("|");
            int senderId = std::stoi(line.substr(0, pos1));
            size_t pos2 = line.find("|", pos1 + 1);
            int receiverId = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            size_t pos3 = line.find("|", pos2 + 1);
            int points = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            std::string timestamp = line.substr(pos3 + 1, line.find("|", pos3 + 1) - pos3 - 1);
            std::string status = line.substr(line.rfind("|") + 1);

            // Kiểm tra nếu giao dịch liên quan đến ví của Customer hiện tại.
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
