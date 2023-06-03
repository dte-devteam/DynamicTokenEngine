#include "../include/module_info.h"
#include <winver.h>
//module_info::module_info();
using namespace tokenoperator::dte_module;
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