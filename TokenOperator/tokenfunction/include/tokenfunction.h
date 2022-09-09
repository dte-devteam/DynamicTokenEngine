#pragma once
#include <vector>
#include <algorithm>
/*
ожидаема€ структура функции
function = {										//объ€вл€ем функцию
	name = "addandadd"								//называем функцию
	args = {										//объ€вл€ем аргументы
		a = int										//называем аргумент и даем ему тип
		b = int	
		с = int	
		r1 = int	
		r2 = int	
	}
	sub_functions = {								//объ€вл€ем функции, которые будут вызыватьс€ внутри 
		add = {a, b, r1}							//объ€вл€ем какие аргументы будут использованы внутри функции
		add = {a, c, r2}
	}
}
*/

namespace tokenfunction {
	struct functionfield {
		uint64_t name;								//им€ пол€
		std::vector<uint64_t> types;				//типы данных, которое может прин€ть поле
	};
	struct argument {
		uint64_t name;								//им€ аргумента
		uint64_t type;								//тип данных
		uint64_t fieldtarget = 0;					//им€ пол€ функции, куда применитс€ аргумент
		void* valuepointer;							//указатель на значение
	};
	struct functioncaller {
		basicfunction* functionpointer;				//указатель на функцию
		std::vector<uint64_t> args_name;			//имена аргументов, которые приментс€ к функции
	};
	struct basicfunction {
		uint64_t name;								//им€ функции
		bool isbasic;								//булевое значение дл€ полиморфизма
		std::vector<argument> defaultvalues;		//вектор с указател€ми на значени€ по умолчанию
		virtual void execute(std::vector<argument> args) = 0;
		protected:
			std::vector<argument> filldefaultvalues(std::vector<argument> args);
	};
	struct function : basicfunction {
		std::vector<functioncaller> subfunctions;	//вектор с указател€ми на функции
		bool isreliable;							//булевое значение дл€ полиморфизма
		void execute(std::vector<argument> args);
	};
	struct unreliablefunction : function {
		//to do
		//короче try catch система
	};
}