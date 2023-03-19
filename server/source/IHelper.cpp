#include "Helper.h"

HRESULT_ __stdcall CreateInstance_(const CLSID_& clsid, const IID_& iid, void** object){
    
    std::cout <<"IHelper::CreateHelper()" << std::endl;
    IUnknown_* helper = NULL;

    if(clsid == CLSID_CHelper) {
        helper = (IUnknown_*)(IClearBin*) new Helper();
    }
    else {
        *object = NULL; 
        return E_NOCOMPONENT_;
    }

    helper -> AddRef();
    HRESULT_ res = helper -> QueryInterface(iid, object);
    helper -> Release();
    
    return res;

}  