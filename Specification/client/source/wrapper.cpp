#include "wrapper.h"

EHelper::EHelper(const char* msg) {
    this -> msg = msg;
}

const char* EHelper::GetMessage() {
    return msg;
}

CHelper::CHelper() {
    const char* path = "./client/source/lib/manager.dll";

    HINSTANCE h = LoadLibrary(path);

    if (!h)
    {
           std::cout << "No such DLL detected. Please, try again." << std::endl;
           return;
    }
    
    FunctionType CreateInst = (FunctionType) GetProcAddress(h, "CreateInstance");

    if (!CreateInst )
    {
          std::cout << "No such function detected. Please, try again." << std::endl;
          return;
    }

    HRESULT_ res = CreateInst (CLSID_ExtraHelperClassFactory, IID_IBasicHelper, (void**) &basic_helper);

    if (res == E_NOCOMPONENT_)
    {
        throw EHelper("Error while creating CHelper: Unsupported component");
    }
    else if (res == E_NOINTERFACE_)
    {
        throw EHelper("Error while creating CHelper: Unsupported interface");
    }
    else if (res != S_OK_)
    {
        throw EHelper("Error while creating CHelper: Unknown error");
    }

    basic_helper -> QueryInterface(IID_IAdvancedHelper, (void**) &advanced_helper);

    if (res != S_OK_)
    {
        basic_helper -> Release();
        if (res == E_NOINTERFACE_)
        {
            throw EHelper("Error while creating CServer: Unsupported interface");
        }
        else
        {
            throw EHelper("Error while creating CServer: Unknown error");
        }
    }

    basic_helper -> QueryInterface(IID_IExtraHelper, (void**) &extra_helper);
}


CHelper::~CHelper() {
    basic_helper -> Release();
    advanced_helper -> Release();
    extra_helper -> Release();
}


CHelper::CHelper(int password)
{
    ExtraHelperClassFactory* extra_helper_CF = NULL;

    const char* path = "./client/source/lib/manager.dll";

    HINSTANCE h = LoadLibrary(path);

    if (!h)
    {
           std::cout << "No such DLL detected. Please, try again." << std::endl;
           return;
    }

    FunctionType GetClassObj = (FunctionType) GetProcAddress(h, "GetClassObject");

    if (!GetClassObj )
    {
          std::cout << "No such function detected. Please, try again." << std::endl;
          return;
    }

    HRESULT_ res = GetClassObj (CLSID_ExtraHelperClassFactory, IID_IExtraHelperClassFactory, (void**) &extra_helper_CF);

    if (res == E_NOCOMPONENT_)
    {
        throw EHelper("Error while creating CHelper: Unsupported component");
    }
    else if (res == E_NOINTERFACE_)
    {
        throw EHelper("Error while creating CHelper: Unsupported interface");
    }
    else if (res != S_OK_)
    {
        throw EHelper("Error while creating CHelper: Unknown error");
    }

    basic_helper = NULL;
    
    res = extra_helper_CF -> CreateInstance(IID_IBasicHelper, (void**) &basic_helper, password);

    if (res != S_OK_)
    {
        throw EHelper("Error: wrong license");
    }

    advanced_helper = NULL;
    res = basic_helper -> QueryInterface(IID_IAdvancedHelper, (void**) &advanced_helper);
    
    if (res != S_OK_)
    {
        basic_helper -> Release();
        if (res == E_NOINTERFACE_)
        {
            throw EHelper("Error while creating CServer: Unsupported interface");
        }
        else
        {
            throw EHelper("Error while creating CServer: Unknown error");
        }
    }

    basic_helper -> QueryInterface(IID_IExtraHelper (void**) &extra_helper);

    extra_helper_CF->Release();
}

HRESULT_ __stdcall CHelper::GetBinFiles() {
    return basic_helper -> GetBinFiles();
}

HRESULT_ __stdcall CHelper::DeleteBinFiles() {
    return basic_helper -> DeleteBinFiles();
}

HRESULT_ __stdcall CHelper::TurnOffMachine() {
    return advanced_helper -> TurnOffMachine();
}

HRESULT_ __stdcall CHelper::GetUnusedPrograms() {
    return extra_helper -> GetUnusedPrograms();
}