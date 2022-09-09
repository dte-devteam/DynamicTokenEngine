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
	struct argument {
		uint64_t name = 0;							//им€ аргумента
		uint64_t type = 0;							//тип данных
		uint64_t fieldtarget = 0;					//им€ пол€ функции, куда применитс€ аргумент
		void* valuepointer = nullptr;				//указатель на значение
	};
	struct basicfunction {
		virtual ~basicfunction(){}
		uint64_t name = 0;							//им€ функции
		bool isbasic = false;						//булевое значение дл€ полиморфизма
		std::vector<argument> defaultvalues;		//вектор с указател€ми на значени€ по умолчанию
		std::vector<std::vector<uint64_t>> types;	//типы данных, которые момогу прин€ть пол€
		virtual void execute(std::vector<argument> args) = 0;
		protected:
			std::vector<argument> filldefaultvalues(std::vector<argument> args);
	};
	struct functioncaller {
		basicfunction* functionpointer = nullptr;	//указатель на функцию
		std::vector<uint64_t> args_name;			//имена аргументов, которые приментс€ к функции
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