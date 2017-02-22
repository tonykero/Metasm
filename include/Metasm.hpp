#pragma once

#include <unordered_map>
#include <vector>
#include <stack>

#include <functional>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <cmath>

namespace meta
{

class Engine
{
    public:
        Engine  ();
        ~Engine ();

        bool                        isValid     ( const std::string& _script );
        void                        loadScript  ( const std::string& _script );
        void                        run         ();

        const std::stack<int>&      getStack    () const;

        void                        push        ( int _arg );
        void                        pop         ();
        void                        swap        ();
        void                        dup         ();
        void                        add         ();
        void                        mul         ();
        void                        div         ();
        void                        nand        ();
        void                        shf         ();
        // void                        lbl         ( const std::string& _label );
        void                        cmp         ();
        void                        jmp         ( const std::string& _label );
        void                        je          ( const std::string& _label );
        void                        jne         ( const std::string& _label );
        void                        jge         ( const std::string& _label );
        void                        jle         ( const std::string& _label );

    private:
        std::pair<int, int>         poplast2    ();
        std::vector<std::string>    split       ( const std::string& _script, const char& _delim );
        void                        parseLabels ();


        std::unordered_map<std::string, std::function<void(const std::string&)>> m_instructions;
        
        std::unordered_map<std::string, unsigned int>   m_labels;
        std::stack<int>                                 m_stack;
        std::string                                     m_script;
        unsigned int                                    m_ip = 0;

        bool    isEqual     = false,
                isLower     = false,
                isGreater   = false;
};

}