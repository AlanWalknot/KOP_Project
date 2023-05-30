#include <iostream>
#include <objbase.h>

#include "./lib/interfaces.h"
#include "./lib/interfaces2.h"


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

int main() {
    std::cout << "CLIENT MAIN START" << std::endl;
    
    try {

        CoInitialize(NULL);

    IClassFactory* HelperCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_Helper, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &HelperCF);

    if(!(SUCCEEDED(resFactory))) {
        std::cout << "No factory!" << std::endl;
        throw "No factory!";
    }

    std::cout << "\nCLIENT::WORKING : BASIC HELPER\n\n";

    IBasicHelper* pBH = NULL;
    HRESULT resInstance = HelperCF -> CreateInstance(NULL, Constants::IID_IBasicHelper, (void**)&pBH);

    if(!(SUCCEEDED(resInstance))) {
        std::cout << "No instance!" << std::endl;
        throw "No instance!";
    }


    pBH -> GetBinFiles();

    
    std::cout << "\nCLIENT::WORKING : ADVANCED HELPER\n\n";

    IAdvancedHelper* pAH = NULL;
    HRESULT resQuery = pBH -> QueryInterface(Constants::IID_IAdvancedHelper, (void**) &pAH);
    
    if(!(SUCCEEDED(resQuery))) {
        std::cout << "No query!" << std::endl;
        throw "No query!"; 
    }

    pAH -> DeleteBinFiles();
    pAH -> TurnOffMachine();
    
    std::cout << "\nCLIENT::FINISHING WORK : ADVANCED, BASIC HELPER\n\n";

    pAH -> Release();
    pBH -> Release();

    HelperCF -> Release();
    
    std::cout << "\nCLIENT::WORKING : CREATING EXTRA HELPER\n\n";

    IClassFactory* ExtraHCF = NULL;
    resFactory = CoGetClassObject(Constants2::CLSID_ExtraHelper, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &ExtraHCF);

    if(!(SUCCEEDED(resFactory))) {
        std::cout << "No factory!" << std::endl;
        throw "No factory!";
    }

    IExtraHelper* pEH = NULL;
 
    resInstance = ExtraHCF -> CreateInstance(NULL, Constants2::IID_IExtraHelper, (void**) &pEH);
    
    if(!(SUCCEEDED(resInstance))) {
        std::cout << "No instance!" << std::endl;
        throw "No instance!";
    }

    std::cout << "\nCLIENT::WORKING : EXTRA HELPER\n\n";

    pEH -> GetUnusedPrograms();

    std::cout << "\nCLIENT::FINISHING WORK : EXTRA HELPER\n\n";

    pEH -> Release();

    ExtraHCF -> Release();

    } catch (const char* str) {
         std::cout << "MAIN::ERROR: " << str << std::endl;
    }
    
    catch(...) {
        std::cout << "MAIN::ERROR: UNKOWN ERROR!" << std::endl;
    }

    CoUninitialize();
    
    std::cout << "\nCLIENT::FINISH" << std::endl;
    
    return 0;
}