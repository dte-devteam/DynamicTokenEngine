#pragma once
#include <iostream>


#include "target_architecture.h"
#include <minwindef.h>
#include <winver.h>


#include <vector>
/*
* future structure:
* lib(data template)->dll(any module, may be multiple)
* lib(data template)->exe(core)
* dll(any module, may be multiple)->exe(core)
*/

//to do, all arrays if can have size 0 - set limit to delete[] (otherwise heap corruption)

void test() {

}