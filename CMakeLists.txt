cmake_minimum_required(VERSION 3.19)
project(UserAndProduct_Test)

set(CMAKE_CXX_STANDARD 11)

add_executable(UserAndProduct_Test main.cpp User.h Process.h BasicOp.h Customer.h Merchant.h)