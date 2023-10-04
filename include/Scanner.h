#pragma once
#include <vector>
#include <map>
#include "Token.h"

class Scanner
{
    private:
        int start = 0;
        int current = 0;
        int line = 1;

        std::string m_Source;
        std::vector<Token> m_Tokens;

        std::map <std::string , TokenType> keywords = 
        {
            {"and",    AND},
            {"class",  CLASS},
            {"else",   ELSE},
            {"false",  FALSE},
            {"for",    FOR},
            {"fun",    FUN},
            {"if",     IF},
            {"nil",    NIL},
            {"or",     OR},
            {"print",  PRINT},
            {"return", RETURN},
            {"super",  SUPER},
            {"this",   THIS},
            {"true",   TRUE},
            {"var",    VAR},
            {"while",  WHILE}
        };

    public:
        Scanner(std::string source)
            :m_Source(source){}
        
        std::vector <Token> scantokens();
    
    private:
        void scantoken();
        void addToken(TokenType type);
        bool isatend();
        char advance();
        void addToken(TokenType type, const std::string& literal);
        bool match(char expected);
        char peek();
        char peeknext();
        void string();
        void number();
        void identifier();
};