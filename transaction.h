#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    static const std::string FILE_PATH;

public:
    static void logTransaction(int fromId, int toId, int points, const std::string& status);
    static std::string getHistoryForUser(int userId);
};

#endif
