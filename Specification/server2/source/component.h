#pragma once

#include "interfaces2.h"
#include "./lib/interfaces.h"

class ExtraHelper: public IBasicHelper, public IAdvancedHelper, public IExtraHelper {
    private:
        int refCount;
        IBasicHelper* basic_helper;
        IAdvancedHelper* advanced_helper;
    public:
        ExtraHelper();
        ~ExtraHelper();
        
        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();
        
        virtual HRESULT __stdcall GetBinFiles();

        virtual HRESULT __stdcall DeleteBinFiles();
        virtual HRESULT __stdcall TurnOffMachine();
        
        virtual HRESULT __stdcall GetUnusedPrograms();

};

class ExtraHelperClassFactory : public IExtraHelperClassFactory, public IClassFactory {
    private:
        int refCount;
    public:
        ExtraHelperClassFactory();
        ~ExtraHelperClassFactory();

        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter,const IID& iid, void** object);

        virtual HRESULT __stdcall LockServer(BOOL bLock);
        
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int password);
};