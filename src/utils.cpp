#include<iostream>
#include <chrono>
#include <iomanip>

#include"utils.h"
using namespace std;

void func(){
    cout<<"message from utils\n";
}

void log(string message) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    cout<<std::put_time(std::localtime(&now_c), "[%Y-%m-%d %X] ")<<message<<endl;
}