#include <iostream>

#include "utils/include/hash.h"
#include "memory/include/function.h"

#include "tests.h"

#define ALGEBRA_EXPORTS
#include "add.h"

#include <chrono>
#include <thread>


typedef int(*DLLPROC)();
DLLPROC dllf = nullptr;

struct int_addadd : function { using function::function; };
struct add_funtion : muxfunction { using muxfunction::muxfunction; };
struct setter : basicfunction { //temp
    using basicfunction::basicfunction;
    void __fastcall execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced) {
        *(size_t*)(*argumentspointer)[1] = (size_t)(*argumentspointer)[0];
    }
};
std::chrono::milliseconds timespan(5000);


int main() {
    int_addadd addadd {
        0,  //name
        {   //defaultvalues
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr
        },
        {   //callings
            {
                &functions::algebra::int_add,
                {
                    {0, false},
                    {1, false},
                    {3, false}
                }
            },
            {
                &functions::algebra::int_add,
                {
                    {0, false},
                    {2, false},
                    {4, false}
                }
            }
        }
    };
    setter set {
        0  //name
    };
    function mux {
        0,  //name
        {   //defaultvalues
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr
        },
        {   //callings
            {
                &set,
                {
                    {5, false},
                    {6, false}
                }
            }
        }
    };
    add_funtion add {
        0,  //name
        {   //defaultvalues
            nullptr,
            nullptr,
            nullptr
        },
        {   //callings
            {
                &functions::algebra::int_add,
                {
                    {0, false},
                    {1, false},
                    {2, false}
                }
            },
            {
                &functions::algebra::float_add,
                {
                    {0, false},
                    {1, false},
                    {2, false}
                }
            },
            
        },
        {   //valuetypes
            {
                (void*)0,
                (void*)1,
                (void*)2,
                (void*)3
            },
            {
                (void*)0,
                (void*)1,
                (void*)2,
                (void*)3
            },
            {
                (void*)0,
                (void*)1,
                (void*)2,
                (void*)3
            }
        },
        &mux    //mux
    };

    clock_t t = clock();

    int a = 2, b = 8, c = 5, r1 = 0, r2 = 0;
    float fa = 20.5f, fb = 80.3f, fr = 0.1f;
    std::vector<void*> args({ &a, &b, &c, &r1, &r2 });
    addadd.execute(&args, nullptr, false);
    std::cout << r1 << "(2+8)" << std::endl;
    std::cout << r2 << "(2+5)" << std::endl;
    std::vector<void*> args2({ &b, &c, &r1, (void*)0, (void*)0, (void*)0 });
    add.execute(&args2, nullptr, false);
    std::cout << r1 << "(8+5)" << std::endl;
    std::vector<void*> args3({ &fa, &fb, &fr, (void*)1, (void*)1, (void*)1 });
    add.execute(&args3, nullptr, false);
    std::cout << fr << "(20.5f+80.3f)" << std::endl;
    std::vector<void*> args4({ &r1, &b, &r2 });
    functions::algebra::int_div.execute(&args4, nullptr, false);
    std::cout << r2 << "(10/8)" << std::endl;
    
    std::cout << "exec time: " <<  (clock() - t) / 1000.0 << "ms" << std::endl;
    t = clock();

    uint64_t e = 0;
    std::vector<void*> vec({(void*)L"algebra.dll", (void*)&dllf, 0, 0});
    memory::function::importfunction.execute(&vec, &e, false);
    std::cout << e << std::endl;
    std::cout << dllf << std::endl;
    dllf = (DLLPROC)GetProcAddress(LoadLibrary(L"algebra.dll"), "getftemp");
    std::cout << dllf << std::endl;
    std::cout << dllf() << std::endl;

    std::cout << "exec time: " << (clock() - t) / 1000.0 << "ms" << std::endl;
    t = clock();
    std::this_thread::sleep_for(timespan);


    test::test(test::INITMEM);

    test::test(test::LOG);
    test::test(test::ADD_OBJ_1);
    std::cout << "ADD" << std::endl;
    test::test(test::LOG);
    test::test(test::RESIZEBIG);
    std::cout << "BIG" << std::endl;
    test::test(test::LOG);
    test::test(test::RESIZESMALL);
    std::cout << "SMALL" << std::endl;
    test::test(test::LOG);

    test::test(test::TERMMEM);

    std::this_thread::sleep_for(timespan);

    return functionfactory::r();
}