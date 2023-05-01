#include "target_architecture.h"
#include <libloaderapi.h>
#include <winver.h>
#include "../include/module.h"
namespace module {
	module::module(std::wstring dllname, std::wstring path) : dllname(dllname) {
        std::wstring fullpath = path + dllname;
		library = LoadLibrary(fullpath.c_str());
        fetch_module_data();
        search_for_version(fullpath);
	}
    module::module(const module& parent) : module(parent.dllname) {}
	module::~module() {
        FreeLibrary(library);
    }
    std::wstring module::getdllname() const {
        return dllname;
    }
    HMODULE module::getlibrary() {
        return library;
    }
    module_version module::getversion() {
        return version;
    }
	void module::search_for_version(std::wstring& fullpath) {
        DWORD verhandle = NULL, versize = GetFileVersionInfoSize(fullpath.c_str(), &verhandle);
        if (versize) {
            UINT size = 0;
            LPBYTE buffer = nullptr;
            LPSTR verdata = new char[versize];
            if (GetFileVersionInfo(fullpath.c_str(), verhandle, versize, verdata)) {
                if (VerQueryValue(verdata, L"\\", (VOID FAR* FAR*) &buffer, &size)) {
                    if (size) {
                        VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)buffer;
                        if (verInfo->dwSignature == 0xfeef04bd) {
                            version = module_version(
                                verInfo->dwFileVersionMS >> 16,
                                verInfo->dwFileVersionMS & 0xFFFF,
                                verInfo->dwFileVersionLS >> 16,
                                verInfo->dwFileVersionLS & 0xFFFF
                            );
                            delete[] verdata;
                            return;
                        }
                    }
                }
            }
            version = module_version();
            delete[] verdata;
        }
	}
    void module::fetch_module_data() {
        functions = (DTE_MODULE_FD*)GetProcAddress(library, "functions");
        types = (DTE_MODULE_TD*)GetProcAddress(library, "types");
        data = (DTE_MODULE_VD*)GetProcAddress(library, "data");
        requirements = (DTE_MODULE_MR*)GetProcAddress(library, "requirements");
    }
}