//
// Created by Jokarc on 2021/5/25.
//

#ifndef USERANDPRODUCT_TEST_MERCHANT_H
#define USERANDPRODUCT_TEST_MERCHANT_H

#include "User.h"

class Merchant : public User {
private:

public:
    Merchant(){}
    ~Merchant(){}
    Merchant(string a, string b) {
        UserName = a;
        PassWord = b;
        UserType = 1;
    }
    void ManageProduct();
    virtual void getUserType();
};

void Merchant::getUserType() {
    cout << "当前用户类型：商家" << endl;
}
/**********************************************************
函数：PrintOpList_ManageProduct
形参：User *CurrentUser
类型：void
作用：打印商品管理界面，支持添加商品，添加库存，进行打折活动
返回：
**********************************************************/
void Merchant::ManageProduct() {
    cout << "*----------------------*" << endl;
    cout << "1：添加商品" << endl;
    cout << "2：添加库存" << endl;
    cout << "3：商品打折" << endl;
    cout << "*----------------------*" << endl;
}
#endif //USERANDPRODUCT_TEST_MERCHANT_H
