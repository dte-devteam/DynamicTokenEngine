#include "function/include/algebra.h"
#include <iostream>
int main() {
    functions::algebra::init();
    //functions::algebra::int_add_function add;
    functions::algebra::int_addadd addadd;
    /*add.defaultvalues = {
        nullptr,
        nullptr,
        nullptr
    };*/
    addadd.defaultvalues = {
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr
    };
    addadd.callings = {
        {
            &functions::algebra::int_add,
            {
                0,
                1,
                3
            }
        },
        {
            &functions::algebra::int_add,
            {
                0,
                2,
                4
            }
        }
    };
    int a = 2, b = 8, c = 5, r1 = 0, r2 = 0;
    float fa = 20.5f, fb = 80.3f, fr = 0.1f;
    std::vector<void*> args({ &a, &b, &c, &r1, &r2 });
    addadd.execute(&args, nullptr);
    std::cout << r1 <<"&"<< r2 << std::endl;
    std::vector<void*> args2({ &b, &c, &r1, (void*)0, (void*)0, (void*)0 });
    functions::algebra::add.execute(&args2, nullptr);
    std::cout << r1 << std::endl;
    std::vector<void*> args3({ &fa, &fb, &fr, (void*)1, (void*)1, (void*)1 });
    functions::algebra::add.execute(&args3, nullptr);
    std::cout << fr << std::endl;
    return functionfactory::test();
}