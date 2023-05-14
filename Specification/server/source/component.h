#pragma once

#include "interfaces.h"


class Helper : public IBasicHelper, public IAdvancedHelper {
    private:
        int refCount;
    public:
        Helper();
        ~Helper();
        
        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall GetBinFiles();

        virtual HRESULT __stdcall DeleteBinFiles();
        virtual HRESULT __stdcall TurnOffMachine();
        
};

class HelperClassFactory : public IHelperClassFactory
{
    private:
        int refCount;
    public:
        HelperClassFactory();
        ~HelperClassFactory();

        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter,const IID& iid, void** object);
        
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int password);

};