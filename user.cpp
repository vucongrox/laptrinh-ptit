#include "user.h"
#include <sstream>
#include <wx/textdlg.h>
#include <functional> 
#include <iomanip>    
#include "wallet.h"

// Định nghĩa đường dẫn tệp lưu trữ thông tin tài khoản và ví.
const std::string User::FILE_PATH = "E:/tai_lieu/c++/taikhoan.txt";
const std::string User::WALLET_FILE_PATH = "E:/tai_lieu/c++/wallets.txt";

// Constructor mặc định, khởi tạo User rỗng với các giá trị mặc định.
User::User() : id(0), accountType(0), walletId(0), otpGeneratedTime(0) {}

// Constructor có tham số, khởi tạo User với thông tin cụ thể.
// Input: id (mã người dùng), type (loại tài khoản: 0-Customer, 1-Manager), username, password, name, dob (ngày sinh), address (địa chỉ), walletId (mã ví).
// Output: Một đối tượng User với các thuộc tính được thiết lập, mật khẩu được băm.
User::User(int id, int type, const std::string& username, const std::string& password,
           const std::string& name, const std::string& dob, const std::string& address, int walletId)
    : id(id), accountType(type), username(username), hashedPassword(hashPassword(password)),
      name(name), dob(dob), address(address), walletId(walletId), otpGeneratedTime(0) {}

// Destructor mặc định.
User::~User() {}

