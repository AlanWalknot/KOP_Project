#include <iostream>
#include "wrapper.h"

int main() {
    std::cout << "CLIENT MAIN START" << std::endl;
    
    try
    {
        std::cout<<"STANDARD CLASS FACTORY"<<std::endl;
        CHelper c;

        c.GetBinFiles();
        c.DeleteBinFiles();
        c.TurnOffMachine();
        c.GetUnusedPrograms();
    }
    catch(EHelper& e)
    {
        std::cout << e.GetMessage() << std::endl;
    }
    
    return 0;
}