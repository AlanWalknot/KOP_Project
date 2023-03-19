#pragma once

using IID_ = int;
using CLSID_ = int;
using HRESULT_ = int;
using ULONG_ = int;


const int IID_IUnknown_ = 0;
const int IID_IClearBin = 1;
const int IID_IBinInfo = 2;

const int CLSID_CHelper = 1;

const int S_OK_ = 0;
const int E_NOINTERFACE_ = 1;
const int E_NOCOMPONENT_ = 2;

class IUnknown_ {
    public:
    virtual HRESULT_ __stdcall QueryInterface(const int& iid, void** ppv) = 0;
    virtual ULONG_ __stdcall AddRef() = 0;
    virtual ULONG_ __stdcall Release() = 0;
};