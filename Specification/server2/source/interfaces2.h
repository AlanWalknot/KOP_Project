#pragma once

#include <string>
#include <iostream>

#include <Windows.h>

class Constants2 {
    public:
    
    static IID IID_IUnknown;
    static IID IID_IClassFactory;

    static IID IID_IBasicHelper;
    static IID IID_IAdvancedHelper;

    static IID IID_IHelperClassFactory;

    //GUID FOR HELPER : {ABEE2CE5-D891-4DBB-9043-6A03766C5E44}
    static CLSID CLSID_Helper;

    static IID IID_IExtraHelper;
    static IID IID_IExtraHelperClassFactory;
    
    //GUID FOR EXTRA HELPER: {D9BB0984-E8BE-4250-B559-73685FE1B5DC}
    static CLSID CLSID_ExtraHelper;
};


class IExtraHelper : public IUnknown{
    public:
        virtual HRESULT __stdcall GetUnusedPrograms() = 0;
};

class IExtraHelperClassFactory : public IUnknown {
    public:
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int password) = 0;
};

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object);
