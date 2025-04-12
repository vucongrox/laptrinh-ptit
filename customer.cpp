#include "customer.h"
#include <sstream>
#include "transaction.h"
Customer::Customer() : User() {}

Customer::Customer(int id, const std::string& username, const std::string& password,
                   const std::string& name, const std::string& dob, const std::string& address, int points)
    : User(id, 0, username, password, name, dob, address, points) {}
