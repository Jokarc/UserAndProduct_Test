//
// Created by Jokarc on 2021/5/25.
//

#ifndef USERANDPRODUCT_TEST_PROCESS_H
#define USERANDPRODUCT_TEST_PROCESS_H
#include <string>
#include "BasicOp.h"
using std::string;

class Process {
private:
    BasicOp Operation;
public:
    Process(){}
    ~Process(){}
    void PrintOpList_1(User *CurrentUser);
    void PrintOpList_2(User *CurrentUser);
    void PrintOpList_3(User *CurrentUser);
    void Register(User *CurrentUser);
    void work(User *CurrentUser, int& Logged, Customer &CurrentCustomer, Merchant &CurrentMerchant);
    int Login(User *CurrentUser, int& Logged, Customer &CurrentCustomer, Merchant &CurrentMerchant);
    int UserLogin(User *CurrentUser, string usrname, string password);
};

/**********************************************************
函数：PrintOpList_1
形参：User *CurrentUser
类型：void
作用：未登录的初始界面
返回：
**********************************************************/
void Process::PrintOpList_1(User *CurrentUser) {
    cout << "*----------------------*" << endl;
    cout << "1：我要登录" << endl;
    cout << "2：我要注册" << endl;
    cout << "3：看看商品" << endl;
    cout << "*----------------------*" << endl;
}
/**********************************************************
函数：PrintOpList_2
形参：User*CurrentUser
类型：void
作用：顾客登录后界面
返回：
**********************************************************/
void Process::PrintOpList_2(User *CurrentUser) {
    cout << "*----------------------*" << endl;
    cout << "1：退出登录" << endl;
    cout << "2：查询余额" << endl;
    cout << "3：看看商品" << endl;
    cout << "4：我叫什么" << endl;
    cout << "5：账户类型" << endl;
    cout << "6：我要充钱" << endl;
    cout << "7：修改密码" << endl;
    cout << "8：关闭程序" << endl;
    cout << "*----------------------*" << endl;
}
/**********************************************************
函数：PrintOpList_3
形参：User*CurrentUser
类型：void
作用：商家登录后界面
返回：
**********************************************************/
void Process::PrintOpList_3(User *CurrentUser) {
    cout << "*----------------------*" << endl;
    cout << "1：退出登录" << endl;
    cout << "2：查询余额" << endl;
    cout << "3：看看商品" << endl;
    cout << "4：我叫什么" << endl;
    cout << "5：账户类型" << endl;
    cout << "6：我要充钱" << endl;
    cout << "7：修改密码" << endl;
    cout << "8：关闭程序" << endl;
    cout << "9：管理商品" << endl;
    cout << "*----------------------*" << endl;
}
/**********************************************************
函数：Register
形参：User* CurrentUser
类型：void
作用：选择注册类型，输入op，用户名，密码，调用UserRegister进行注册
返回：
**********************************************************/
void Process::Register(User *CurrentUser) {
    string cus = "Customer";
    string mer = "Merchant";
    cout << "*----------------------*" << endl;
    cout << "1：注册为顾客" << endl;
    cout << "2：注册为商家" << endl;
    cout << "用户名格式要求：以字母开头，仅能由字母，数字以及下划线构成，至少4位" << endl;
    cout << "密码格式要求：同时有字母以及数字，至少6位，不能有空格" << endl;
    int op; cin >> op;
    if (op != 1 && op != 2) return ;
    cout << "请分行输入用户名及密码" << endl;
    string name, word; getchar();
    while (1) {
        getline(cin, name);
        getline(cin, word);
        if (CurrentUser->UserRegister(name, word, op == 1 ? (cus) : (mer)))
            break;
        else {
            cout << "ERROR" << endl;
        }
    }
}
/**********************************************************
函数：UserLogin
形参：User *CurrentUser，string usrname，string password
类型：int
作用：用户登录，在UserInfo.txt中寻找用户名以及相应密码，判断是否能登录
返回：0，用户名或密码不正确
     1，登录为客户
     2，登录为商家
    -1，找不到文件
**********************************************************/
int Process::UserLogin(User *CurrentUser, string usrname, string password) {
    ifstream FileIn("../Data/UserData/UserInfo.txt", ios::in);
    string temp, temp2, temp3;
    string cus = "Customer";
    string mer = "Merchant";
    bool UserNameExist = false;
    bool pswdCorrect = false;
    if (!FileIn) {
        cout << "can't find UserInfo.txt when UserLogin." << endl;
        return -1;
    }
    while (getline(FileIn, temp)) {
        getline(FileIn, temp2);
        getline(FileIn, temp3);
        if (usrname == temp){
            UserNameExist = 1;
            if (password == temp2){
                pswdCorrect = 1;
                break;
            }
        }
    }
    if (!UserNameExist || (UserNameExist && !pswdCorrect))
        cout << "UserName Or Password Error." << endl;
    if (UserNameExist && pswdCorrect) {
        cout << "Login Success." << endl;
        cout << "Your user type is " << temp3 << endl;
    }
    FileIn.close();
    if (UserNameExist && pswdCorrect && temp3 == cus) return 1;
    if (UserNameExist && pswdCorrect && temp3 == mer) return 2;
    return 0;
}
/**********************************************************
函数：Login
形参：User *CurrentUser，int &Logged，Customer &CurrentCustomer，Merchant &CurrentMerchant
类型：int
作用：输入用户名以及密码，调用UserLogin函数判断是否能登录，根据类型不同给不同对象初始化
返回：1，登录为顾客
     2，登录为商家
**********************************************************/
int Process::Login(User *CurrentUser, int& Logged, Customer &CurrentCustomer, Merchant &CurrentMerchant) {
    cout << "请分行输入用户名及密码" << endl;
    string name, word;
    User* temp = NULL;
    while (1) {
        cin >> name;
        cin >> word;
        int flag = UserLogin(CurrentUser, name, word);
        Logged = flag;
        if (flag == 1) {
            CurrentCustomer.setInfo(name,word);
            CurrentCustomer.setBalance(CurrentCustomer.findBalance());
            return 1;
        }
        if (flag == 2) {
            CurrentMerchant.setInfo(name, word);
            CurrentMerchant.setBalance(CurrentMerchant.findBalance());
            return 2;
        }
        if (Logged) break;
    }
    return 0;
}

