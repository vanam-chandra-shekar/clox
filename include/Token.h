#pragma once

#include <string>
#include "TokenType.h"

class Token
{
    public:
        TokenType type;
        std::string lexeme;
        std::string literal;
        int line;
    
        Token(const TokenType& Type , const std::string& Lexeme , const std::string& Literal,int Line);
        std::string toString();

};