// Tìm ID lớn nhất trong tệp taikhoan.txt để tạo ID mới.
// Input: Không có.
// Output: ID lớn nhất hiện có trong tệp, hoặc 0 nếu tệp rỗng.
int User::getMaxId() {
    // Mở tệp taikhoan.txt để đọc.
    std::ifstream file(FILE_PATH);
    int maxId = 0;
    if (file.is_open()) {
        std::string line;
        // Đọc từng dòng, lấy ID từ trường đầu tiên.
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

// Băm mật khẩu bằng hàm hash của STL.
// Input: password (mật khẩu dạng chuỗi).
// Output: Chuỗi băm của mật khẩu (định dạng hex).
std::string User::hashPassword(const std::string& password) {
    // Sử dụng std::hash để băm mật khẩu.
    std::hash<std::string> hasher;
    size_t hashValue = hasher(password);
    // Chuyển giá trị băm thành chuỗi hex.
    std::stringstream ss;
    ss << std::hex << hashValue;
    return ss.str();
}

// Kiểm tra xem username đã tồn tại trong tệp taikhoan.txt chưa.
// Input: username (tên đăng nhập cần kiểm tra).
// Output: true nếu username đã tồn tại, false nếu chưa.
bool User::isUsernameTaken(const std::string& username) {
    // Mở tệp taikhoan.txt để đọc.
    std::ifstream file(FILE_PATH);
    if (file.is_open()) {
        std::string line;
        // Đọc từng dòng, kiểm tra trường username.
        while (std::getline(file, line)) {
            try {
                size_t pos2 = line.find("|", line.find("|") + 1);
                if (pos2 == std::string::npos) continue;
                size_t pos3 = line.find("|", pos2 + 1);
                if (pos3 == std::string::npos) continue;
                std::string fileUsername = line.substr(pos2 + 1, pos3 - pos2 - 1);
                if (fileUsername == username) {
                    file.close();
                    return true;
                }
            } catch (const std::exception&) {
                continue; // Bỏ qua dòng lỗi
            }
        }
        file.close();
    }
    return false;
}

// Sinh mã OTP để xác thực thao tác.
// Input: Không có.
// Output: Chuỗi mã OTP 6 chữ số.
std::string User::generateOTP() {
    // Lưu thời gian tạo OTP để kiểm tra thời gian hết hạn.
    otpGeneratedTime = time(nullptr);
    // Gọi hàm generateTOTP từ lớp OTP (TOTP, 6 chữ số, 30 giây).
    return OTP::generateTOTP(6, 30);
}

// Xác thực đăng nhập của người dùng.
// Input: username (tên đăng nhập), password (mật khẩu).
// Output: true nếu đăng nhập thành công, false nếu thất bại.
bool User::login(const std::string& username, const std::string& password) {
    // Băm mật khẩu đầu vào để so sánh.
    std::string hashedInput = hashPassword(password);
    // Mở tệp taikhoan.txt để đọc.
    std::ifstream file(FILE_PATH);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    // Đọc từng dòng, kiểm tra username và mật khẩu băm.
    while (std::getline(file, line)) {
        try {
            size_t pos2 = line.find("|", line.find("|") + 1);
            if (pos2 == std::string::npos) continue;
            size_t pos3 = line.find("|", pos2 + 1);
            if (pos3 == std::string::npos) continue;
            size_t pos4 = line.find("|", pos3 + 1);
            if (pos4 == std::string::npos) continue;
            std::string fileUsername = line.substr(pos2 + 1, pos3 - pos2 - 1);
            std::string filePassword = line.substr(pos3 + 1, pos4 - pos3 - 1);
            if (fileUsername == username && filePassword == hashedInput) {
                // Nếu khớp, tải thông tin người dùng và trả về true.
                loadFromId(std::stoi(line.substr(0, line.find("|"))));
                file.close();
                return true;
            }
        } catch (const std::exception& e) {
            continue; // Bỏ qua dòng lỗi
        }
    }
    file.close();
    return false;
}

// Đổi mật khẩu của người dùng.
// Input: oldPassword (mật khẩu cũ), newPassword (mật khẩu mới).
// Output: true nếu đổi thành công, false nếu thất bại (mật khẩu cũ sai hoặc lỗi tệp).
bool User::changePassword(const std::string& oldPassword, const std::string& newPassword) {
    // Kiểm tra mật khẩu cũ có khớp không.
    if (hashedPassword != hashPassword(oldPassword)) {
        return false;
    }

    // Băm mật khẩu mới.
    hashedPassword = hashPassword(newPassword);
    // Mở tệp taikhoan.txt để đọc và cập nhật.
    std::ifstream file(FILE_PATH);
    std::stringstream buffer;
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    // Đọc từng dòng, cập nhật dòng của người dùng hiện tại.
    while (std::getline(file, line)) {
        try {
            if (!line.empty() && std::stoi(line.substr(0, line.find("|"))) == id) {
                buffer << id << "|" << accountType << "|" << username << "|" << hashedPassword << "|"
                       << name << "|" << dob << "|" << address << "|" << walletId << "\n";
            } else {
                buffer << line << "\n";
            }
        } catch (const std::exception&) {
            buffer << line << "\n";
        }
    }
    file.close();

    // Ghi lại tệp với mật khẩu mới.
    std::ofstream outFile(FILE_PATH);
    if (!outFile.is_open()) {
        return false;
    }
    outFile << buffer.str();
    outFile.close();
    return true;
}

// Lấy thông tin cá nhân của người dùng, bao gồm số dư ví.
// Input: Không có.
// Output: Chuỗi chứa thông tin cá nhân (ID, username, tên, ngày sinh, địa chỉ, số dư).
std::string User::getPersonalInfo() const {
    std::stringstream ss;
    int balance = 0;

    // Mở tệp wallets.txt để lấy số dư ví.
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
        balance = -1; // Báo lỗi nếu không mở được tệp
    }

    // Tạo chuỗi thông tin cá nhân.
    ss << "ID: " << id << "\n"
       << "Username: " << username << "\n"
       << "Ten: " << name << "\n"
       << "Ngay Sinh: " << dob << "\n"
       << "Dia Chi: " << address << "\n"
       << "So Du: " << balance;
    return ss.str();
}

// Lấy danh sách tất cả người dùng thông thường (Customer) từ tệp taikhoan.txt.
// Input: Không có.
// Output: Chuỗi chứa danh sách người dùng thông thường, mỗi dòng là một người dùng.
std::string User::getCustomerList() {
    // Mở tệp taikhoan.txt để đọc.
    std::ifstream file(FILE_PATH);
    std::stringstream ss;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            try {
                size_t pos1 = line.find("|");
                if (pos1 == std::string::npos) continue;
                int type = std::stoi(line.substr(pos1 + 1, line.find("|", pos1 + 1) - pos1 - 1));
                if (type == 0) { // Chỉ lấy Customer (type = 0)
                    ss << line << "\n";
                }
            } catch (const std::exception&) {
                continue; // Bỏ qua dòng lỗi
            }
        }
        file.close();
    }
    return ss.str();
}

// Đăng ký tài khoản mới cho người dùng.
// Input: username, password, name, dob (ngày sinh), address (địa chỉ).
// Output: true nếu đăng ký thành công, false nếu thất bại (username đã tồn tại, lỗi tệp).
bool User::registerAccount(const std::string& username, const std::string& password,
                           const std::string& name, const std::string& dob, const std::string& address) {
    // Kiểm tra username đã tồn tại chưa.
    if (isUsernameTaken(username)) return false;

    // Mở tệp taikhoan.txt và wallets.txt để ghi.
    std::ofstream file(FILE_PATH, std::ios::app);
    if (!file.is_open()) return false;

    std::ofstream walletFile(WALLET_FILE_PATH, std::ios::app);
    if (!walletFile.is_open()) {
        file.close();
        return false;
    }

    try {
        // Tạo ID mới và walletId cho tài khoản.
        int id = getMaxId() + 1;
        int newWalletId = id + 1000;
        std::string hashedPass = hashPassword(password);

        // Ghi thông tin tài khoản vào taikhoan.txt.
        file << id << "|0|" << username << "|" << hashedPass << "|" << name << "|" << dob << "|" << address << "|" << newWalletId << "\n";
        file.close();

        // Ghi thông tin ví vào wallets.txt với số dư ban đầu là 0.
        walletFile << newWalletId << "|0\n";
        walletFile.close();

        return true;
    } catch (const std::exception& e) {
        file.close();
        walletFile.close();
        return false;
    }
}

