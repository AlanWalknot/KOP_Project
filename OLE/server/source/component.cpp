#include "component.h"

    IID Constants::IID_NULL_ = {0x10000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants::IID_IUnknown = {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants::IID_IClassFactory = {0x00000001,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

    IID Constants::IID_IHelperClassFactory = {0x000000010,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants::IID_IBasicHelper = {0x000000015,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    IID Constants::IID_IAdvancedHelper = {0x000000016,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    //00020400-0000-0000-C000-000000000046
    IID Constants::IID_IDispatch =  {0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    

    //GUID FOR HELPER : {ABEE2CE5-D891-4DBB-9043-6A03766C5E44}
    CLSID Constants::CLSID_Helper = {0xABEE2CE5, 0xD891, 0x4DBB, {0x90, 0x43, 0x6A, 0x03, 0x76, 0x6C, 0x5E, 0x44}};


Helper::Helper() {
    std::cout << "Helper::Helper()" << std::endl;
    refCount = 0;
}

Helper::~Helper() {
	std::cout << "Helper::~Helper()" << std::endl;
}


HRESULT __stdcall Helper::QueryInterface(const IID& iid, void** object) {

    std::cout << "Helper::QueryInterface" << std::endl;
    
    if (iid == Constants::IID_IUnknown)	{
        *object = (IUnknown*) (IBasicHelper*) this;
    }
    
    else if (iid == Constants::IID_IBasicHelper)    {
        *object = static_cast<IBasicHelper*>(this);
    }
    
    else if (iid == Constants::IID_IAdvancedHelper)    {
        *object = static_cast<IAdvancedHelper*>(this);
    }
    else if(iid == Constants::IID_IDispatch) {
        *object = static_cast<IDispatch*> (this);
    }
    
    else    {
        *object = NULL;
        return E_NOINTERFACE;
    }
    
    this -> AddRef();
    return S_OK;
}

ULONG __stdcall Helper::AddRef() {
    refCount++;
    return refCount;
}

ULONG __stdcall Helper::Release() {
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

HRESULT __stdcall  Helper::DeleteBinFiles() {
    std::cout << "Helper::DeleteBinFiles()" << std::endl;
    return S_OK;
}

HRESULT __stdcall  Helper::TurnOffMachine() {
    std::cout << "Helper::TurnOffMachine()" << std::endl;
    return S_OK;
}

//-------------------------IDispatch part begins--------------------------------------

HRESULT __stdcall Helper::GetTypeInfoCount(UINT* pctinfo) {
    std::cout << "Helper::GetTypeInfoCount" << std::endl;
    return S_OK;
}

HRESULT __stdcall Helper::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo) {
    std::cout << "Helper::GetTypeInfo" << std::endl;
}

HRESULT __stdcall Helper::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
                                        LCID lcid, DISPID* rgDispId) {

    std::cout << "Helper::GetIDsOfNames" << std::endl;

    if(cNames != 1) {return E_NOTIMPL;}

    /*Отладочные сообщения
    const wchar_t* src = rgszNames[0];
    char* dest = new char[32];
    wcstombs(dest,src,32);
    printf(dest); printf("\n");
    */

   if(wcscmp(rgszNames[0], L"GetBinFiles")==0) {
        rgDispId[0] = 1;
   }

   else if(wcscmp(rgszNames[0], L"DeleteBinFiles")==0) {
        rgDispId[0] = 2;
   }

   else if(wcscmp(rgszNames[0], L"TurnOffMachine")==0) {
        rgDispId[0] = 3;
   }

   else {
    return E_NOTIMPL;
   }

   return S_OK;

    }

HRESULT _stdcall Helper::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,WORD wFlags, DISPPARAMS* pDispParams,VARIANT* pVarResult,
                             EXCEPINFO* pExcepInfo, UINT* puArgErr) {

    std::cout << "Helper::Invoke" << std::endl;

    if(dispIdMember == 1) {
        
        /*if(wFlags == DISPATCH_PROPERTYGET) {
            if(pVarResult != NULL) {
                pVarResult -> vt = VT_BSTR;
                pVarResult -> bstrVal = GetBinFiles();
            }
        }*/
        GetBinFiles();

    }

    else if (dispIdMember == 2) {
        DeleteBinFiles();
    }

    else if (dispIdMember == 3) {
        TurnOffMachine();
    }

    else {
        return E_NOTIMPL;
    }
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

HRESULT HelperClassFactory::LockServer(BOOL bLock) {
    std::cout << "HelperClassFactory::LockServer()";
    return S_OK;
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

HRESULT HelperClassFactory::CreateInstance(IUnknown* pUnknownOuter,const IID& iid, void** object)
{
    std::cout << "HelperClassFactory::CreateInstance()" << std::endl;
    
    IUnknown* s = (IUnknown*) (IBasicHelper*) new Helper();

    s -> AddRef();
    HRESULT res = s->QueryInterface(iid, object);
    s -> Release();
    
    return res;
}

HRESULT HelperClassFactory::CreateInstance(const IID& iid, void** object, int password)
{
    std::cout << "HelperClassFactory::CreateInstance(password)" << std::endl;
    
    HRESULT res = E_NOTIMPL;

    if (password == !NULL)
    {
        IUnknown* s = (IUnknown*) (IBasicHelper*) new Helper();

        s -> AddRef();
        res = s -> QueryInterface(iid, object);
        s -> Release();
    }
    
    return res;
}