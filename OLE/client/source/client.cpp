#include <iostream>
#include <objbase.h>
#include <stdio.h>
#include <windows.h>

#include "lib/interfaces.h"
#include "lib/interfaces2.h"


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


int main() {
    
    std::cout << "client::main" << std::endl;

    try {
    
    CoInitialize(NULL);

    CLSID CLSID_Helper;
    CLSID CLSID_ExtraHelper;
    {
    
        const wchar_t* progID = L"Helper";
        
        HRESULT resCLSID_ProgID = CLSIDFromProgID(progID, &CLSID_Helper);

        if(!(SUCCEEDED(resCLSID_ProgID))) {
            throw "No CLSID form ProgID";
        }
        
        else {
            std::cout << "CLSID form ProgID OK!" << std::endl;
        }
    }

    IClassFactory* pCF = NULL;

    HRESULT resFactory = CoGetClassObject(CLSID_Helper, CLSCTX_INPROC_SERVER, NULL,
                                         Constants::IID_IClassFactory, (void**)&pCF);
    if(!(SUCCEEDED(resFactory))) throw "No factory";

    IBasicHelper* pBH = NULL;
    HRESULT resInstance = pCF -> CreateInstance(NULL, Constants::IID_IBasicHelper, (void**)&pBH);
    if(!(SUCCEEDED(resInstance))) throw "No instance";

    pBH -> GetBinFiles();

    IAdvancedHelper* pAH = NULL;
    HRESULT resQuery = pBH -> QueryInterface(Constants::IID_IAdvancedHelper, (void**)&pAH);
    if (!(SUCCEEDED(resQuery))) throw "No query";

    pAH -> DeleteBinFiles();

    IAdvancedHelper* pAH2 = pAH;
    pAH2 -> AddRef();
    pAH2 -> TurnOffMachine();
    pAH2 -> Release();

    //------------Dispatch part begin---------------
    IDispatch* pDisp = NULL;
    HRESULT resQueryDisp = pBH -> QueryInterface(Constants::IID_IDispatch, (void**)&pDisp);
    if(!(SUCCEEDED(resQueryDisp))) throw "No query dispatch";

    DISPID dispid;

    int namesCount = 1;
    OLECHAR** names = new OLECHAR*[namesCount];
    OLECHAR* name = const_cast<OLECHAR*>(L"DeleteBinFiles");
    names[0] = name;

    HRESULT resID_Name = pDisp -> GetIDsOfNames(
                                                    Constants::IID_NULL_,
                                                    names,
                                                    namesCount,
                                                    GetUserDefaultLCID(),
                                                    &dispid
    );

    if(!(SUCCEEDED(resID_Name))) {
        std::cout << "No ID of name " << std::endl;
    }
    else {
        DISPPARAMS dispparamsNoArgs = {
                                        NULL,
                                        NULL,
                                        0,
                                        0,
                                       };

        HRESULT resInvoke = pDisp -> Invoke(
                                                dispid,
                                                Constants::IID_NULL_,
                                                GetUserDefaultLCID(),
                                                DISPATCH_METHOD,
                                                &dispparamsNoArgs,
                                                NULL,
                                                NULL,
                                                NULL
                                            );

        if(!(SUCCEEDED(resInvoke))) {
            std::cout << "Invoke error!" << std::endl;
        }
    }

    pDisp -> Release();

    pAH -> Release();
    pBH -> Release();
    pCF -> Release();


    }
    catch(const char* str) {
        std::cout << "Main::Error: " << str << std::endl;
    }

    CoUninitialize();

    std::cout << "Main::Finish" << std::endl;
    return 0;
}