
#pragma once
#include <windows.h>
#include <ShlObj.h> // For SHGetKnownFolderPath
#include <filesystem> // For std::filesystem
#include <string>
#include <ShlObj.h>
class AssetPath
{


public:
    std::wstring GetAssetsFolderPath()
    {

        auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;
        //get the path to te running solution
        auto name = folder->Path;

        auto pad = name + "\\Assets";

        //folder->GetFileAsync(Platform::StringReference(filename.c_str()))).then([](StorageFile^ file);

        return ConvertString(pad);
    }

    std::wstring ConvertString(Platform::String^ str)
    {
        std::wstring wstr(str->Begin(), str->End());
        return wstr;
    }
    //std::wstring GetLocalAssetsFolderPath()
    //{
    //    WCHAR szPath[MAX_PATH];
    //    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath)))
    //    {
    //        std::wstring path(szPath);
    //        path += L"\\MyApp\\Assets\\";
    //        return path;
    //    }
    //    return L"";
    //}
};
