#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include <string>

class Constants {
    public:
    static IID IID_IUnknown;
    static IID IID_IClassFactory;

    static IID IID_IBasicHelper;
    static IID IID_IAdvancedHelper;

    static IID IID_IHelperClassFactory;

    //GUID FOR HELPER : {ABEE2CE5-D891-4DBB-9043-6A03766C5E44}
    static IID CLSID_Helper;
};



class IBasicHelper : public IUnknown {
    public:
        virtual HRESULT __stdcall GetBinFiles() = 0;
};

class IAdvancedHelper : public IUnknown
{
    public:
        virtual HRESULT __stdcall DeleteBinFiles() = 0;
        virtual HRESULT __stdcall TurnOffMachine() = 0;
};

class IHelperClassFactory  : public IUnknown
{
    public:
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int password) = 0;
};

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object);