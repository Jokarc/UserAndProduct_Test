//
// Created by Jokarc on 2021/5/25.
//

#ifndef USERANDPRODUCT_TEST_MERCHANT_H
#define USERANDPRODUCT_TEST_MERCHANT_H
#include <fstream>
#include "User.h"
using std::ifstream;
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
    void AddNewProduct();
    int FindProduct(char *, string);
    virtual void getUserType();
};

void Merchant::getUserType() {
    cout << "当前用户类型：商家" << endl;
}
/**********************************************************
函数：FindProduct
形参：
类型：void
作用：寻找商品，//名称，价格，数量，打折力度，描述
返回：
**********************************************************/
int Merchant::FindProduct(char *FileName, string ProductName) {
    ifstream FileIn(FileName, ios::in);
    if (!FileIn) {
        cout << "can't find " << FileName << " when FindProduct." << endl;
        return -1;
    }
    string temp, temp2, temp3, temp4, temp5;
    while (getline(FileIn, temp)) {
        getline(FileIn, temp2);
        getline(FileIn, temp3);
        getline(FileIn, temp4);
        getline(FileIn, temp5);
        if (ProductName == temp){
            cout << "您的该商品已存在，请勿重复添加" << endl;
            return -1;
        }
    }
    FileIn.close();
    return 1;
}
/**********************************************************
函数：AddProduct
形参：
类型：void
作用：添加商品
返回：
**********************************************************/
void Merchant::AddNewProduct() {
    char FileName[50] = "../Data/ProductData/";
    Operation.StrCat(FileName, getUserName());
    strcat(FileName, ".txt");
    ifstream FileIn(FileName, ios::in);
    ofstream FileOut(FileName, ios::app);
    bool ProductNameExist = false;
    if (!FileIn) {
        cout << "can't find " << FileName << " when FindProduct." << endl;
        return ;
    }
    double tempPrice;
    int tempNum;
    string tempDescription;
    string ProductName;
    getline(cin, ProductName);
    if (FindProduct(FileName,ProductName) == -1)
        return ;
    string temp;
    cout << "请输入商品价格，浮点数，支持三位精度" << endl;
    getline(cin, temp);
    if (!Operation.checkDouble(temp)) {
        cout << "请按要求输入" << endl;
        return ;
    }
    tempPrice = Operation.Converse(temp);
    cout << "请输入商品数量，非负整数" << endl;
    getline(cin, temp);
    if (!Operation.checkInt(temp)) {
        cout << "请按要求输入" << endl;
        return ;
    }
    tempNum = Operation.Converse(temp);
    cout << "请输入商品描述" << endl;
    getline(cin, temp);
    tempDescription = temp;
    FileOut << ProductName << endl;
    FileOut << tempPrice << endl;
    FileOut << tempNum << endl;
    FileOut << 1 << endl;
    FileOut << tempDescription << endl;
    FileIn.close();
    FileOut.close();
}
/**********************************************************
函数：ManageProduct
形参：
类型：void
作用：打印商品管理界面，支持添加商品，添加库存，进行打折活动
返回：
**********************************************************/
void Merchant::ManageProduct() {
    cout << "*----------------------*" << endl;
    cout << "1：添加商品" << endl;
    cout << "2：添加库存" << endl;
    cout << "3：商品打折" << endl;
    cout << "4：查看商品" << endl;
    cout << "*----------------------*" << endl;
    int op = Operation.checkOp();
    if (op == -1) return ;
    if (op == 1) AddNewProduct();
}
#endif //USERANDPRODUCT_TEST_MERCHANT_H
