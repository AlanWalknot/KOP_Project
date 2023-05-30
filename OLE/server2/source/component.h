#pragma once

#include "interfaces2.h"
#include "./lib/interfaces.h"

class ExtraHelper: public IBasicHelper, public IAdvancedHelper, public IExtraHelper, public IDispatch {
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

        //IDispatch(Begin)
        virtual HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId);
        virtual HRESULT __stdcall Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDIspParams,
                                        VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr);

        virtual HRESULT __stdcall GetTypeInfoCount(UINT* pctinfo); // Заглушка
        virtual HRESULT __stdcall GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo);
};

class ExtraHelperClassFactory : public IClassFactory, public IExtraHelperClassFactory {
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