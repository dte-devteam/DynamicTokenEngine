#include "../include/module_version.h"
#include "target_architecture.h"
#include <minwindef.h>
#include <winver.h>
#include <libloaderapi.h>
namespace dte_module {
	bool module_version::set_version_to_file(const wchar_t* path) {
        DWORD verhandle = NULL, versize = GetFileVersionInfoSize(path, &verhandle);
        if (versize) {
            UINT size = 0;
            LPBYTE buffer = nullptr;
            LPSTR verdata = new char[versize];
            if (GetFileVersionInfo(path, verhandle, versize, verdata)) {
                if (VerQueryValue(verdata, L"\\", (VOID FAR* FAR*) &buffer, &size)) {
                    if (size) {
                        VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)buffer;
                        if (verInfo->dwSignature == 0xfeef04bd) {
                            numbers[3] = verInfo->dwFileVersionLS & 0xFFFF;
                            numbers[2] = verInfo->dwFileVersionLS >> 16;
                            numbers[1] = verInfo->dwFileVersionMS & 0xFFFF;
                            numbers[0] = verInfo->dwFileVersionMS >> 16;
                            delete[] verdata;
                            return true;
                        }
                    }
                }
            }
            delete[] verdata;
        }
        return false;
	}
}
