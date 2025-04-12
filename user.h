#ifndef USER_H
#define USER_H

#include <wx/wx.h>
#include <string>
#include <fstream>
#include <ctime>
#include "wallet.h"

class User {
protected:
    static const std::string FILE_PATH; // "taikhoan.txt"
    static const std::string WALLET_FILE_PATH; // "wallets.txt"
    int id;
    int accountType; // 0: Customer, 1: Manager
    std::string username;
    std::string hashedPassword;
    std::string name;
    std::string dob;
    std::string address;
	int walletId; 

    static int getMaxId();
    static std::string hashPassword(const std::string& password);
    static bool isUsernameTaken(const std::string& username);
    static std::string generateOTP();

public:
    User();
    User(int id, int type, const std::string& username, const std::string& password,
         const std::string& name, const std::string& dob, const std::string& address, int points = 0);
    virtual ~User(); 
    
    bool login(const std::string& username, const std::string& password);
    bool changePassword(const std::string& oldPassword, const std::string& newPassword);
    std::string getPersonalInfo() const;
    static std::string getCustomerList();
    static bool registerAccount(const std::string& username, const std::string& password,
                              const std::string& name, const std::string& dob, const std::string& address);
    void loadFromId(int id);
    bool updatePersonalInfo(const std::string& name, const std::string& dob, const std::string& address, wxWindow* parent);
    int getId() const { return id; }
    int getAccountType() const { return accountType; }
	int getWalletId() const { return walletId; }
    static std::string generateRandomPassword();
};

#endif