// Tải thông tin người dùng từ tệp taikhoan.txt dựa trên ID.
// Input: id (mã người dùng cần tải).
// Output: Cập nhật các thuộc tính của đối tượng User; nếu không tìm thấy, đặt giá trị mặc định.
void User::loadFromId(int id) {
    // Mở tệp taikhoan.txt để đọc.
    std::ifstream file(FILE_PATH);
    if (!file.is_open()) {
        // Nếu không mở được tệp, đặt giá trị mặc định.
        this->id = 0;
        this->accountType = 0;
        this->username = "";
        this->hashedPassword = "";
        this->name = "";
        this->dob = "";
        this->address = "";
        this->walletId = 0;
        return;
    }

    std::string line;
    // Đọc từng dòng, tìm dòng có ID khớp.
    while (std::getline(file, line)) {
        try {
            size_t pos1 = line.find("|");
            if (pos1 == std::string::npos || std::stoi(line.substr(0, pos1)) != id) continue;
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
            // Cập nhật thông tin người dùng.
            this->id = id;
            this->accountType = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            this->username = line.substr(pos2 + 1, pos3 - pos2 - 1);
            this->hashedPassword = line.substr(pos3 + 1, pos4 - pos3 - 1);
            this->name = line.substr(pos4 + 1, pos5 - pos4 - 1);
            this->dob = line.substr(pos5 + 1, pos6 - pos5 - 1);
            this->address = line.substr(pos6 + 1, pos7 - pos6 - 1);
            this->walletId = std::stoi(line.substr(pos7 + 1));
            break;
        } catch (const std::exception& e) {
            continue; // Bỏ qua dòng lỗi
        }
    }
    file.close();
}

// Cập nhật thông tin cá nhân của người dùng với xác thực OTP.
// Input: name, dob (ngày sinh), address (địa chỉ), parent (cửa sổ cha để hiển thị thông báo).
// Output: true nếu cập nhật thành công, false nếu thất bại (OTP sai, hết hạn, lỗi tệp).
bool User::updatePersonalInfo(const std::string& name, const std::string& dob, const std::string& address, wxWindow* parent) {
    // Sinh mã OTP để xác thực thao tác.
    std::string otp = generateOTP();
    time_t otpTime = getOtpGeneratedTime();
    wxString otpMsg = wxString::Format("Ma OTP: %s\nThay doi: Ten: %s, Ngay Sinh: %s, Dia Chi: %s",
                                       otp.c_str(), name.empty() ? this->name.c_str() : name.c_str(),
                                       dob.empty() ? this->dob.c_str() : dob.c_str(),
                                       address.empty() ? this->address.c_str() : address.c_str());
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
    // Đọc từng dòng, cập nhật thông tin người dùng hiện tại.
    while (std::getline(file, line)) {
        try {
            size_t pos1 = line.find("|");
            if (pos1 == std::string::npos || line.empty()) {
                buffer << line << "\n";
                continue;
            }
            int currentId = std::stoi(line.substr(0, pos1));
            if (currentId == id) {
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
                // Cập nhật thông tin (giữ nguyên nếu trường rỗng).
                buffer << id << "|" << line.substr(pos1 + 1, pos4 - pos1 - 1) << "|" 
                       << (name.empty() ? currentName : name) << "|"
                       << (dob.empty() ? currentDob : dob) << "|" 
                       << (address.empty() ? currentAddress : address) << "|" << walletId << "\n";
                found = true;
                // Cập nhật giá trị trong đối tượng.
                this->name = (name.empty() ? currentName : name);
                this->dob = (dob.empty() ? currentDob : dob);
                this->address = (address.empty() ? currentAddress : address);
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

// Tạo mật khẩu ngẫu nhiên (dùng để kiểm tra hoặc tạo tài khoản tạm).
// Input: Không có.
// Output: Chuỗi mật khẩu ngẫu nhiên (định dạng: "pass" + số ngẫu nhiên từ 0-9999).
std::string User::generateRandomPassword() {
    // Khởi tạo seed ngẫu nhiên dựa trên thời gian.
    std::srand(time(0));
    // Tạo mật khẩu với tiền tố "pass" và số ngẫu nhiên.
    std::string pass = "pass" + std::to_string(rand() % 10000);
    return pass;
}
