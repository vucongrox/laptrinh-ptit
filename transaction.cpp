#include "transaction.h"
#include <fstream>
#include <sstream>
#include <ctime>

// Định nghĩa đường dẫn tệp lưu trữ lịch sử giao dịch.
const std::string Transaction::FILE_PATH = "E:/tai_lieu/c++/transactions.txt";

// Ghi log giao dịch vào tệp transactions.txt.
// Input: fromId (ID ví gửi), toId (ID ví nhận), points (số điểm), status (trạng thái giao dịch).
// Output: Không có, giao dịch được ghi vào tệp.
void Transaction::logTransaction(int fromId, int toId, int points, const std::string& status) {
    // Mở tệp transactions.txt để ghi (chế độ append).
    std::ofstream file(FILE_PATH, std::ios::app);
    if (file.is_open()) {
        // Lấy thời gian hiện tại và định dạng timestamp.
        time_t now = time(0);
        std::string timestamp = ctime(&now);
        timestamp.pop_back(); // Xóa ký tự xuống dòng ở cuối.
        // Tạo transactionId tăng dần (static để giữ giá trị giữa các lần gọi).
        static int transactionId = 0;
        // Ghi thông tin giao dịch vào tệp.
        file << ++transactionId << "|" << fromId << "|" << toId << "|" << points << "|" << timestamp << "|" << status << "\n";
        file.close();
    }
}

// Lấy lịch sử giao dịch của một người dùng từ transactions.txt.
// Input: userId (ID ví của người dùng cần lấy lịch sử).
// Output: Chuỗi chứa các giao dịch liên quan đến userId, mỗi dòng là một giao dịch.
std::string Transaction::getHistoryForUser(int userId) {
    // Mở tệp transactions.txt để đọc.
    std::ifstream file(FILE_PATH);
    std::stringstream ss;
    if (file.is_open()) {
        std::string line;
        // Đọc từng dòng trong tệp.
        while (std::getline(file, line)) {
            // Phân tách dòng để lấy fromId và toId.
            size_t pos1 = line.find("|");
            size_t pos2 = line.find("|", pos1 + 1);
            int fromId = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            size_t pos3 = line.find("|", pos2 + 1);
            int toId = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            // Kiểm tra nếu giao dịch liên quan đến userId (gửi hoặc nhận).
            if (fromId == userId || toId == userId) {
                ss << line << "\n";
            }
        }
        file.close();
    }
    return ss.str();
}
