#pragma once
#include <string>

class Clox
{
    public:
        Clox(const Clox& ) = delete;
        Clox(){};
        void runFile(const std::string& path);
        void runpromt();
        void error(const int& line , const std::string& message){report(line,"",message);}

        static Clox& getinstance();

    private:
        bool haderror = false;

        static Clox m_instance;

        void run(const std::string& source);
        void report(const int& line ,const std::string& where , const std::string& message);

};