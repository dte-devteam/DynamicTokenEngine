#include "../include/module_info.h"
#include <winver.h>
#include <libloaderapi.h>
using namespace tokenoperator::dte_module;
module_info::module_info(std::wstring dllname, uint64_t ID) : object(ID), dllname(dllname), library(LoadLibrary(dllname.c_str())) {
    search_for_version(dllname);
    fetch_module_data();
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
void module_info::fetch_module_data() {
    //DLL_PROC_FD fd = (DLL_PROC_FD)GetProcAddress(library, "getfunctions");
    //DLL_PROC_T t = (DLL_PROC_T)GetProcAddress(library, "gettypes");
    //DLL_PROC_V v = (DLL_PROC_V)GetProcAddress(library, "getdata");
    //DLL_PROC_MR mr = (DLL_PROC_MR)GetProcAddress(library, "getinitrequirements");
    //functions = fd ? fd() : nullptr;
    //types = t ? t() : nullptr;
    //data = v ? v() : nullptr;
    //requirements = mr ? mr() : nullptr;
}