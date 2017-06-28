namespace insts
{
    TEST_CASE("Instructions Tests", "[intructions]" )
    {
        meta::Engine engine(4);

        std::string script;
        std::function<int(void)> function;

        SECTION("Memory")
        {
            script = 
                "PUSH 2\n"
                "PUSH 3\n"
                "POP\n"         // 2
                "STORE R1\n"
                "PUSH 4\n"      // 4
                "LOAD R1\n"     // 4 2
                "SWAP\n"        // 2 4
                "DUP\n"         // 2 4 4
                "SWAP\n";       // 2 4 4
            
            engine.load_script(script);
            function = engine.compile();

            REQUIRE( function() == 4 );
        }
        SECTION("Arithmetic")
        {
            
            script =
                "PUSH 4\n"
                "PUSH 3\n"
                "MUL\n"     // 12
                "PUSH 2\n"
                "ADD\n"     // 14
                "PUSH 20\n"
                "SUB\n"     // 6
                "PUSH 3\n"
                "SWAP \n"
                "DIV\n"     // 2
                "PUSH 2\n"
                "MOD\n";    // 0

            engine.load_script( script );
            function = engine.compile();

            REQUIRE( function() == 0);
        }
        SECTION("Logical")
        {

            script =
                "PUSH 47\n"
                "PUSH 16\n"
                "XOR\n"     // 63
                "PUSH 5\n"
                "AND\n"     // 5
                "PUSH 20\n"
                "OR\n"      // 21
                "PUSH 2\n"
                "SWAP\n"
                "SHL\n"     // 84
                "PUSH 3\n"
                "SWAP\n"
                "SHR\n";    // 10

            engine.load_script( script );
            function = engine.compile();

            REQUIRE( function() == 10 );
        }
        SECTION("Jumps")
        {

            script =
                "PUSH 1\n"  
                "JMP L2\n"  
                "LBL L1\n"          // 1 43  
                "PUSH 43\n"         // 1 43 43
                "JE L3\n"
                "LBL L2\n"  // 1
                "PUSH 43\n" // 1 43
                "JGE L1\n"
                "LBL L3\n"          // 1 43 43
                "SUB\n"             // 1 0
                "JLE L4\n"        
                "LBL L5\n"                      // 1 0
                "PUSH 1\n"                      // 1 0 1
                "JMP END\n"
                "LBL L4\n"          // 1 0
                "JNE L5\n"
                "LBL END\n";                     // 1 0 1

            engine.load_script( script );
            function = engine.compile();

            REQUIRE( function() == 1 );
        }
    }
}