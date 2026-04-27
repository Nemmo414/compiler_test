#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Token.h"

class Lexer
{
public:
	Lexer(std::string src);
	//void lex();
	Token getToken();
	std::vector<Token> tokenize();
	std::vector<std::vector<Token>> tokenizeMultipleLines();

	std::string source;
	char curChar;
	int curPos = -1;

	void eat();
	char peek();

	void skipWhitespace();
	void skipComments();

	void formatSource();
};

