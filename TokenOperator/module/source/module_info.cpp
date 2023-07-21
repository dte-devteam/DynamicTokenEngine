#include "../include/module_info.h"
using namespace tokenoperator::dte_module;
using namespace tokenoperator::dte_token::data;
module_info::module_info(std::wstring dllname, uint64_t ID) : value<std::pair<module_source*, size_t>>(ID), dllname(dllname), library(LoadLibrary(dllname.c_str())) {
    search_for_version(dllname);
    module_source** module_source_pointer = (module_source**)GetProcAddress(library, "module_sources");
    size_t* module_source_num_pointer = (size_t*)GetProcAddress(library, "module_scope");
    v.first = module_source_pointer ? *module_source_pointer : nullptr;
    v.second = module_source_num_pointer ? *module_source_num_pointer : 0;
}
module_info::module_info(const module_info& mi) : value<std::pair<module_source*, size_t>>(mi.ID), dllname(mi.dllname), library(LoadLibrary(mi.dllname.c_str())) {
    v = mi.v;
}
module_info::~module_info() {
    FreeLibrary(library);
}
void module_info::search_for_version(std::wstring& fullpath) {
    DWORD verhandle = NULL, versize = GetFileVersionInfoSize(fullpath.c_str(), &verhandle);
    if (versize) {
        UINT size = 0;
        LPBYTE buffer = nullptr;
        LPSTR verdata = new char[versize];
        if (GetFileVersionInfo(fullpath.c_str(), verhandle, versize, verdata)) {
            if (VerQueryValue(verdata, L"\\", (VOID FAR * FAR*) & buffer, &size)) {
                if (size) {
                    VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)buffer;
                    if (verInfo->dwSignature == 0xfeef04bd) {
                        version = module_version(
                            0,  //id (to do)
                            verInfo->dwFileVersionLS & 0xFFFF,
                            verInfo->dwFileVersionLS >> 16,
                            verInfo->dwFileVersionMS & 0xFFFF,
                            verInfo->dwFileVersionMS >> 16
                        );
                        delete[] verdata;
                        return;
                    }
                }
            }
        }
        version = module_version(
            0  //id (to do)
        );
        delete[] verdata;
    }
}