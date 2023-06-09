#include "component.h"

    IID Constants::IID_IUnknown = {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants::IID_IClassFactory = {0x00000001,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

    IID Constants::IID_IHelperClassFactory = {0x000000010,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants::IID_IBasicHelper = {0x000000015,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants::IID_IAdvancedHelper = {0x000000016,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

    //GUID FOR HELPER : {ABEE2CE5-D891-4DBB-9043-6A03766C5E44}
    CLSID Constants::CLSID_Helper = {0xABEE2CE5, 0xD891, 0x4DBB, {0x90, 0x43, 0x6A, 0x03, 0x76, 0x6C, 0x5E, 0x44}};


Helper::Helper() {
    std::cout << "Helper::Helper()" << std::endl;
    refCount = 0;
}

Helper::~Helper() {
	std::cout << "Helper::~Helper()" << std::endl;
}


HRESULT Helper::QueryInterface(const IID& iid, void** object) {

    std::cout << "Helper::QueryInterface" << std::endl;
    
    if (iid == Constants::IID_IUnknown)	{
        *object = (IUnknown*) (IBasicHelper*) this;
    }
    
    else if (iid == Constants::IID_IBasicHelper) {
        *object = static_cast<IBasicHelper*>(this);
    }
    
    else if (iid == Constants::IID_IAdvancedHelper) {
        *object = static_cast<IAdvancedHelper*>(this);
    }
    
    else    {
        *object = NULL;
        return E_NOINTERFACE;
    }

    this -> AddRef();
    return S_OK;
}

ULONG Helper::AddRef() {
    refCount++;
    return refCount;
}

ULONG Helper::Release() {
    refCount--;
    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT __stdcall Helper::GetBinFiles() {
    std::cout << "Helper::GetBinFiles()" << std::endl;
    return S_OK;
}

HRESULT Helper::DeleteBinFiles() {
    std::cout << "Helper::DeleteBinFiles()" << std::endl;
    return S_OK;
}

HRESULT Helper::TurnOffMachine() {
    std::cout << "Helper::TurnOffMachine()" << std::endl;
    return S_OK;
}

//-------------------------ClassFactory begins--------------------------------------

HelperClassFactory::HelperClassFactory() {
    std::cout << "HelperClassFactory::HelperClassFactory()" << std::endl;
    this -> refCount = 0;
}

HelperClassFactory::~HelperClassFactory() {
    std::cout << "HelperClassFactory::~HelperClassFactory()" << std::endl;
}


HRESULT HelperClassFactory::QueryInterface(const IID& iid, void** object) {
    std::cout <<" HelperClassFactory::QueryInterface()" << std::endl;

    if (iid == Constants::IID_IClassFactory)
    {
        *object = (IUnknown*) (IClassFactory*) this;
    }
    else if (iid == Constants::IID_IHelperClassFactory)
    {
        *object = (IUnknown*) (IHelperClassFactory*) this;
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }
    
    this -> AddRef();
    return S_OK;
}

ULONG HelperClassFactory::AddRef()
{
    refCount++;
    return refCount;
}

ULONG HelperClassFactory::Release()
{
    refCount--;

    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT HelperClassFactory::LockServer(BOOL bLock) {
    std::cout << "HelperClassFactory::LockServer()" << std::endl;
    return S_OK;
}

HRESULT HelperClassFactory::CreateInstance(IUnknown* pUnknownOuter,const IID& iid, void** object)
{
    std::cout << "HelperClassFactory::CreateInstance()" << std::endl;
    
   if (pUnknownOuter!=NULL)    {
      return E_NOTIMPL;
   };

    HRESULT res = S_OK;

    Helper* helper = new Helper();

    res = helper -> QueryInterface(iid, object);
}

HRESULT HelperClassFactory::CreateInstance(const IID& iid, void** object, int password)
{
    std::cout << "HelperClassFactory::CreateInstance(password)" << std::endl;
    
    HRESULT res = S_OK;

    Helper* helper = new Helper();

    res = helper -> QueryInterface(iid, object);

    
    return res;
}

