#include <iostream>

#include "utils/include/hash.h"
#include "memory/include/function.h"

#include "memory/include/init_data.h"

#define ALGEBRA_EXPORTS
#include "add.h"

#include <chrono>
#include <thread>
#include <ctime>


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

    int temp1 = -4;
    int temp2 = 14;
    int tempr = 0;
    std::vector<void*> args5({ &temp1, &temp2, &tempr });
    functions::algebra::int_add.execute(&args5, nullptr, false);
    std::cout << tempr << "(-4+14)" << std::endl;
    temp1 = -8;
    temp2 = 18;
    functions::algebra::int_add.execute(&args5, nullptr, false);
    std::cout << tempr << "(-8+18)" << std::endl;
    temp1 = -7;
    temp2 = 17;
    functions::algebra::int_add.execute(&args5, nullptr, false);
    std::cout << tempr << "(-7+17)" << std::endl;
    temp1 = -6;
    temp2 = 16;
    functions::algebra::int_add.execute(&args5, nullptr, false);
    std::cout << tempr << "(-6+16)" << std::endl;
    temp1 = -5;
    temp2 = 15;
    functions::algebra::int_add.execute(&args5, nullptr, false);
    std::cout << tempr << "(-5+15)" << std::endl;
    temp1 = -1;
    temp2 = 11;
    functions::algebra::int_add.execute(&args5, nullptr, false);
    std::cout << tempr << "(-1+11)" << std::endl;

    std::cout << "exec time: " << (clock() - t) / 1000.0 << "ms" << std::endl;
    t = clock();

    int ta = 2;
    int tb = 8;
    int tr = 0;
    int* tap = &ta;
    int* tbp = &tb;
    int* trp = &tr;
    *trp = *tap + *tbp;
    std::cout << tr << "(2+8)" << std::endl;
    ta = 7;
    tb = 3;
    tr = 0;
    tap = &ta;
    tbp = &tb;
    trp = &tr;
    *trp = *tap + *tbp;
    std::cout << tr << "(7+3)" << std::endl;
    ta = 9;
    tb = 1;
    tr = 0;
    tap = &ta;
    tbp = &tb;
    trp = &tr;
    *trp = *tap + *tbp;
    std::cout << tr << "(9+1)" << std::endl;
    float tfa = 2.0f;
    float tfb = 8.0f;
    float tfr = 0.0f;
    float* tfap = &tfa;
    float* tfbp = &tfb;
    float* tfrp = &tfr;
    *tfrp = *tfap + *tfbp;
    std::cout << tr << "(2.0f+8.0f)" << std::endl;
    ta = 6;
    tb = 4;
    tr = 0;
    tap = &ta;
    tbp = &tb;
    trp = &tr;
    *trp = *tap / *tbp;
    std::cout << tr << "(6/4)" << std::endl;

    std::cout << "exec time: " << (clock() - t) / 1000.0 << "ms" << std::endl;
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

    memory::init::initobjmemory();
    for (memory::object::typeallocator* typealloc : memory::object::memorycontroller::instance()->objects) {
        std::cout << std::left << std::setw(6) << "size: ";
        std::cout << std::left << std::setw(7) << typealloc->gettypesize();
        std::cout << std::left << std::setw(8) << "length: ";
        std::cout << typealloc->getlistsize() << std::endl;
    }

    memory::object::memorycontroller::instance()->objects[2]->addobject(1, 12, nullptr);
    memory::object::memorycontroller::instance()->objects[2]->addobject(2, 12, nullptr);
    memory::object::memorycontroller::instance()->objects[2]->log_data();

    std::cout << "exec time: " << (clock() - t) / 1000.0 << "ms" << std::endl;
    t = clock();


    long long* mbi1 = (long long*)(memory::object::memorycontroller::instance()->objects[2]->getobject(1, false, nullptr)->pointer);
    *mbi1 = -25;
    mbi1 = (long long*)(memory::object::memorycontroller::instance()->objects[2]->getobject(2, false, nullptr)->pointer);
    *mbi1 = -50;
    std::cout << *(long long*)memory::object::memorycontroller::instance()->objects[2]->getobject(1, false, nullptr)->pointer << std::endl; //вот так будет, если мы посмотри на эти данные как на __int64
    std::cout << *(int*)memory::object::memorycontroller::instance()->objects[2]->getobject(1, false, nullptr)->pointer << std::endl;       //вот так будет, если мы посмотри на эти данные как на int
    std::cout << *(long long*)memory::object::memorycontroller::instance()->objects[2]->getobject(2, false, nullptr)->pointer << std::endl; //вот так будет, если мы посмотри на эти данные как на __int64
    std::cout << *(int*)memory::object::memorycontroller::instance()->objects[2]->getobject(2, false, nullptr)->pointer << std::endl;       //вот так будет, если мы посмотри на эти данные как на int

    std::cout << "exec time: " << (clock() - t) / 1000.0 << "ms" << std::endl;
    t = clock();

    memory::object::memorycontroller::instance()->objects[2]->log_data();

    std::cout << "exec time: " << (clock() - t) / 1000.0 << "ms" << std::endl;
    t = clock();

    std::chrono::milliseconds timespan(10000);
    std::this_thread::sleep_for(timespan);
    return functionfactory::test();
}