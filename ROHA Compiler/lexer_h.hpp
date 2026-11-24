#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <bits/stdc++.h>

enum TokenType;
class Token;
bool isNum(std::string s);
std::optional<Token> string_to_token(std::string current_string);
std::optional<std::vector<Token>> Tokenize(const std::string& filestream);

//declare all tokens here
Token RETURN;
Token SEMICOLON;

#endif