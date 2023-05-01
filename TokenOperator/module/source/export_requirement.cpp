#include "../include/export_requirement.h"
#include "token_data.h"
namespace module {
	export_requirement::export_requirement(std::vector<std::pair<uint64_t, desc_type>> export_units, void*& target, bool critial, std::vector<std::vector<size_t>> whenbecomescritical) : export_units(export_units), target(target), critial(critial), whenbecomescritical(whenbecomescritical) {}
	std::vector<std::vector<size_t>> export_requirement::getwhenbecomescritical() {
		return whenbecomescritical;
	}
	std::vector<std::pair<uint64_t, desc_type>> export_requirement::getexport_units() {
		return export_units;
	}
	void*& export_requirement::gettarget() {
		return target;
	}
	bool export_requirement::iscritial() {
		return critial;
	}
	bool export_requirement::becomescritical(std::vector<size_t>& inited_requirements) {
		std::vector<size_t>::iterator begin = inited_requirements.begin();
		std::vector<size_t>::iterator end = inited_requirements.end();
		for (std::vector<size_t>& wbc : whenbecomescritical) {
			for (size_t wbc_i : wbc) {
				std::vector<size_t>::iterator iter = std::find_if(
					begin,
					end,
					[wbc_i](size_t i) {
						return i == wbc_i;
					}
				);
				if (iter == end) {
					return true;
				}
			}
		}
		return false;
	}
}