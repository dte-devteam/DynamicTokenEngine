#pragma once
#include <iostream>

#include "token/function/include/basic_function.h"

#include "token/data/include/scope.h"
#include "token/function/include/basic_function.h"
#include "token/stream/include/basic_stream.h"
using namespace tokenoperator::dte_token;

#include "module/include/module_version.h"
#include "module/include/module_source_requirement.h"
using namespace tokenoperator::dte_module;

#include "utils/include/hash.h"
#include "utils/include/exec_time.h"
using namespace utils;

/*
* future structure:
* lib(functions)-------->dll(any module, may be multiple)
*   ↓                     ↓
* lib(static instances)->exe
*/

struct int_add : function::basic_function {
	using basic_function::basic_function;
	void execute(const stream::basic_stream& caller, const function::bf_args& args, bool forced = false) {
		std::cout << ++(*(int*)(args.get_data())[0]) << std::endl;
		//std::cout << argument_pointer->size() << std::endl;
	}
};
bool* is_base_of_scope = new bool[10] { false };
void func1() {}
data::smart_pointer<data::smart_pointer<object>> func2() {
	return data::smart_pointer<data::smart_pointer<object>>(new data::smart_pointer<object>(nullptr, 9876));
}
void func3() {
	std::pair<uint64_t, bool>* paths = new std::pair<uint64_t, bool>[] {
		{ 50, false },
		{ 45, false },
		{ 40, false },
		{ 35, false },
		{ 30, false },
		{ 25, false },
		{ 20, false },
		{ 15, false },
		{ 10, false },
		{ 5, false }
	};
	data::scope_path sc(10, paths, 7887);
	std::cout << "path is:" << std::endl;
	for (size_t i = 0; i < sc.get_size(); i++) {
		std::cout << i << "->" << sc.get_value()[i].first << ":" << sc.get_value()[i].second << std::endl;
	}
	//ok^^^
}
void func4() {
	data::scope_path sp1(2, new std::pair<uint64_t, bool>[] { {2222, false}, { 3333, false }});
	data::scope_path sp2(2, new std::pair<uint64_t, bool>[] { {2222, true}, { 1111, true }});
	data::smart_pointer<object> sop_root = new data::scope(0, 0, 0);
	data::smart_pointer<object> sop1 = new data::scope(0, 0, 1111);
	data::smart_pointer<object> sop2 = new data::scope(1, 1, 2222);
	data::smart_pointer<object> sop3 = new data::scope(0, 0, 3333);
	((data::scope*)sop_root.get_pointer())->add_object(sop1, true);
	((data::scope*)sop1.get_pointer())->add_object(sop2, true);
	((data::scope*)sop2.get_pointer())->add_object(sop3, true);
	std::cout << ((data::scope*)sop1.get_pointer())->root_num << std::endl;
	std::cout << ((data::scope*)sop1.get_pointer())->roots[0]->getID() << std::endl;
	std::cout << ((data::scope*)sop2.get_pointer())->root_num << std::endl;
	std::cout << ((data::scope*)sop2.get_pointer())->roots[0]->getID() << std::endl;
	std::cout << ((data::scope*)sop3.get_pointer())->root_num << std::endl;
	std::cout << ((data::scope*)sop3.get_pointer())->roots[0]->getID() << std::endl;

	std::cout << "----------" << std::endl;
	std::cout << ((data::scope*)sop1.get_pointer())->get_object(sp1)->getID() << std::endl;
	std::cout << ((data::scope*)sop3.get_pointer())->get_object(sp2)->getID() << std::endl;
	std::cout << "----------" << std::endl;

	((data::scope*)sop2.get_pointer())->remove_object(sop3->getID());
	std::cout << ((data::scope*)sop3.get_pointer())->root_num << std::endl;
}
void func5() {
	std::cout << pearson_hash<char, int>(new char[] {'f'}, 1) << std::endl;
	std::cout << pearson_hash<int, int>(new int[] {123}, 1) << std::endl;
	std::cout << pearson_hash<wchar_t, int>(L"text", 4) << std::endl;


	wchar_t i = 0;
	uint64_t ii = 0;
	std::cout << type_in_type_capasity<decltype(i), decltype(ii)>() << std::endl;

	const wchar_t* _str = L"wwwwwwww/.z\\y/.x";
	wchar_t* wstr = L"wwwwwwww";
	wchar_t* zstr = L"z";
	wchar_t* ystr = L"y";
	wchar_t* xstr = L"x";
	data::scope_path sp = data::token_path(_str, std::wcslen(_str), 0);
	std::cout << "----------" << std::endl;
	std::cout << pearson_hash<wchar_t, int>(wstr, std::wcslen(wstr)) << std::endl;
	std::cout << sp.get_value()[0].first << ":" << sp.get_value()[0].second << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << pearson_hash<wchar_t, int>(zstr, std::wcslen(zstr)) << std::endl;
	std::cout << sp.get_value()[1].first << ":" << sp.get_value()[1].second << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << pearson_hash<wchar_t, int>(ystr, std::wcslen(ystr)) << std::endl;
	std::cout << sp.get_value()[2].first << ":" << sp.get_value()[2].second << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << pearson_hash<wchar_t, int>(xstr, std::wcslen(xstr)) << std::endl;
	std::cout << sp.get_value()[3].first << ":" << sp.get_value()[3].second << std::endl;
	std::cout << "----------" << std::endl;
}
void func6() {
	data::smart_pointer<object> adder = new int_add();
	stream::basic_stream s_helper = stream::basic_stream(nullptr, 0);
	stream::basic_stream s = stream::basic_stream(adder, 0);
	s_helper.callstack = new std::stack<uint64_t>();
	int a = 0, b = 0;
	object* _args_a[] = {
		(object*)&a
	};
	object* _args_b[] = {
		(object*)&b
	};
	function::bf_args args_a{ 1, _args_a };
	function::bf_args args_b{ 2, _args_b };
	size_t i = 1;
	exec_time et;
	while (i--) {
		s.execute(s_helper, args_a, false);
		s.joinstream();
		s.execute(s_helper, args_b, false);
		s.joinstream();
	}
	std::cout << "dt: " << et.get_dt() << std::endl;
}
void func7() {
	function::bf_args bfa1(6, new object*[]{
		(object*)1,
		(object*)0,
		(object*)3,
		(object*)0,
		(object*)5,
		(object*)12
	});
	function::bf_args bfa2(5, new object*[]{
		(object*)6,
		(object*)7,
		(object*)8,
		(object*)9,
		(object*)10
	});
	function::bf_args bfa3(bfa1, bfa2);
	//output should be: 1,7,3,9,5,12
	size_t i = 0;
	while (i < bfa3.get_size()) {
		std::cout << (uint64_t)bfa3.get_data()[i++] << std::endl;
	}
}
void func8() {
	module_version mv = module_version(123, MAX_MODULE_VERSION);
	std::cout << mv.getID() << std::endl;

	func1();
	data::smart_pointer<data::smart_pointer<object>> sop2(func2());
	data::smart_pointer<data::smart_pointer<object>> sop3(sop2);
	std::cout << sop3 << ":" << sop3.get_owner_num() << std::endl;
	std::cout << sop2 << ":" << sop2.get_owner_num() << std::endl;
	sop2 = nullptr;
	std::cout << sop3 << ":" << sop3.get_owner_num() << std::endl;
	std::cout << sop2 << ":" << sop2.get_owner_num() << std::endl;
	sop2 = sop3;
	std::cout << sop3 << ":" << sop3.get_owner_num() << std::endl;
	std::cout << sop2 << ":" << sop2.get_owner_num() << std::endl;
	std::cout << sop2->getID() << std::endl;
	std::cout << ((data::type<void*>*)sop2.get_pointer())->getID() << std::endl;

	//fuck yes :) code below will allow to create other instantiation of smart_pointer template
	data::smart_pointer<object> sop4(sop3);
	std::cout << sop4->getID() << ":" << sop4.get_owner_num() << std::endl;
	std::cout << (sop4 == sop3) << std::endl;
}
void func9() {
	data::smart_pointer<int> i = new int[]{-9};
	std::cout << *i << ":" << i.get_type().get_name() << std::endl;
	data::smart_pointer<long long> ii = i;
	std::cout << ii.get_type().get_name() << std::endl;
}



void test() {
	std::cout << "**********" << std::endl;
	std::cout << "func1:" << std::endl;
	func1();
	std::cout << "func3:" << std::endl;
	func3();
	std::cout << "func4:" << std::endl;
	func4();
	std::cout << "func5:" << std::endl;
	func5();
	std::cout << "func6:" << std::endl;
	func6();
	std::cout << "func7:" << std::endl;
	func7();
	std::cout << "func8:" << std::endl;
	func8();
	std::cout << "func9:" << std::endl;
	func9();
	std::cout << "**********" << std::endl;
}