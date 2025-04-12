#ifndef MANAGER_H
#define MANAGER_H

#include "user.h"

class Manager : public User {
public:
    Manager();
    Manager(int id, const std::string& username, const std::string& password,
            const std::string& name, const std::string& dob, const std::string& address, int walletId);
    std::string getUserList();
    bool createUser(const std::string& username, const std::string& password,
                    const std::string& name, const std::string& dob, const std::string& address);
    bool updateUserInfo(int userId, const std::string& name, const std::string& dob, 
                        const std::string& address, wxWindow* parent);
    bool addPointsToUser(int userWalletId, int points); 
    std::string getTransactionHistory();
};

#endif
