#pragma once
#include <stdint.h>
#include <vector>
#include "deletable_obj.h"
namespace data {
	//(to do) ������� �� lib � DynamicTokenEngine � lib, ��� �� ����� �������������� dll (�� ������� �������)
	//��� ����������, ����� ����� ��������������
	static size_t POINTER_SIZE = sizeof(void*);
	static const unsigned int UINT_ZERO = 0;
	static const unsigned long long ULL_ZERO = UINT_ZERO;
	static const void* NULL_PTR = nullptr;
}