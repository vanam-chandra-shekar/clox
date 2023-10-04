#include "Scanner.h"
#include "Clox.h"
#define null "null"



std::vector<Token> Scanner::scantokens()
{
    while(!isatend())
    {
        start = current;
        scantoken();
    }

    m_Tokens.emplace_back(LOF,null,null,line);

    return m_Tokens;
}

bool Scanner::isatend()
{
    return current >= m_Source.length();
}

char Scanner::advance()
{
    return m_Source.at(current++);
}

void Scanner::addToken(TokenType type, const std::string &literal)
{
    std::string text = m_Source.substr(start,(current-start));
    m_Tokens.emplace_back(type,text,literal,line);
}

bool Scanner::match(char expected)
{
    if(isatend()) return false;
    if(m_Source.at(current) != expected) return false;

    current++;
    return true;
}

char Scanner::peek()
{
    if(isatend()) return '\0';
    return m_Source.at(current);
}

char Scanner::peeknext()
{
    if(current+1 >= m_Source.length()) return '\0';
    return m_Source.at(current+1);
}

void Scanner::string()
{
    while (peek() != '"' && !isatend())
    {
        if(peek()=='\n') line++;
        advance();
    }

    if(isatend())
    {
        Clox::getinstance().error(line,"Undeterminated String");
    }

    advance();

    std::string value = m_Source.substr(start+1,(current-start)-2);
    addToken(STRING,value);
    
}

void Scanner::number()
{
    while (std::isdigit(peek())) advance();

    if(peek() == '.' && std::isdigit(peeknext()))
    {   
        //consume
        advance();

        while(std::isdigit(peek())) advance();
    }


    addToken(NUMBER,std::to_string(std::stod(m_Source.substr(start,(current-start)))));
    
}

void Scanner::identifier()
{
    while(std::isalnum(peek()) || peek() == '_') advance();

    std::string text = m_Source.substr(start,(current-start));
    TokenType type;

    if(keywords.find(text) == keywords.end())
    {
        type = IDENTIFIER;
    }
    else
    {
        type = keywords[text];
    }

    addToken(type);

}

void Scanner::addToken(TokenType t)
{
    addToken(t,null);
}



void Scanner::scantoken()
{
    char c = advance();
    switch (c)
    {
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;
        case '{': addToken(LEFT_BRACE); break;
        case '}': addToken(RIGHT_BRACE); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break;

        case '!':
            addToken( match('=') ? BANG_EQUAL : BANG );
            break;
        case '=':
            addToken( match('=') ? EQUAL_EQUAL : EQUAL );
            break;
        case '<':
            addToken( match('=') ? LESS_EQUAL : LESS );
            break;
        case '>':
            addToken( match('=') ? GREATER_EQUAL : GREATER );
            break;

        case '/':
            if(match('/'))
            {
                while (peek() != '\n' && !isatend()) advance();
            }else{
                addToken(SLASH);
            }
            break;

        case ' ':
        case '\r':
        case '\t':
            //ignoring white spaces
            break;
        
        case '\n':
            line++;
            break;

        case '"': string(); break;

        default:
            if(std::isdigit(c))
            {
                number();
            }
            else if(std::isalpha(c) || c=='_' )
            {
                identifier();
            }
            else{
                Clox::getinstance().error(line,"Unexpected character");
                break;
            }
    }
}