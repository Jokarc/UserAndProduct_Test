//
// Created by Jokarc on 2021/5/25.
//

#ifndef USERANDPRODUCT_TEST_MERCHANT_H
#define USERANDPRODUCT_TEST_MERCHANT_H
#include <fstream>
#include "User.h"
#include "Product.h"
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
    void ShowProduct();
    void ManageProduct();
    void ProductDiscount();
    void ChangeProductPrice();
    void ChangeProductInfo(char *FileName, string name, string info, int offset);
    void ShowThisKindProduct(string kind);
    void ShowThisNameProduct(string name);
    int AddNewProduct();
    int AddProductNum();
    int FindProduct(char *, string);
    virtual void getUserType();
};

void Merchant::getUserType() {
    cout << "��ǰ�û����ͣ��̼�" << endl;
}
/**********************************************************
������FindProduct
�βΣ�
���ͣ�void
���ã�Ѱ����Ʒ��//���ƣ����࣬�۸��������������ȣ�����
���أ�
**********************************************************/
int Merchant::FindProduct(char *FileName, string ProductName) {
    ifstream FileIn(FileName, ios::in);
    if (!FileIn) {
        cout << "can't find " << FileName << " when FindProduct." << endl;
        return -1;
    }
    string temp, temp2, temp3, temp4, temp5, temp6;
    getline(FileIn, temp);
    while (getline(FileIn, temp)) {
        getline(FileIn, temp2);
        getline(FileIn, temp3);
        getline(FileIn, temp4);
        getline(FileIn, temp5);
        getline(FileIn, temp6);
        if (ProductName == temp){
            return -1;//��Ʒ����
        }
    }
    FileIn.close();
    return 1;//��Ʒ������
}
/**********************************************************
������ChangeProductInfo
�βΣ�
���ͣ�void
���ã��޸���Ʒ��//���ƣ����࣬�۸��������������ȣ�����
���أ�
**********************************************************/
void Merchant::ChangeProductInfo(char *FileName, string name, string info, int offset) {
    ifstream FileIn(FileName, ios::in);
    if (!FileIn) {
        cout << "can't find " << FileName << " when ChangeProductInfo." << endl;
        return ;
    }
    int line = 2;
    int flag = 0;
    string temp, temp2, temp3, temp4, temp5, temp6;
    getline(FileIn, temp);
    while (getline(FileIn, temp)) {
        getline(FileIn, temp2);
        getline(FileIn, temp3);
        getline(FileIn, temp4);
        getline(FileIn, temp5);
        getline(FileIn, temp6);
        if (name == temp){
            flag = 1;
            Operation.ModifyLineData(FileName, line + offset, info);
        }
        line += 6;
    }
    if (!flag) cout << "Find ERROR" << endl;
    FileIn.close();
    return ;
}
/**********************************************************
������AddProduct
�βΣ�
���ͣ�void
���ã������Ʒ
���أ�
**********************************************************/
int Merchant::AddNewProduct() {
    char FileName[50] = "../Data/ProductData/";
    Operation.StrCat(FileName, getUserName());
    strcat(FileName, "_Products.txt");
    ifstream FileIn(FileName, ios::in);
    ofstream FileOut(FileName, ios::app);
    if (!FileIn) {
        cout << "can't find " << FileName << " when AddNewProduct." << endl;
        return -1;
    }
    string s;
    getline(FileIn, s);
    if (s.length() < 1 || !isdigit(s[0])) {
//        cout << "kkk" << endl;
        FileOut << 0 << endl;
    }
    double tempPrice;
    int tempNum;
    string tempDescription;
    string ProductName;
    cout << "��������Ʒ����" << endl;
    getline(cin, ProductName);
    if (FindProduct(FileName,ProductName) == -1) {
        cout << "���ĸ���Ʒ�Ѵ��ڣ������ظ����" << endl;
        return 0;
    }
    string temp;
    cout << "��������Ʒ�۸񣬸�������֧����λ����" << endl;
    getline(cin, temp);
    if (!Operation.checkDouble(temp)) {
        cout << "�밴Ҫ������" << endl;
        return 0;
    }
    tempPrice = Operation.Converse(temp);
    cout << "��������Ʒ�������Ǹ�����" << endl;
    getline(cin, temp);
    if (!Operation.checkInt(temp)) {
        cout << "�밴Ҫ������" << endl;
        return 0;
    }
    tempNum = Operation.Converse(temp);
    cout << "��������Ʒ����" << endl;
    getline(cin, temp);
    cout << "��ѡ����Ʒ����" << endl;
    cout << "1���鱾" << endl;
    cout << "2���·�" << endl;
    cout << "3��ʳƷ" << endl;
    int op = Operation.checkOp();
    if (op == -1) {
        cout << "���벻�Ϸ�" << endl;
        return 0;
    }
    tempDescription = temp;
    FileOut << ProductName << endl;
    if (op == 1) FileOut << "Book" << endl;
    if (op == 2) FileOut << "Clothes" << endl;
    if (op == 3) FileOut << "Food" << endl;
    FileOut << tempPrice << endl;
    FileOut << tempNum << endl;
    FileOut << 1 << endl;
    FileOut << tempDescription << endl;
    FileIn.close();
    ifstream FileIn2(FileName, ios::in);
    getline(FileIn2, s);
    Operation.ModifyLineData(FileName, 1, to_string(int(Operation.Converse(s) + 1)));
    FileIn2.close();
    FileOut.close();
    return 0;
}
/**********************************************************
������AddProductNum
�βΣ�
���ͣ�int
���ã������Ʒ���
���أ�����0����Ʒ�����ڣ�����-1�����ļ�
**********************************************************/
int Merchant::AddProductNum() {
    cout << "���ڵ�����Ʒ��棬������Ҫ��������Ʒ����" << endl;
    string s; getline(cin, s);
    char FileName[50] = "../Data/ProductData/";
    Operation.StrCat(FileName, getUserName());
    strcat(FileName, "_Products.txt");
    if (FindProduct(FileName, s) == 1) {
        cout << "��Ʒ�����ڣ��뷵��ѡ�������Ʒ" << endl;
        return 0;
    }
    ifstream FileIn(FileName, ios::in);
    if (!FileIn) {
        cout << "can't find " << FileName << " when AddProductNum." << endl;
        return -1;
    }
    int line = -1; bool flag = false;
    string temp, temp2, temp3, temp4, temp5, temp6;
    getline(FileIn, temp);
    while (getline(FileIn, temp)) {
        getline(FileIn, temp2);
        getline(FileIn, temp3);
        getline(FileIn, temp4);
        getline(FileIn, temp5);
        getline(FileIn, temp6);
        line += 6;
        if (s == temp){
            flag = true;
            break;
        }
    }
    if (!flag) {
        cout << "Find Error." << endl;
    } else {
        int num = Operation.Converse(temp4);
        cout << "��ǰ����Ϊ��" << num << endl;
        cout << "������������������Ϊ������������Ϊ������" << endl;
        string s;
        getline(cin, s);
        int x = Operation.checkInt(s);
        if (!x) {
            cout << "���벻�Ϸ�" << endl;
            return -1;
        }
        int op = (int)Operation.Converse(s) + num;
        if (op >= 0) {
            Operation.ModifyLineData(FileName, line, to_string(op));
            cout << "�������ɹ�������Ʒʵʱ���Ϊ��" << op << endl;
        }
        else {
            cout << "ERROR, ��治��Ϊ����" << endl;
        }
    }
    FileIn.close();
    return 1;
}
/**********************************************************
������ShowThisKindProduct
�βΣ�string kind
���ͣ�void
���ã�չʾkind����Ʒ
���أ�
**********************************************************/
void Merchant::ShowThisKindProduct(string kind) {
    char FileName[50] = "../Data/ProductData/";
    Operation.StrCat(FileName, getUserName());
    strcat(FileName, "_Products.txt");
    ifstream FileIn(FileName, ios::in);
    if (!FileIn) {
        cout << "can't find " << FileName << " when FindProduct." << endl;
        return ;
    }
    int line = -4, num = 0;
    string temp, temp2, temp3, temp4, temp5, temp6;
    getline(FileIn, temp);
    while (getline(FileIn, temp)) {
        getline(FileIn, temp2);
        getline(FileIn, temp3);
        getline(FileIn, temp4);
        getline(FileIn, temp5);
        getline(FileIn, temp6);
        line += 6;
        if (kind == temp2){
            num++;
            cout << "��Ʒ���ƣ�" << temp << endl;
            cout << "��Ʒ���ۣ�" << temp3 << endl;
            cout << "��Ʒ��棺" << temp4 << endl;
            double k = Operation.Converse(temp5);
            double newPrice = k * Operation.Converse(temp3);
            double koff = 1-k;
            cout << "�ۿ����ȣ���" << koff * 100 << "%��ʵʱ�۸�" << newPrice << endl;
            cout << "��Ʒ������" << temp6 << endl;
            cout << "*------------------------*" << endl;
        }
    }
    cout << "������" << kind << "����Ʒ" << num << "��" << endl;
    FileIn.close();
}
/**********************************************************
������ShowThisNameProduct
�βΣ�string Name
���ͣ�void
���ã�չʾ����Name��Ʒ
���أ�
**********************************************************/
void Merchant::ShowThisNameProduct(string name) {
    char FileName[50] = "../Data/ProductData/";
    Operation.StrCat(FileName, getUserName());
    strcat(FileName, "_Products.txt");
    ifstream FileIn(FileName, ios::in);
    if (!FileIn) {
        cout << "can't find " << FileName << " when FindProduct." << endl;
        return ;
    }

    int line = -4, num = 0;
    string temp, temp2, temp3, temp4, temp5, temp6;
    getline(FileIn, temp);
    while (getline(FileIn, temp)) {
        getline(FileIn, temp2);
        getline(FileIn, temp3);
        getline(FileIn, temp4);
        getline(FileIn, temp5);
        getline(FileIn, temp6);
        line += 6;
        if (name == temp){
            num++;
            cout << "��Ʒ���ƣ�" << temp << endl;
            cout << "��Ʒ���ۣ�" << temp3 << endl;
            cout << "��Ʒ��棺" << temp4 << endl;
            double k = Operation.Converse(temp5);
            double newPrice = k * Operation.Converse(temp3);
            double koff = 1-k;
            cout << "�ۿ����ȣ���" << koff * 100 << "%��ʵʱ�۸�" << newPrice << endl;
            cout << "��Ʒ������" << temp6 << endl;
            cout << "*------------------------*" << endl;
            return ;
        }
    }
    cout << "��δ�������Ϊ " << name << " ����Ʒ" << endl;
    FileIn.close();
}
/**********************************************************
������ShowProduct
�βΣ�
���ͣ�void
���ã�չʾ��Ʒ
���أ�
**********************************************************/
void Merchant::ShowProduct() {
    cout << "*----------------------*" << endl;
    cout << "1���鿴�鱾����Ʒ" << endl;
    cout << "2���鿴�·�����Ʒ" << endl;
    cout << "3���鿴ʳ������Ʒ" << endl;
    cout << "4�������Ʋ鿴��Ʒ" << endl;
    cout << "*----------------------*" << endl;
    int op = Operation.checkOp();
    if (op == -1) {
        cout << "���벻�Ϸ�" << endl;
        return ;
    }
    string book = "Book";
    string clothes = "Clothes";
    string food = "Food";
    if (op == 1) ShowThisKindProduct(book);
    if (op == 2) ShowThisKindProduct(clothes);
    if (op == 3) ShowThisKindProduct(food);
    if (op == 4) {
        string productname; //getchar();
        cout << "����Ҫ�鿴����Ʒ���ƣ�" << endl;
        getline(cin, productname);
        ShowThisNameProduct(productname);
    }
}
/**********************************************************
������ProductDiscount
�βΣ�
���ͣ�void
���ã���Ʒ����
���أ�
**********************************************************/
void Merchant::ProductDiscount() {
    cout << "���ڶ�������Ʒ���д��ۣ�������Ҫ���۵���Ʒ����(Book, Clothes, Food)" << endl;
    string s; getline(cin, s);
    char FileName[50] = "../Data/ProductData/";
    Operation.StrCat(FileName, getUserName());
    strcat(FileName, "_Products.txt");
//    if (FindProduct(FileName, s) == 1) {
//        cout << "��Ʒ�����ڣ��뷵��ѡ�������Ʒ" << endl;
//        return ;
//    }
    ifstream FileIn(FileName, ios::in);
    if (!FileIn) {
        cout << "can't find " << FileName << " when AddProductNum." << endl;
        return ;
    }
    cout << "������������ȣ�������С��1�ĸ����������������0.9���ɣ�" << endl;
    string discount;
    getline(cin, discount);
    int x = Operation.checkDouble(discount);
    if (!x) {
        cout << "���벻�Ϸ�" << endl;
        return ;
    }
    double op = Operation.Converse(discount);
    if (op > 1) {
        cout << "������С��1�ĸ�����" << endl;
        return ;
    }

    int line = -1; bool flag = false;
    string temp, temp2, temp3, temp4, temp5, temp6;
    getline(FileIn, temp);
    while (getline(FileIn, temp)) {
        getline(FileIn, temp2);
        getline(FileIn, temp3);
        getline(FileIn, temp4);
        getline(FileIn, temp5);
        getline(FileIn, temp6);
        line += 6;
        if (s == temp2){
            flag = true;
            Operation.ModifyLineData(FileName, line+1, to_string(op));
        }
    }

    if (!flag) {
        cout << "û�и�Ʒ����Ʒ��discount ERROR." << endl;
    }
    FileIn.close();
    return ;
}
/**********************************************************
������ChangeProductPrice
�βΣ�
���ͣ�void
���ã��޸���Ʒ���ۣ����ּ�
���أ�
**********************************************************/
void Merchant::ChangeProductPrice() {
    cout << "�����޸���Ʒ���ۣ�������Ҫ�޸ĵ���Ʒ����" << endl;
//    getchar();
    string s; getline(cin, s);
    cout << s << endl;
    char FileName[50] = "../Data/ProductData/";
    Operation.StrCat(FileName, getUserName());
    strcat(FileName, "_Products.txt");
    if (FindProduct(FileName, s) == 1) {
        cout << "��Ʒ�����ڣ��뷵��ѡ�������Ʒ" << endl;
        return ;
    }
    ifstream FileIn(FileName, ios::in);
    if (!FileIn) {
        cout << "can't find " << FileName << " when ChangeProductPrice." << endl;
        return ;
    }
    int line = -2; bool flag = false;
    string temp, temp2, temp3, temp4, temp5, temp6;
    getline(FileIn, temp);
    while (getline(FileIn, temp)) {
        getline(FileIn, temp2);
        getline(FileIn, temp3);
        getline(FileIn, temp4);
        getline(FileIn, temp5);
        getline(FileIn, temp6);
        line += 6;
        if (s == temp){
            flag = true;
            break;
        }
    }
    if (!flag) {
        cout << "Find Error." << endl;
    } else {
        double price = Operation.Converse(temp3);
        cout << "��ǰ����Ϊ��" << price << endl;
        cout << "�������¶���" << endl;
        string s;
        getline(cin, s);
        int x = Operation.checkDouble(s);
        if (!x) {
            cout << "���벻�Ϸ�" << endl;
            return ;
        }
        double np = Operation.Converse(s);
        if (np >= 0) {
            Operation.ModifyLineData(FileName, line, to_string(np));
            cout << "���۵����ɹ�������Ʒ�¶���Ϊ��" << np << endl;
        }
        else {
            cout << "ERROR, ���۲���Ϊ����" << endl;
        }
    }
    FileIn.close();
    return ;
}
/**********************************************************
������ManageProduct
�βΣ�
���ͣ�void
���ã���ӡ��Ʒ������棬֧�������Ʒ����ӿ�棬���д��ۻ
���أ�
**********************************************************/
void Merchant::ManageProduct() {
    cout << "*----------------------*" << endl;
    cout << "1�������Ʒ" << endl;
    cout << "2���������" << endl;
    cout << "3����Ʒ����" << endl;
    cout << "4���鿴��Ʒ" << endl;
    cout << "5���޸Ķ���" << endl;
    cout << "*----------------------*" << endl;
    int op = Operation.checkOp();
    if (op == -1) return ;
    if (op == 1) if (AddNewProduct() == -1) AddNewProduct();
    if (op == 2) AddProductNum();
    if (op == 3) ProductDiscount();
    if (op == 4) ShowProduct();
    if (op == 5) ChangeProductPrice();

}
#endif //USERANDPRODUCT_TEST_MERCHANT_H
