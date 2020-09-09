#include <iostream>
#include <chrono>//for clock()
#include "tester.hpp"

//#include <time.h>     // for clock()

using namespace std;

namespace {
/*
void test(int num) {

    if (b3prac::Tester(num).test())
        std::cout << "...OK" << std::endl;
    else
        std::cout << "...Failed" << std::endl;
}
*/
}



int main(int argc, char* argv[]) {//コマンドライン引数 argcはコマンドの数
    b3prac::Tester tester;
    chrono::system_clock::time_point start, end;
    start = chrono::system_clock::now();
    if (argc == 1) {
        for (int i = 0; i < 4; i++) {
            std::cout << "Test" << i << std::endl;
        }


    } else {
        tester = b3prac::Tester(argv[1][0]-'0');
    }
    end = chrono::system_clock::now();

    double time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
    printf("time %lf[ms]\n", time);
    return 0;

    
}