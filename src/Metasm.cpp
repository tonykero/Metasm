#include <Metasm.hpp>

using namespace meta;

Engine::Engine( unsigned int _maxStackDepth )
:m_context      ( gccjit::context::acquire() ),
m_int_type      ( m_context.get_type( GCC_JIT_TYPE_INT )),
m_stack_type    ( m_context.new_array_type( m_int_type, _maxStackDepth )),
m_void_type     ( m_context.get_type( GCC_JIT_TYPE_VOID ) ),
m_void_ptr_type ( m_context.get_type( GCC_JIT_TYPE_VOID_PTR ) ),
m_params        { },
m_function      ( m_context.new_function( GCC_JIT_FUNCTION_EXPORTED, m_int_type, "main", m_params, 1)),
m_print         ( m_context.get_builtin_function( "printf" )),
m_stack         ( m_function.new_local( m_stack_type, "stack" )),
m_stack_depth   ( m_function.new_local( m_int_type, "stack_depth" )),
m_x             ( m_function.new_local( m_int_type, "x" )),
m_y             ( m_function.new_local( m_int_type, "y" )),
m_ret           ( m_function.new_local( m_int_type, "ret" )),
m_const_one     ( m_context.one(m_int_type)),
m_initial_block ( m_function.new_block("initial"))
{
    //m_context.set_bool_option   (GCC_JIT_BOOL_OPTION_DUMP_GENERATED_CODE, 0);
    m_context.set_int_option    (GCC_JIT_INT_OPTION_OPTIMIZATION_LEVEL, 3);

}

Engine::~Engine()
{
    m_context.release();
    gcc_jit_result_release( m_result );
}

void Engine::init_blocks()
{
    for(unsigned int i = 0; i < m_ops.size(); i++)
    {
        m_instruction_blocks.push_back( m_function.new_block( std::string( "insn" ) +
                                        std::to_string(i) ));
    }

    m_initial_block.add_assignment( m_stack_depth, m_context.zero( m_int_type ) );
    m_initial_block.end_with_jump( m_instruction_blocks[0] );
}

bool Engine::is_valid( const std::string& _script )
{
    //TODO: isValid()
    return true;
}

void Engine::load_script( const std::string& _script )
{
    if(is_valid(_script))
    {
        m_script = _script;
    
        std::vector<std::string> lines = split(m_script, '\n');
        m_ops = lines;

        init_blocks();
        parse_labels();
    }
}

std::function<int(void)> Engine::compile( )
{
    for(unsigned int i = 0; i < m_ops.size(); i++)
    {
        std::vector<std::string> args = split(m_ops[i], ' ');
        std::string arg;
    
        // assign argument
        if(args.size() > 1)
            arg = args[1];
        
        m_actual_block  = m_instruction_blocks[i];
        if(i < m_ops.size()-1)
            m_next_block = m_instruction_blocks[i + 1];
        else
            m_valid_next = false;

        unsigned int instruction_id = scan( args[0] );
        switch( instruction_id )
        {
            // memory
            case INST_PUSH:
                push( m_context.new_rvalue( m_int_type, std::stoi( args[1] ) ));
                break;
            case INST_POP:
                m_actual_block.add_assignment_op( m_stack_depth, GCC_JIT_BINARY_OP_MINUS, m_const_one );
                break;
            case INST_SWAP:
                pop(m_x);
                pop(m_y);
                push(m_x);
                push(m_y);
                break;
            case INST_DUP:
                pop(m_x);
                push(m_x);
                push(m_x);
                push(m_x);
                break;
            // arithmetic
            case INST_ADD:
                pop(m_x);
                pop(m_y);
                push(m_x + m_y);
                break;
            case INST_SUB:
                pop(m_x);
                pop(m_y);
                push(m_x - m_y);
                break;
            case INST_MUL:
                pop(m_x);
                pop(m_y);
                push(m_x * m_y);
                break;
            case INST_DIV:
                pop(m_x);
                pop(m_y);
                push(m_x / m_y);
                break;
            case INST_MOD:
                pop(m_x);
                pop(m_y);
                push(m_x % m_y);
            // logical
            case INST_XOR:
                pop(m_x);
                pop(m_y);
                push(m_x ^ m_y);
                break;
            case INST_OR:
                pop(m_x);
                pop(m_y);
                push(m_x | m_y);
                break;
            case INST_AND:
                pop(m_x);
                pop(m_y);
                push(m_x & m_y);
                break;
            case INST_NOT:
                pop(m_x);
                push(~m_x);
                break;
            case INST_SHR:
                pop(m_y);
                pop(m_x);
                push( m_context.new_binary_op(GCC_JIT_BINARY_OP_RSHIFT, m_int_type, m_x, m_y));
                break;
            case INST_SHL:
                pop(m_y);
                pop(m_x);
                push( m_context.new_binary_op(GCC_JIT_BINARY_OP_LSHIFT, m_int_type, m_x, m_y));
                break;
            // jumps
            case INST_LBL:
                // do nothing
                break;
            case INST_JMP:
                m_actual_block.end_with_jump( m_instruction_blocks[ m_labels[arg] ] );
                break;
            case INST_JE:
                pop(m_x);
                pop(m_y);
                push(m_y);
                push(m_x);
                m_actual_block.end_with_conditional( m_x == m_y, m_instruction_blocks[ m_labels[arg] ], m_next_block );
                break;
            case INST_JNE:
                pop(m_x);
                pop(m_y);
                push(m_y);
                push(m_x);
                m_actual_block.end_with_conditional( m_x != m_y, m_instruction_blocks[ m_labels[arg] ], m_next_block );
                break;
            case INST_JGE:
                pop(m_x);
                pop(m_y);
                push(m_y);
                push(m_x);
                m_actual_block.end_with_conditional( m_x >= m_y, m_instruction_blocks[ m_labels[arg] ], m_next_block );
                break;
            case INST_JLE:
                pop(m_x);
                pop(m_y);
                push(m_y);
                push(m_x);
                m_actual_block.end_with_conditional( m_x <= m_y, m_instruction_blocks[ m_labels[arg] ], m_next_block );
                break;
            // io
            case INST_PRINT:
                pop(m_x);
                push(m_x);
                m_actual_block.add_eval( m_context.new_call( m_print, m_context.new_rvalue("topmost value: %i\n"), m_x));
                break;
            default:
                // instruction not found, can't be reached
                break;
        }
    
        if( instruction_id != INST_JMP  &&
            instruction_id != INST_JE   &&
            instruction_id != INST_JNE  &&
            instruction_id != INST_JGE  &&
            instruction_id != INST_JLE )
        {
            if(m_valid_next)
                m_actual_block.end_with_jump( m_next_block );
            else
            {
                m_actual_block.add_assignment_op( m_stack_depth, GCC_JIT_BINARY_OP_MINUS, m_const_one);
                m_actual_block.add_assignment( m_ret, m_context.new_array_access( m_stack, m_stack_depth ) );
                m_actual_block.end_with_return( m_ret );
            }
        }
    
    //gccjit::context

    }
    m_result = m_context.compile();

    typedef int (*function)(void);
    function fun = (function)gcc_jit_result_get_code(m_result, "main");
    return fun;
}

