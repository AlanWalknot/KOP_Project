#pragma once

#include "lib/interfaces.h"
#include "lib/interfaces2.h"

#include <windows.h>
#include <iostream>

typedef HRESULT_ __stdcall (*FunctionType) (const CLSID_&, const IID_&, void**);

class EHelper
{
    private:
        const char* msg;
    public:
        EHelper(const char* msg);
        const char* GetMessage();
};

class CHelper
{
    private:
        IBasicHelper* basic_helper;
        IAdvancedHelper* advanced_helper;
        IExtraHelper* extra_helper;
        CHelper(const CHelper&) {};
        CHelper& operator=(const CHelper&) {return *this;};
    public:
        CHelper();
        CHelper(int password);

        virtual HRESULT_ __stdcall GetBinFiles();

        virtual HRESULT_ __stdcall DeleteBinFiles();
        virtual HRESULT_ __stdcall TurnOffMachine();
        
        virtual HRESULT_ __stdcall GetUnusedPrograms();

        ~CHelper();
};