/**********************************************************
函数：work
形参：User *CurrentUser，int &Logged，Customer &CurrentCustomer，Merchant &CurrentMerchant
类型：void
作用：维持初始界面，根据Logged值不同，打印不同界面
返回：
**********************************************************/
void Process::work(User *CurrentUser, int& Logged, Customer &CurrentCustomer, Merchant &CurrentMerchant) {
    int op = 0;
    while (1) {
        if (!Logged) {
            PrintOpList_1(CurrentUser);
            scanf ("%d", &op);
            if (op == 1) {
                int Type = Login(CurrentUser, Logged, CurrentCustomer, CurrentMerchant);
                if (Type == 1) CurrentUser = &CurrentCustomer;
                if (Type == 2) CurrentUser = &CurrentMerchant;
            }
            if (op == 2) Register(CurrentUser);
        } else {
            if (Logged == 1) PrintOpList_2(CurrentUser);
            if (Logged == 2) PrintOpList_3(CurrentUser);
            scanf ("%d", &op);
            if (op == 8) break;
            if (op == 1) CurrentUser->UserLogOut(Logged);
            if (op == 2) cout << "当前余额：" << CurrentUser -> getAccountBalance() << endl;
            if (op == 3) ;
            if (op == 4) cout << "您的用户名为：" << CurrentUser -> getUserName() << endl;
            if (op == 5) {
                if (Logged == 1) CurrentCustomer.getUserType();
                if (Logged == 2) CurrentMerchant.getUserType();
            }
            if (op == 6) {
                cout << "充值金额为浮点数，最多支持三位精度" << endl;
                cout << "请输入充值金额：" << endl;
                double val; string s;
                getchar();
                getline(cin, s);
                if (!Operation.checkDouble(s)) {
                    cout << "输入不合法" << endl;
                    continue;
                }
                val = Operation.Converse(s);
                cout << "您要充值的金额为：" << val << endl;
                CurrentUser ->UserRecharge(CurrentUser -> getAccountBalance() + val);
                cout << "充值成功" << endl;
            }
            if (op == 7) CurrentUser -> UserChangePswd();
            if (op == 9 && Logged == 2) {
                CurrentMerchant.ManageProduct();
            }
        }
    }
}

#endif //USERANDPRODUCT_TEST_PROCESS_H
