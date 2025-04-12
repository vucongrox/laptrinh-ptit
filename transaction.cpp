#include "transaction.h"
#include <fstream>
#include <sstream>
#include <ctime>

const std::string Transaction::FILE_PATH = "E:/tai_lieu/c++/transactions.txt";

void Transaction::logTransaction(int fromId, int toId, int points, const std::string& status) {
    std::ofstream file(FILE_PATH, std::ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        std::string timestamp = ctime(&now);
        timestamp.pop_back(); 
        static int transactionId = 0;
        file << ++transactionId << "|" << fromId << "|" << toId << "|" << points << "|" << timestamp << "|" << status << "\n";
        file.close();
    }
}

std::string Transaction::getHistoryForUser(int userId) {
    std::ifstream file(FILE_PATH);
    std::stringstream ss;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos1 = line.find("|");
            size_t pos2 = line.find("|", pos1 + 1);
            int fromId = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            size_t pos3 = line.find("|", pos2 + 1);
            int toId = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            if (fromId == userId || toId == userId) {
                ss << line << "\n";
            }
        }
        file.close();
    }
    return ss.str();
}
