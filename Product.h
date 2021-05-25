//
// Created by Jokarc on 2021/5/25.
//

#ifndef USERANDPRODUCT_TEST_PRODUCT_H
#define USERANDPRODUCT_TEST_PRODUCT_H

class Product {
protected:
    bool isDiscount;
    int num;
    double price;
    double discount;
    string productDescription;

public:
    virtual double getPrice(){}
    bool IsDiscount() {
        return isDiscount;
    }
    string ShowProductDescription() {
        return productDescription;
    }
    int productResNum() {
        return num;
    }
};
class Book:public Product {
public:
    virtual double getPrice(){
        return price;
    }
};
class Clothes:public Product {
public:
    virtual double getPrice(){
        return price;
    }
};
class Food:public Product {
public:
    virtual double getPrice(){
        return price;
    }
};
#endif //USERANDPRODUCT_TEST_PRODUCT_H
