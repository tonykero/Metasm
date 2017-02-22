#include <Metasm.hpp>

using namespace meta;

Engine::Engine()
{
    m_instructions["PUSH"]  = [this]( const std::string& _str ){ push( atoi(_str.c_str()) );};
    m_instructions["POP"]   = [this]( const std::string& _str ){ pop();             };
    m_instructions["SWAP"]  = [this]( const std::string& _str ){ swap();            };
    m_instructions["DUP"]   = [this]( const std::string& _str ){ dup();             };
    m_instructions["ADD"]   = [this]( const std::string& _str ){ add();             };
    m_instructions["MUL"]   = [this]( const std::string& _str ){ mul();             };
    m_instructions["DIV"]   = [this]( const std::string& _str ){ div();             };
    m_instructions["NAND"]  = [this]( const std::string& _str ){ nand();            };
    m_instructions["SHF"]   = [this]( const std::string& _str ){ shf();             };
    // m_instructions["LBL"]   = [this]( const std::string& _str ){ lbl( _str );       };
    m_instructions["CMP"]   = [this]( const std::string& _str ){ cmp();             };
    m_instructions["JMP"]   = [this]( const std::string& _str ){ jmp( _str );       };
    m_instructions["JE"]    = [this]( const std::string& _str ){ je( _str );        };
    m_instructions["JNE"]   = [this]( const std::string& _str ){ jne( _str );       };
    m_instructions["JGE"]   = [this]( const std::string& _str ){ jge( _str );       };
    m_instructions["JLE"]   = [this]( const std::string& _str ){ jle( _str );       };
}

Engine::~Engine()
{

}

bool Engine::isValid( const std::string& _script )
{
    //TODO: isValid()
    return true;
}

void Engine::loadScript( const std::string& _script )
{
    if(isValid(_script))
    {
        m_script = _script;
        parseLabels();
    }
}

void Engine::run( )
{
    std::vector<std::string> lines = split(m_script, '\n');

    for(m_ip = 0; m_ip < lines.size(); m_ip++)
    {
        std::vector<std::string> args = split(lines[m_ip], ' ');
        std::string arg = "\0";

        if(args.size() > 1)
            arg = args[1];
        if(args[0] != "LBL")
            m_instructions[ args[0] ](arg);
    }
}

const std::stack<int>& Engine::getStack() const
{
    return m_stack;
}

// Instructions
void Engine::push( int _arg )
{
    m_stack.push( _arg );
}

void Engine::pop()
{
    m_stack.pop();
}

void Engine::swap()
{
    std::pair<int, int> ab = poplast2();
            
    m_stack.push(ab.first);
    m_stack.push(ab.second);
}

void Engine::dup()
{
    m_stack.push( m_stack.top() );
}

void Engine::add()
{
    std::pair<int, int> ab = poplast2();

    m_stack.push( ab.first + ab.second );
}

void Engine::mul()
{
    std::pair<int, int> ab = poplast2();

    m_stack.push( ab.first * ab.second );
}

void Engine::div()
{
    std::pair<int, int> ab = poplast2();

    m_stack.push( ab.first / ab.second );
}

void Engine::nand()
{
    std::pair<int, int> ab = poplast2();

    int r = ab.first & ab.second;
    m_stack.push( ~r );
}

void Engine::shf()
{
    std::pair<int, int> ab = poplast2();

    if(ab.first >= 0)
        m_stack.push(ab.second >> ab.first);
    else if(ab.first < 0)
        m_stack.push(ab.second << std::abs(ab.first));
}

void Engine::cmp()
{
    std::pair<int, int> ab = poplast2();
    m_stack.push(ab.second);
    m_stack.push(ab.first);

    if(ab.first > ab.second)
    {
        isGreater   = true;
        isLower     = false;
        isEqual      = false;
    }
    else if(ab.first == ab.second)
    {
        isEqual     = true;
        isLower     = false;
        isGreater   = false;
    }
    else
    {
        isLower     = true;
        isEqual     = false;
        isGreater   = false;
    }
}

void Engine::jmp( const std::string& _label )
{
   m_ip= m_labels[ _label ];
}

void Engine::je( const std::string& _label )
{
    if(isEqual)
       m_ip= m_labels[ _label ];
}

void Engine::jne( const std::string& _label )
{
    if(!isEqual)
       m_ip= m_labels[ _label ];
}

void Engine::jge( const std::string& _label )
{
    if(isGreater || isEqual)
       m_ip= m_labels[ _label ];
}

void Engine::jle( const std::string& _label )
{
    if(isLower ||isEqual)
       m_ip= m_labels[ _label ];
}

std::pair<int, int> Engine::poplast2()
{
    std::pair<int, int> ab;
    ab.first    =   m_stack.top();
                    m_stack.pop();
    ab.second   =   m_stack.top();
                    m_stack.pop();

    return ab;
}

std::vector<std::string> Engine::split( const std::string& _script, const char& _delim )
{
    std::stringstream           ss(_script);
    std::vector<std::string>    ret;
    std::string                 word;

    while(std::getline(ss, word, _delim))
        ret.push_back(word);
    
    return ret;
}

void Engine::parseLabels()
{
    std::vector<std::string> lines = split(m_script, '\n');
    
    for(unsigned int i = 0; i < lines.size(); i++)
    {
        std::vector<std::string> words = split(lines[i], ' ');
        if(words[0] == "LBL")
            m_labels[ words[1] ] = i;
    }
}
