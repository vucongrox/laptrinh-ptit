#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include "transaction.h"

class Customer : public User {
public:
    Customer();
    Customer(int id, const std::string& username, const std::string& password,
             const std::string& name, const std::string& dob, const std::string& address, int points = 0);
    bool transferPoints(const std::string& receiverUsername, int points, wxWindow* parent); // Sửa tham số
    bool findCustomerByUsername(const std::string& username, std::string& output);
    std::string getTransactionHistory() const;
};

#endif
