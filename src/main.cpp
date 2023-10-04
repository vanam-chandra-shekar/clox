#include <iostream>
#include "Clox.h"

int main(int argc , char* argv[])
{
    Clox& clox = Clox::getinstance();
    if(argc >2)
    {
        std::cout<<"Usage: jlox [script]";
        exit(EXIT_FAILURE);
    }
    else if(argc == 2)
    {
        clox.runFile(argv[1]);
    }
    else
    {
        clox.runpromt();
    }
}