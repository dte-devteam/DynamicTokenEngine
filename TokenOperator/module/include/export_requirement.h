#pragma once
#include <cvt/wstring>
#include <vector>
#include "desc_type.h"
namespace module {
	//critial - if yes, export_requirement must be inited (if can`t - object will be uninited)
	//export_unit defines what data can be used for initiation, if none will be found object won`t have export_requirement inited
	//whenbecomescritical defines which indices should be uninited to make this export_requirement (which isn`t normaly critical) critical
	class export_requirement {
		public:
			export_requirement(std::pair<uint64_t, desc_type> export_unit, void*& target, bool critial = true, std::vector<std::vector<size_t>> whenbecomescritical = {});
			std::pair<uint64_t, desc_type> getexport_unit();
			std::vector<std::vector<size_t>> getwhenbecomescritical();
			void*& gettarget();
			bool iscritial();
			bool becomescritical(std::vector<size_t>& inited_requirements);
		protected:
			std::pair<uint64_t, desc_type> export_unit;
			std::vector<std::vector<size_t>> whenbecomescritical;
			void*& target;
			bool critial;
	};
}