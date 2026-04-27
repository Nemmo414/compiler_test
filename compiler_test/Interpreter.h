#pragma once
#include "Lexer.h"

class Interpreter
{
public:
	Interpreter(std::vector<Token> _tokens);
	std::vector<Token> tokens;
	Token curToken;
	int curTokenIndex = 0;


	Token expect(tokenType type);
	Token peek();
	Token getNextToken();

	int factor();
	int term();
	int expr();


	void interpret();
	void interpret(std::vector<Token> tkns);

};

