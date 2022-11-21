#pragma once
#pragma warning(disable:4275) //solve this later!
#include "pch.h"
#ifdef ALGEBRA_EXPORTS
#define ALGEBRA_API __declspec(dllexport)
#else
#define ALGEBRA_API __declspec(dllimport)
#endif
using namespace functionfactory;
namespace functions {
	namespace algebra {
		//constructors
		//(+)
		struct __declspec(dllexport) int_add_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct __declspec(dllexport) float_add_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct __declspec(dllexport) add_function : muxfunction {
			using muxfunction::muxfunction;
		};
		//(-)
		struct __declspec(dllexport) int_sub_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct __declspec(dllexport) float_sub_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		//(*)
		struct __declspec(dllexport) int_mul_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct __declspec(dllexport) float_mul_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		//(/)
		struct __declspec(dllexport) int_div_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		struct __declspec(dllexport) float_div_function : basicfunction {
			using basicfunction::basicfunction;
			void execute(std::vector<void*>* argumentspointer, uint64_t* errorcodepointer, bool forced, void* stream);
		};
		//(%)
		//instances
		//(+)
		int_add_function int_add {
			0,	//name
			{	//default values
				nullptr,
				nullptr,
				nullptr
			}
		};
		float_add_function float_add {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		add_function add {
			0,	//name
			{	//defaultvalues
				nullptr,
				nullptr,
				nullptr
			},
			{	//callings
				{
					&int_add,
					{
						{0, false},
						{1, false},
						{2, false}
					}
				},
				{
					&float_add,
					{
						{0, false},
						{1, false},
						{2, false}
					}
				}
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
			nullptr //&mux
		};
		//(-)
		int_sub_function int_sub {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		float_sub_function float_sub {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		//(*)
		int_mul_function int_mul {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		float_mul_function float_mul {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		//(/)
		int_div_function int_div {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		float_div_function float_div {
			0,
			{
				nullptr,
				nullptr,
				nullptr
			}
		};
		//(%)
		//function vector
		std::vector<basicfunction*>* functions = new std::vector<basicfunction*>(
			{
				&int_add,
				&float_add,
				&add,
				&int_sub,
				&float_sub,
				&int_mul,
				&float_mul,
				&int_div,
				&float_div
			}
		);
		extern _declspec(dllexport) std::vector<basicfunction*>* getfunctions() {
			return functions;
		}
	}
}