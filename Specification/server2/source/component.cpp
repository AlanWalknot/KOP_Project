#include "component.h"

    IID Constants::IID_IUnknown = {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants::IID_IClassFactory = {0x00000001,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

    IID Constants::IID_IHelperClassFactory = {0x000000010,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants2::IID_IExtraHelperClassFactory = {0x000000011,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants::IID_IBasicHelper = {0x000000015,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants::IID_IAdvancedHelper = {0x000000016,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants2::IID_IExtraHelper = {0x000000017,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

    //GUID FOR HELPER : {ABEE2CE5-D891-4DBB-9043-6A03766C5E44}
    CLSID Constants::CLSID_Helper = {0xABEE2CE5, 0xD891, 0x4DBB, {0x90, 0x43, 0x6A, 0x03, 0x76, 0x6C, 0x5E, 0x44}};
    //GUID FOR EXTRA HELPER: {D9BB0984-E8BE-4250-B559-73685FE1B5DC}
    CLSID Constants2::CLSID_ExtraHelper = {0xD9BB0984, 0xE8BE, 0x4250, {0xB5,0x59, 0x73, 0x68, 0x5F, 0xE1, 0xB5, 0xDC}};

ExtraHelper::ExtraHelper() {
    std::cout << "ExtraHelper::ExtraHelper()" << std::endl;
    refCount = 0;

    
    CoInitialize(NULL);

    IClassFactory* HCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_Helper, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**)&HCF);

    if(!SUCCEEDED(resFactory)) {
        std::cout << "No factory detected. Please, try again." << std::endl;
    }

    HRESULT resInstance = HCF -> CreateInstance(NULL, Constants::IID_IBasicHelper, (void**)&basic_helper);

    if (!SUCCEEDED(resInstance)) {
        std::cout << "No such function detected. Please, try again." << std::endl;
    }

   HRESULT resQuery = basic_helper -> QueryInterface(Constants::IID_IAdvancedHelper, (void**)&advanced_helper);

   if(!SUCCEEDED(resQuery)) {
        std::cout << "Error while trying to perform server2/component.cpp:basic_helper -> QueryInterface " << std::endl;
   }

   HCF -> Release();
   CoUninitialize();
}

ExtraHelper::~ExtraHelper() {
    std::cout << "ExtraHelper::~ExtraHelper()" << std::endl;
    
    basic_helper -> Release();
    advanced_helper -> Release();
}


HRESULT ExtraHelper::QueryInterface(const IID& iid, void** object) {
    std::cout << "ExtraHelper::QueryInterface()" << std::endl;

    if (iid == Constants::IID_IUnknown)
    {
        *object = (IUnknown*) (IBasicHelper*) this;
    }
    else if (iid == Constants::IID_IBasicHelper)
    {
        *object = static_cast<IBasicHelper*>(this);
    }
    else if (iid == Constants::IID_IAdvancedHelper)
    {
        *object = static_cast<IAdvancedHelper*>(this);
    }
    else if (iid == Constants2::IID_IExtraHelper)
    {
        *object = static_cast<IExtraHelper*>(this);
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }
    
    this->AddRef();
    return S_OK;
}

ULONG ExtraHelper::AddRef() {
    refCount++;
    return refCount;
}

ULONG ExtraHelper::Release() {
    refCount--;
    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT ExtraHelper::GetBinFiles() {

    std::cout << "ExtraHelper::GetBinFiles()" << std::endl;
    
    return basic_helper -> GetBinFiles();
}

HRESULT ExtraHelper::DeleteBinFiles() {
    std::cout << "ExtraHelper::DeleteBinFiles()" << std::endl;
    
    return advanced_helper -> DeleteBinFiles();
}

HRESULT ExtraHelper::TurnOffMachine() {
    std::cout << "ExtraHelper::TurnOffMachine()" << std::endl;
    
    return advanced_helper -> TurnOffMachine();
}

HRESULT ExtraHelper::GetUnusedPrograms() {

    std::cout << "ExtraHelper::GetUnusedPrograms()" << std::endl;
    return S_OK;
}

//-------------------------ClassFactory begins--------------------------------------

ExtraHelperClassFactory::ExtraHelperClassFactory () {
    std::cout << "ExtraHelperClassFactory::ExtraHelperClassFactory()" << std::endl;
    this->refCount = 0;
}

ExtraHelperClassFactory::~ExtraHelperClassFactory() {
    std::cout << "ExtraHelperClassFactory::~ExtraHelperClassFactory()" << std::endl;
}


HRESULT ExtraHelperClassFactory ::QueryInterface(const IID& iid, void** object) {
    std::cout << "ExtraHelperClassFactory::QueryInterface()" << std::endl;

    if (iid == Constants::IID_IClassFactory)
    {
        *object = (IUnknown*) (IClassFactory*) this;
    }
    else if (iid == Constants2::IID_IExtraHelperClassFactory )
    {
        *object = (IUnknown*) (IExtraHelperClassFactory*) this;
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }
    
    this->AddRef();
    return S_OK;
}

ULONG ExtraHelperClassFactory ::AddRef() {
    refCount++;
    return refCount;
}

ULONG ExtraHelperClassFactory ::Release() {
    refCount--;

    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT ExtraHelperClassFactory::CreateInstance(IUnknown* pUnknownOuter,const IID& iid, void** object) {
    std::cout << "ExtraHelperClassFactory::CreateInstance()" << std::endl;
    IUnknown* s = (IUnknown*) (IBasicHelper*) new ExtraHelper();

    s -> AddRef();
    HRESULT res = s->QueryInterface(iid, object);
    s -> Release();
    
    return res;
}

HRESULT ExtraHelperClassFactory ::CreateInstance(const IID& iid, void** object, int password)
{
    std::cout <<" ExtraHelperClassFactory::CreateInstance(password)" << std::endl;
    HRESULT res = E_NOTIMPL;

    if (password != NULL)
    {
        IUnknown* s = (IUnknown*) (IBasicHelper*) new ExtraHelper();

        s -> AddRef();
        res = s -> QueryInterface(iid, object);
        s -> Release();
    }
    
    return res;
}

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object)
{
    std::cout << "Export Function: GetClassObject()" << std::endl;

    IUnknown* s = NULL;

    if (clsid == Constants2::CLSID_ExtraHelper)
    {
        s = (IUnknown*) (IClassFactory*) new ExtraHelperClassFactory();
    }
    else
    {
        *object = NULL;
        return E_NOTIMPL;
    }

    s -> AddRef();
    HRESULT res = s -> QueryInterface(iid, object);
    s -> Release();
    
    return S_OK;
}
