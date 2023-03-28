#include "target_architecture.h"
#include <libloaderapi.h>
#include <winver.h>
#include "../include/module.h"
namespace module {
	module::module(std::wstring dllname) : dllname(dllname) {
		library = LoadLibrary(dllname.c_str());
        fetch_module_data();
        search_for_version(dllname);
	}
	module::~module() {
		FreeLibrary(library);
	}
    std::wstring module::getdllname() {
        return dllname;
    }
    HMODULE module::getlibrary() {
        return library;
    }
    module_version module::getversion() {
        return version;
    }
	void module::search_for_version(std::wstring dllname) {
        DWORD verhandle = NULL, versize = GetFileVersionInfoSize(dllname.c_str(), &verhandle);
        if (versize) {
            UINT size = 0;
            LPBYTE buffer = nullptr;
            LPSTR verdata = new char[versize];
            if (GetFileVersionInfo(dllname.c_str(), verhandle, versize, verdata)) {
                if (VerQueryValue(verdata, L"\\", (VOID FAR* FAR*) &buffer, &size)) {
                    if (size) {
                        VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)buffer;
                        if (verInfo->dwSignature == 0xfeef04bd) {
                            version = module_version(
                                verInfo->dwFileVersionMS >> 16,
                                verInfo->dwFileVersionMS & 0xffff,
                                verInfo->dwFileVersionLS >> 16,
                                verInfo->dwFileVersionLS & 0xffff
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
        DLL_PROC_FD fd = (DLL_PROC_FD)GetProcAddress(library, "getnfunctions");
        DLL_PROC_TD t = (DLL_PROC_TD)GetProcAddress(library, "gettypes");
        DLL_PROC_VD v = (DLL_PROC_VD)GetProcAddress(library, "getdata");
        DLL_PROC_MR mr = (DLL_PROC_MR)GetProcAddress(library, "getinitrequirements");
        functions = fd ? fd() : nullptr;
        types = t ? t() : nullptr;
        data = v ? v() : nullptr;
        requirements = mr ? mr() : nullptr;
    }
}