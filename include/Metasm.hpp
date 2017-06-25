#pragma once

#include <libgccjit++.h>

#include <vector>
#include <stack>

#include <functional>
#include <utility>
#include <sstream>
#include <unordered_map>
#include <cmath>

#define INST_PUSH    0x01
#define INST_POP     0x02
#define INST_SWAP    0x03
#define INST_DUP     0x04
#define INST_ADD     0x05
#define INST_SUB     0x06
#define INST_MUL     0x07
#define INST_DIV     0x08
#define INST_XOR     0x09
#define INST_OR      0x0A
#define INST_AND     0x0B
#define INST_NOT     0x1C
#define INST_SHR     0x1D
#define INST_SHL     0x1E
#define INST_LBL     0x1F
#define INST_JMP     0x10
#define INST_JE      0x11
#define INST_JNE     0x12
#define INST_JGE     0x13
#define INST_JLE     0x14

namespace meta
{

class Engine
{
    public:
        Engine  ( unsigned int _maxStackDepth );
        ~Engine ();

        void                        init_blocks();

        bool                        is_valid     ( const std::string& _script );
        void                        load_script  ( const std::string& _script );
        void                        compile      ();
        int                         execute      ();

    private:

        void                        push        ( gccjit::rvalue _arg );
        void                        pop         ( gccjit::lvalue _arg );

        std::vector<std::string>    split       ( const std::string& _script, const char& _delim );
        unsigned int                scan        ( const std::string& );
        void                        parse_labels();

        std::string                 m_script;

        gccjit::context             m_context;
        gccjit::type                m_int_type,
                                    m_stack_type,
                                    m_void_type,
                                    m_void_ptr_type;
        std::vector<gccjit::param>  m_params;
        gccjit::function            m_function;

        gcc_jit_result*             m_result;
        
        gccjit::lvalue              m_stack,
                                    m_stack_depth,
                                    m_x,
                                    m_y,
                                    m_ret;
        gccjit::rvalue              m_const_one;

        gccjit::block               m_initial_block;
        gccjit::block               m_actual_block, m_next_block;
        bool                        m_valid_next = true;
        
        std::unordered_map< std::string, unsigned int >
                                    m_labels;
        std::vector<gccjit::block>  m_instruction_blocks;
        
        std::vector<std::string>    m_ops;
};

}