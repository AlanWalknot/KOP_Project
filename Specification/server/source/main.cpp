#include "component.h"

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object)
{
    std::cout << "Export Function: GetClassObject()" << std::endl;

    IUnknown* s = NULL;

    if (clsid == Constants::CLSID_Helper)
    {
        s = (IUnknown*) (IClassFactory*) new HelperClassFactory();
    }
    else
    {
        *object = NULL;
        return E_NOTIMPL;
    }

    s -> AddRef();
    HRESULT res = s->QueryInterface(iid, object);
    s -> Release();
    
    return S_OK;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            
            break;

        case DLL_PROCESS_DETACH:
            
            break;

        case DLL_THREAD_ATTACH:
            
            break;

        case DLL_THREAD_DETACH:
            
            break;
    }
    return TRUE;
}