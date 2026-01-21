#include <iostream>
#include <memory>
#include "Tableau.h"

int main()
{
    try 
    {
        auto tableau = std::make_unique<Tableau>();
        tableau->executer();
        return 0;
    } 
    catch(const exception& e) 
    {
        std::cerr << "ERR: " << e.what() << std::endl;
        return 1;
    } 
    catch(...) 
    {
        std::cerr << "ERR: E999" << std::endl;
        return 2;
    }
}