#include "main.h"
#include "login_frame.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <algorithm>
#include <direct.h> // Để tạo thư mục trên Windows

// Hàm kiểm tra thư mục tồn tại (thay thế std::filesystem)
bool directoryExists(const std::string& path) {
    struct stat info;
    return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
}

// Hàm tạo thư mục (thay thế std::filesystem)
void createDirectory(const std::string& path) {
    _mkdir(path.c_str());
}

// Hàm xóa tệp (thay thế std::filesystem::remove)
void removeFile(const std::string& path) {
    remove(path.c_str());
}

// Hàm sao lưu toàn cục với log chi tiết
void backupFiles(const std::string& backupDir) {
    time_t now = std::time(nullptr);
    std::cout << "Starting backup at " << std::ctime(&now);

    // Kiểm tra và tạo thư mục sao lưu nếu chưa tồn tại
    if (!directoryExists(backupDir)) {
        std::cout << "Creating backup directory: " << backupDir << std::endl;
        createDirectory(backupDir);
    }

    std::string timestamp = std::to_string(now);
    std::vector<std::string> files = {
        "E:/tai_lieu/c++/taikhoan.txt",
        "E:/tai_lieu/c++/transactions.txt",
        "E:/tai_lieu/c++/wallets.txt"
    };
    std::vector<std::string> fileNames = {"taikhoan", "transactions", "wallets"};

    for (size_t i = 0; i < files.size(); ++i) {
        std::string backupPath = backupDir + "/" + fileNames[i] + "_backup_" + timestamp + ".txt";
        std::ifstream src(files[i], std::ios::binary);
        std::ofstream dst(backupPath, std::ios::binary);
        if (!src.is_open()) {
            std::cerr << "Failed to open source file: " << files[i] << std::endl;
            continue;
        }
        if (!dst.is_open()) {
            std::cerr << "Failed to create backup file: " << backupPath << std::endl;
            src.close();
            continue;
        }
        dst << src.rdbuf();
        src.close();
        dst.close();
        std::cout << "Created backup: " << backupPath << std::endl;
    }

    // Giữ tối đa 7 bản sao gần nhất cho mỗi loại tệp
    for (const auto& fileName : fileNames) {
        std::vector<std::string> backups;
        std::ifstream dirList(backupDir); // Không dùng std::filesystem
        std::string dirEntry;
        while (std::getline(dirList, dirEntry)) {
            if (dirEntry.find(fileName + "_backup_") != std::string::npos) {
                backups.push_back(dirEntry);
            }
        }
        dirList.close();
        std::sort(backups.begin(), backups.end(), std::greater<std::string>());
        for (size_t i = 7; i < backups.size(); ++i) {
            removeFile(backups[i]);
            std::cout << "Removed old backup: " << backups[i] << std::endl;
        }
    }
}

bool MyApp::OnInit() {
    // Gọi sao lưu ngay khi khởi động để kiểm tra
    std::cout << "Initial backup at startup" << std::endl;
    backupFiles("E:/tai_lieu/c++/backups");

    // Khởi động sao lưu định kỳ trong một luồng riêng
    std::thread backupThread([]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::minutes(1)); // Giảm xuống 1 phút để kiểm tra nhanh
            time_t now = std::time(nullptr);
            std::cout << "Scheduled backup triggered at " << std::ctime(&now);
            backupFiles("E:/tai_lieu/c++/backups");
        }
    });
    backupThread.detach(); // Chạy luồng nền

    LoginFrame* frame = new LoginFrame("Dang Nhap");
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
