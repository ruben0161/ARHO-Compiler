#include <iostream>
#include "lexer_h.hpp"
#include <sstream>

std::string Assemble(std::vector<Token> tokens) {
    std::stringstream output;
    output << "default rel" << std::endl << "extern puts" << std::endl << "global main";

    return output.str();
}

int main(){
    std::vector<Token> final_tokens = {RETURN};
    std::cout << Assemble();
}