#include <fstream> // will remove after main function is moved files
#include <cstdlib>
#include <bits/stdc++.h>

enum TokenType {
    NUM,
    STRING,
    //VAR,
    //OPERATOR,
    DELIMITER,
    KEYWORD,
};

class Token {
    public:
    //representation of the token as a string 
    std::string repr;
    TokenType type;
    friend bool operator==(Token &t1, const Token &t2){
        return (t1.repr == t2.repr);
    }

    Token(std::string repr_param, TokenType type_param) {
        repr = repr_param;
        type = type_param;
    }
};


//Token IF = Token("if", TokenType::KEYWORD);
//Token FOR = Token("for", TokenType::KEYWORD);
Token RETURN = Token("return", TokenType::KEYWORD);
Token SEMICOLON = Token(";", TokenType::DELIMITER);

bool isNum (std::string s){
    for(char c : s){
        if(std::isdigit(c)){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

std::optional<Token> string_to_token(std::string current_string) {
        if (isNum(current_string)) {
            return Token(current_string, TokenType::NUM);
        }

        if (current_string == ";"){
            return SEMICOLON;
        }

        if (current_string == "return"){
            return RETURN;
        }
        return std::nullopt;

}

std::optional<std::vector<Token>> Tokenize(const std::string& filestream) { //file handling  in future main compiling file

    std::string current_string;
    std::vector<Token> output_tokens;

    for(int i = 0; i < filestream.size(); i++){
        
        char curr_char = filestream[i];
        if (curr_char == ' ') {
            std::optional<Token> new_token = string_to_token(current_string);
            if (new_token == std::nullopt) {
                return std::nullopt;
            }
            output_tokens.push_back(new_token.value());
            current_string.clear();
        }
        else{
            current_string.push_back(curr_char);
        }
    }
    std::optional<Token> new_token = string_to_token(current_string);
    if (new_token == std::nullopt) {
        return std::nullopt;
    }
    output_tokens.push_back(new_token.value());
    
    return output_tokens;
    // TO ADD:
    // use better token detcetion than just whitespace
    // maximal munch implementation (use an fsm?)

    // at this point output_tokens contains every token in the string
}

// int main(int argc, char* argv[]){
//     std::ifstream rohafile;
//     if (argc != 2){
//         std::cout << "Error opening file" << std::endl;
//         return EXIT_FAILURE;
//     }

//     rohafile.open(argv[1]);

//     std::string line;
//     std::string filestream;

//     while (getline(rohafile, line)){
//         filestream += line;
//     }

//     rohafile.close();

//     std::optional<std::vector<Token>> potential_tokens = Tokenize(filestream);
//     if (potential_tokens == std::nullopt) {
//         return EXIT_FAILURE;
//     }
//     std::vector<Token> output_tokens = potential_tokens.value();

//     std::cout << "Final tokens are: " << std::endl;
//     for (Token token : output_tokens) {
//         std::cout << token.repr << " " << token.type << std::endl;
//     }

// }