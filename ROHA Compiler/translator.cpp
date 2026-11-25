#include <iostream>
#include "lexer_h.hpp"
#include <sstream>

//this function should be moved - file may also be shifted to somewhere else
std::string Token_to_Assembly(std::vector<Token> tokens) {
    std::stringstream output;
    output << "default rel\nglobal main\n\nsection .text \nmain:\n";
    for(int i = 0; i < tokens.size()-2; i++){
        if (tokens[i].repr == RETURN.repr){
            if (tokens[i+1].type == TokenType::NUM ){
                if (tokens[i+2].repr == SEMICOLON.repr){
                    output << "    mov eax, " << tokens[i+1].repr << std::endl;
                }

            }
            
        }
    }
    output << "    ret";  
    return output.str();
    
}

int main(int argc, char* argv[]){
    //handling the rohafile input
    std::ifstream rohafile;
    if (argc != 2){ //later on, the file will be handled on its own and the argument should be 1
        std::cout << "Incorrect file argument" << std::endl;
        return EXIT_FAILURE;
    }
    std::string roha_filename = argv[1];  //this will be used to name the .asm file properly
    std::string filetype;

    for (int i = roha_filename.size() - 5; i < roha_filename.size(); i++){ //should be made more secure, could input improper filenames with spaces still, should check its longer than 5 
        filetype.push_back(roha_filename[i]);
    }
    if (filetype != ".roha" ){
        std::cout << "roha file was not detected ";
        return EXIT_FAILURE;
    }
    rohafile.open(roha_filename);

    std::string line;
    std::string roha_filestream;

    while (getline(rohafile, line)){
        roha_filestream += line;
    }

    rohafile.close();

    std::optional<std::vector<Token>> potential_tokens = Tokenize(roha_filestream);
    if (potential_tokens == std::nullopt) {
        return EXIT_FAILURE;
    }
    std::vector<Token> output_tokens = potential_tokens.value();
    //handling the asm file output
    std::ofstream asmfile;
    std::string asm_filename;

    for(int i = 0; i < roha_filename.size() - 5; i++){ 
        asm_filename.push_back(roha_filename[i]);
    }

    asm_filename += ".asm";

    asmfile.open(asm_filename);
    if(!asmfile.is_open()){
        std::cout << "Error creating assembly file, could not open";
        return EXIT_FAILURE;
    }
    asmfile << Token_to_Assembly(output_tokens);
    asmfile.close();


    return EXIT_SUCCESS;
}
