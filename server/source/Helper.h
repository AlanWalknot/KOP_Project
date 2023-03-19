#include "IHelper.h"

class Helper : public IClearBin, public IBinInfo {
    private:
    int fRefCount;

    public:
    Helper();
    ~Helper();
    virtual HRESULT_ __stdcall QueryInterface(const int& iid, void** ppv);
    virtual ULONG_ __stdcall AddRef();
    virtual ULONG_ __stdcall Release();

    virtual HRESULT_ __stdcall GetFiles();
    virtual HRESULT_ __stdcall GetWeight();

    virtual HRESULT_ __stdcall ClearBin();
};