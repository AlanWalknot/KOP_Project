#pragma once

#include "IUnknown_.h"

class IClearBin : public IUnknown_ {
    public:
    virtual HRESULT_ __stdcall ClearBin() = 0;
};