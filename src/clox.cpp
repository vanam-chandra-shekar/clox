#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Clox.h"
#include "Token.h"
#include "Scanner.h"

Clox Clox::m_instance;

void Clox::runFile(const std::string &path)
{
    std::ifstream file (path);
    std::stringstream source;
    source<<file.rdbuf();

    run(source.str());
    if(haderror) exit(EXIT_FAILURE);
}

void Clox::runpromt()
{
    for(;;)
    {
        std::cout<<"> ";
        std::string line;
        std::getline(std::cin,line);
        if(line.empty() || haderror) break;
        run(line);

        haderror = false;
    }
}

Clox &Clox::getinstance()
{
    return m_instance;
}

void Clox::run(const std::string &source)
{
    Scanner scanner(source);
    std::vector <Token> tokens = scanner.scantokens();

    for(Token token : tokens)
    {
        std::cout<<token.toString()<<std::endl;
    }
}

void Clox::report(const int &line, const std::string &where, const std::string &message)
{
    std::cout<<"[ line "<<line<<" ] Error "<<where<<": "<<message<<"\n";
    haderror = true;
}
