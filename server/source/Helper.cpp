#include "Helper.h"

Helper::Helper() {
    std::cout << "Helper::Helper()" << std::endl; //Create constructor
}

Helper::~Helper() {
    std::cout << "Helper::~Helper()" << std::endl; //Create destructor
}

HRESULT_ Helper::QueryInterface(const IID_& iid, void** object) {
    std::cout << "Helper::QueryInterfac()" << std::endl;

    if(iid == IID_IUnknown_) *object = (IUnknown_*)(IBinInfo*)this;
    else if (iid == IID_IBinInfo) *object = static_cast<IBinInfo*>(this);
    else if (iid == IID_IClearBin) *object = static_cast<IClearBin*>(this);
    else {
        *object = NULL;
        return E_NOCOMPONENT_;
    }
    this -> AddRef();
    return S_OK_;

}

ULONG_ __stdcall Helper::AddRef()
{
   std::cout << "Helper::AddRef" << std::endl;
   fRefCount++;
   std::cout << "Current references: " << fRefCount << std::endl;
   return fRefCount;
}

ULONG_ __stdcall Helper::Release() {
    std::cout << "Helper::Release()" << std::endl;
    fRefCount--;
    std::cout << "Current references: " << fRefCount << std::endl;

    if(fRefCount == 0) {
        std::cout << "Self-destructing..." << std::endl;
        delete this;
        std::cout << "Self-destructing...OK" << std::endl;
    } 
    return fRefCount;
}

HRESULT_ Helper::GetFiles() {
    std::cout << "Helper::GetFiles()" << std::endl;
}

HRESULT_ Helper::GetWeight() {
    std::cout << "Helper::GetWeight()" << std::endl;
}

HRESULT_ Helper::ClearBin() {
    std::cout << "Helper::ClearBin()" << std::endl;
}

