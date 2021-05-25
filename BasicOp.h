//
// Created by Jokarc on 2021/5/25.
//

#ifndef USERANDPRODUCT_TEST_BASICOP_H
#define USERANDPRODUCT_TEST_BASICOP_H
#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;

class BasicOp {
public:
    BasicOp(){}
    ~BasicOp(){}
    int checkOp();
    bool checkPswd(string s);
    bool checkName(string s);
    bool checkDouble(string s);
    double Converse(string s);
    string numToStr(double num);
};
/**********************************************************
函数：checkOp
形参：string s
类型：int
作用：判断输入Op的合法
返回：合法返回相应数字，不合法返回-1
**********************************************************/
int BasicOp::checkOp() {
    string s;
    getline(cin, s);
    cout << s << endl;
    getline(cin, s);
    getline(cin, s);
    if (s.length() > 1) return -1;
    if (!isdigit(s[0])) return -1;
    return s[0]-'0';
}
/**********************************************************
函数：checkPswd
形参：string s
类型：bool
作用：判断密码字符串的合法性
返回：密码合法返回true
     密码格式：长度至少6位，不能含空格，同时拥有字母和数字
**********************************************************/
bool BasicOp::checkPswd(string s) {
    if (s.length() < 6) return 0;
    int chNum(0), digNum(0);
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') return 0;
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) chNum++;
        if (isdigit(s[i])) digNum++;
    }
    return chNum && digNum;
}
/**********************************************************
函数：checkName
形参：string s
类型：bool
作用：判断用户名字符串的合法性
返回：用户名合法返回true
     用户名格式：长度至少4位，仅能由字母和数字以及下划线‘_’构成，且必须由字母开头
**********************************************************/
bool BasicOp::checkName(string s) {
    if (s.length() < 4) return 0;
    if (!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))) return 0;
    bool flag = 1;
    for (int i = 1; i < s.length(); i++) {
        if (isdigit(s[i])) flag = 1;
        else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_') flag = 1;
        else {
            flag = 0;
            break;
        }
    }
    return flag;
}
/**********************************************************
函数：checkDouble
形参：string s
类型：bool
作用：判断一个字符串是否表示为一个浮点数
返回：表示为合法浮点数返回true
     格式要求：仅由小数点和数字构成，为充值判断函数，不支持负数充值
             至多一个小数点'.'以及小数点不能为第一位或最后一位，及小数点前后都有数字
**********************************************************/
bool BasicOp::checkDouble(string s) {
    bool flag = 1;
    bool dotflag = 0;
    if (!isdigit(s[0])) return 0;
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i]) && s[i] != '.') return 0;
        if (s[i] == '.') {
            if (!dotflag) dotflag = 1;
            else return 0;
            if (i == s.length() - 1) return 0;
        }
    }
    return flag;
}
/**********************************************************
函数：Converse
形参：string s
类型：double
作用：将字符串s转换为浮点数
返回：相应浮点数值
**********************************************************/
double BasicOp::Converse(string s) {
    double x = 0;
    int i = 0;
    for ( ; i < s.length(); i++) {
        if (s[i] == '.') break;
        x = x * 10 + s[i] - 48;
    }
    double f = 0.1;
    i++;
    for (; i < s.length(); i++){
        x += f * (s[i] - 48);
        f *= 0.1;
    }
    return x;
}
/**********************************************************
函数：numToStr
形参：double num
类型：string
作用：将double num转换为字符串形式
返回：str
**********************************************************/
string BasicOp::numToStr(double num) {
    std::stringstream stream{};
    int precision = 3;
    stream<<std::fixed<<std::setprecision(precision)<<num;
    return stream.str();
}
#endif //USERANDPRODUCT_TEST_BASICOP_H
