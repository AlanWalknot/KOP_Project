#pragma once

#include "interfaces.h"


class Helper : public IBasicHelper, public IAdvancedHelper, public IDispatch {
    private:
        int refCount;
        //Тут поле для присвоения значений при необходимости
    public:
        Helper();
        ~Helper();
        
        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall GetBinFiles();

        virtual HRESULT __stdcall DeleteBinFiles();
        virtual HRESULT __stdcall TurnOffMachine();

        //IDispatch(Begin)
        virtual HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId);
        virtual HRESULT __stdcall Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDIspParams,
                                        VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr);

        virtual HRESULT __stdcall GetTypeInfoCount(UINT* pctinfo); // Заглушка
        virtual HRESULT __stdcall GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo);
};

class HelperClassFactory : public IClassFactory, public IHelperClassFactory
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

        virtual HRESULT __stdcall LockServer(BOOL bLock);

};