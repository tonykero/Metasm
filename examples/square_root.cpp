#include <Metasm.hpp>
#include <iostream>

using namespace std;

int main()
{
    meta::Engine engine(4);

     //square_root
    std::string script = 
                    "PUSH 512\n"      //8
                    "DUP\n"         //8 8
                    "PUSH 1024\n"       //8 8 16
                    "DIV\n"         //8 2
                    "PUSH 512\n"      //8 2 8
                    "LBL L1\n"      //          5 5 3       
                    "ADD\n"         //8 10      5 8         
                    "PUSH 2\n"      //8 10 1    5 9 1     
                    "SWAP\n"         //8 5       5 5         
                    "DIV\n"
                    "JE EXIT\n"     //                      
                    "SWAP\n"        //5 8       
                    "POP\n"         //5         
                    "DUP\n"         //5 5       
                    "DUP\n"         //5 5 5     
                    "PUSH 1024\n"     //5 5 5 16  
                    "DIV\n"         //5 5 3     
                    "JNE L1\n"      //                      
                    "LBL EXIT\n"    //                      
                    "POP\n";        //
                    

    engine.load_script(script);
    engine.compile();
    std::cout << engine.execute() << std::endl;
}