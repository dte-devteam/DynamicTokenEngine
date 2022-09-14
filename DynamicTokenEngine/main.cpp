#include "function/include/algebra.h"
#include <iostream>
int main() {
    functions::algebra::int_add add;
    functions::algebra::int_addadd addadd;
    add.defaultvalues = {
        nullptr,
        nullptr,
        nullptr
    };
    addadd.defaultvalues = {
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr
    };
    addadd.callings = {
        {
            &add,
            {
                0,
                1,
                3
            }
        },
        {
            &add,
            {
                0,
                2,
                4
            }
        }
    };
    add.name = 0;
    int a = 2, b = 8, c = 5, r1 = 0, r2 = 0;
    std::vector<void*> args({ &a, &b, &c, &r1, &r2 });
    addadd.execute(&args, false);
    std::cout << r1 <<"&"<< r2 << std::endl;
    return functionfactory::test();
}