void Engine::compile( const std::string& _filename, bool _asm )
{
    m_context.compile_to_file(GCC_JIT_OUTPUT_KIND_EXECUTABLE , _filename.c_str());
    if( _asm )
        m_context.compile_to_file(GCC_JIT_OUTPUT_KIND_ASSEMBLER , std::string(_filename + ".asm").c_str());
}

// Instructions
void Engine::push( gccjit::rvalue _arg )
{
    m_actual_block.add_assignment( m_context.new_array_access( m_stack, m_stack_depth ), _arg );
    m_actual_block.add_assignment_op( m_stack_depth, GCC_JIT_BINARY_OP_PLUS, m_const_one);
}

void Engine::pop( gccjit::lvalue _arg )
{
    m_actual_block.add_assignment_op( m_stack_depth, GCC_JIT_BINARY_OP_MINUS, m_const_one );
    m_actual_block.add_assignment( _arg, m_context.new_array_access( m_stack, m_stack_depth ) );
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

unsigned int Engine::scan( const std::string& _instruction )
{
    unsigned int inst_id = 0x00;
    (_instruction == "PUSH" )   && ( inst_id= INST_PUSH );
    (_instruction == "POP"  )   && ( inst_id= INST_POP  );
    (_instruction == "SWAP" )   && ( inst_id= INST_SWAP );
    (_instruction == "DUP"  )   && ( inst_id= INST_DUP  );
    (_instruction == "ADD"  )   && ( inst_id= INST_ADD  );
    (_instruction == "SUB"  )   && ( inst_id= INST_SUB  );
    (_instruction == "MUL"  )   && ( inst_id= INST_MUL  );
    (_instruction == "DIV"  )   && ( inst_id= INST_DIV  );
    (_instruction == "MOD"  )   && ( inst_id= INST_MOD  );
    (_instruction == "XOR"  )   && ( inst_id= INST_XOR  );
    (_instruction == "OR"   )   && ( inst_id= INST_OR   );
    (_instruction == "AND"  )   && ( inst_id= INST_AND  );
    (_instruction == "NOT"  )   && ( inst_id= INST_NOT  );
    (_instruction == "SHR"  )   && ( inst_id= INST_SHR  );
    (_instruction == "SHL"  )   && ( inst_id= INST_SHL  );
    (_instruction == "LBL"  )   && ( inst_id= INST_LBL  );
    (_instruction == "JMP"  )   && ( inst_id= INST_JMP  );
    (_instruction == "JE"   )   && ( inst_id= INST_JE   );
    (_instruction == "JNE"  )   && ( inst_id= INST_JNE  );
    (_instruction == "JGE"  )   && ( inst_id= INST_JGE  );
    (_instruction == "JLE"  )   && ( inst_id= INST_JLE  );
    (_instruction == "PRINT")   && ( inst_id= INST_PRINT);

    return inst_id;

}

void Engine::parse_labels()
{
    for(unsigned int i = 0; i < m_ops.size(); i++)
    {
        std::vector<std::string> args = split(m_ops[i], ' ');
        std::string arg;

        if( args[0] == "LBL")
            m_labels[args[1]] = i;
    }
}