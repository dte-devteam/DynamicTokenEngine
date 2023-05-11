#include <iostream>
#include <chrono>

#include "tests.h"
#include "utils/include/exec_time.h"
using namespace utils::exec_time;

#include <Windows.h>

/*
* future structure:
* lib(functions)-------->dll(any module, may be multiple)
*   ↓                     ↓
* lib(static instances)->exe
*/

struct int_addadd : function::function { using function::function; };
struct add_funtion : function::muxfunction { using muxfunction::muxfunction; };
struct setter : function::basicfunction { //temp
    using basicfunction::basicfunction;
    void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream) {
        *(size_t*)(*argumentspointer)[0] = (size_t)(*argumentspointer)[4];
    }
};
void f(int& v) {
    v = 100;
}
std::chrono::milliseconds timespan(5000);
int main() {
    test::inittestdata();
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
                (function::basicfunction*)(*test::modules[0].functions)[0].pointer,
                {
                    {0, false},
                    {1, false},
                    {3, false}
                }
            },
            {
                (function::basicfunction*)(*test::modules[0].functions)[0].pointer,
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
    add_funtion add {
        0,  //name
        {   //defaultvalues
            nullptr,
            nullptr,
            nullptr
        },
        {   //callings
            {
                (function::basicfunction*)(*test::modules[0].functions)[0].pointer,
                {
                    {0, false},
                    {1, false},
                    {2, false}
                }
            },
            {
                (function::basicfunction*)(*test::modules[0].functions)[1].pointer,
                {
                    {0, false},
                    {1, false},
                    {2, false}
                }
            }
        },
        &set   //mux
    };

    exec_time et;

    int a = 2, b = 8, c = 5, r1 = 0, r2 = 0;
    float fa = 20.5f, fb = 80.3f, fr = 0.1f;
    std::vector<void*> args{ &a, &b, &c, &r1, &r2 };
    addadd.execute(&args, nullptr, false, nullptr);
    std::cout << r1 << "(2+8)" << std::endl;
    std::cout << r2 << "(2+5)" << std::endl;
    std::vector<void*> args2{ &b, &c, &r1, (void*)0 };
    add.execute(&args2, nullptr, false, nullptr);
    std::cout << r1 << "(8+5)" << std::endl;
    std::vector<void*> args3{ &fa, &fb, &fr, (void*)1 };
    add.execute(&args3, nullptr, false, nullptr);
    std::cout << fr << "(20.5f+80.3f)" << std::endl;
    std::vector<void*> args4{ &r1, &b, &r2 };
    (*test::modules[0].functions)[7].pointer->execute(&args4, nullptr, false, nullptr);
    std::cout << r2 << "(10/8)" << std::endl;
    
    et.log();

    test::test(test::THREAD_CREATE);
    //std::cout << "THREAD" << std::endl;

    test::test(test::INITMEM);
    et.log();
    //test::test(test::LOG);
    test::test(test::ADD_OBJ);
    //test::test(test::LOG);
    test::test(test::ADD_OBJ);
    //test::test(test::LOG);
    //test::test(test::RESIZEBIG);
    //test::test(test::LOG);
    //test::test(test::RESIZESMALL);
    //test::test(test::LOG);
    test::test(test::LOG_INT_OBJ);
    test::test(test::OP_INT_SET_0);
    test::test(test::LOG_INT_OBJ);
    size_t i = 2;
    while (i--) {
        test::test(test::OP_INT_ADD);
        test::test(test::LOG_INT_OBJ);
    }
    test::test(test::THREAD_DELETE);
    //test::test(test::LOG);
    et.log();
    i = 20;
    while (i--) {
        test::test(test::THREAD_CREATE);
        test::test(test::THREAD_DELETE);
    }
    et.log();

    test::test(test::TERMMEM);

    
    std::cout << "END" << std::endl;

    et.log();

    //std::this_thread::sleep_for(timespan);
    test::us->joinstream(test::controlstream);

    return 0;
}