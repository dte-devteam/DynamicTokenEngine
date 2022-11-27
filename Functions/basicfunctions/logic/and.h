#pragma once
#pragma warning(disable:4275) //solve this later!
#include "pch.h"
using namespace functionfactory;
std::vector<basicfunction*>* functions = new std::vector<basicfunction*>(
	{

	}
);
extern std::vector<basicfunction*>* getfunctions() {
	return functions;
}