#pragma once

#include "IUnknown_.h"

class IBinInfo : public IUnknown_ {
    public:
    virtual HRESULT_ __stdcall GetFiles() = 0;
    virtual HRESULT_ __stdcall GetWeight() = 0;
};