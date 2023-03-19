#include "lib/IHelper.h"

#include <iostream>

using namespace std;

int main() {
    try {
        cout << "Client::Main()" << endl;

        cout << "Client::CreateInstance()" << endl;
        IClearBin* clearBin = NULL;
        HRESULT_ res = CreateInstance_(CLSID_CHelper, IID_IClearBin, (void**)&clearBin);

        if(res == S_OK_) {
            cout << "Client::Main::Success ClearBin: " << endl;
            clearBin -> ClearBin();
        }
        else {
            cout << "Client::Main::Error CHelper or ClearBin" << endl;
            return 0;
        }

        cout << "Client::Main::QI ClearBin - > BinInfo" << endl;
        IBinInfo* binInfo = NULL;
        res = clearBin -> QueryInterface(IID_IBinInfo, (void**)&binInfo);
        cout << "Client::Main::ClearBin -> Release" << endl;
        clearBin -> Release();

        if(res == S_OK_) {
            cout << "Client::Main::Success IBinInfo" << endl;
            binInfo -> GetFiles();
            binInfo -> GetWeight();
        }
        else {
            cout << "Client::Main::Error IBinInfo: " << res << endl;
        }

        cout << "Client::Main::IBinInfo -> Release" << endl;
        binInfo -> Release();

        cout << "Client::Main::Finish" << endl;
    }
    catch(...) {
        cout << "Client::Main() UNKNOWN ERROR APPEARED ";
        return 0;
    }
};