//
// Created by Jokarc on 2021/5/25.
//

#ifndef USERANDPRODUCT_TEST_CUSTOMER_H
#define USERANDPRODUCT_TEST_CUSTOMER_H

#include "User.h"
#include <iostream>
using std::cout;
using std::endl;

class Customer : public User {
private:

public:
    Customer(){}
    ~Customer(){}
    Customer(string a, string b) {
        UserName = a;
        PassWord = b;
        UserType = 1;
    }
    void showBalance();
    virtual void getUserType();
};

void Customer::showBalance() {
    cout << "当前账户余额：" << this -> getAccountBalance() << endl;
}

void Customer::getUserType() {
    cout << "当前用户类型：消费者" << endl;
}

#endif //USERANDPRODUCT_TEST_CUSTOMER_H
