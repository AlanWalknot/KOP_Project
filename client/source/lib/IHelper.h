#pragma once

#include "IUnknown_.h"
#include "IClearBin.h"
#include "IBinInfo.h"

#include <iostream>

class IHelper  {
    public:

    virtual HRESULT_ __stdcall QueryInterface(const int& iid, void** ppv)=0;
    virtual ULONG_ __stdcall AddRef()=0;
    virtual ULONG_ __stdcall Release()=0;
    virtual HRESULT_ __stdcall GetFiles()=0;
    virtual HRESULT_ __stdcall GetWeight()=0;
    virtual HRESULT_ __stdcall ClearBin()=0;
};

HRESULT_ __stdcall CreateInstance_(const CLSID_& clsid, const IID_& iid, void** object);
