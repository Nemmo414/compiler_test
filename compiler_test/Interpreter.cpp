#include "Interpreter.h"

Interpreter::Interpreter(std::vector<Token> _tokens)
{
	tokens = _tokens;
	curTokenIndex = 0;
	curToken = tokens[curTokenIndex];
}

Token Interpreter::expect(tokenType type)
{
	Token ret;
	if (curToken.type == type)
	{
		ret = curToken;
		curToken = getNextToken();
	}
	else
	{
		std::cout << "Wrong token type! Got " << curToken.text << " of type " << tokenTypeString(curToken.type) <<
			" , expected " << tokenTypeString(type) << "\n";
		ret = Token("EOF", EOFTOKEN);
		exit(-1);
	}
	return ret;
}

Token Interpreter::peek()
{
	if (curTokenIndex < tokens.size())
	{
		return tokens[curTokenIndex + 1];
	}
	return Token("EOF", EOFTOKEN);;
}

Token Interpreter::getNextToken()
{
	curTokenIndex++;
	if (curTokenIndex < tokens.size())
	{
		return tokens[curTokenIndex];
	}
	return Token("EOF", EOFTOKEN);
}

int Interpreter::factor()
{
	if (curToken.type == NUMLITERAL)
	{
		Token t = curToken;
		expect(NUMLITERAL);
		return t.value;
	}
	else if (curToken.type == PAREN and curToken.text == "(")
	{
		expect(PAREN);
		int result = expr();
		//std::cout << "Found closed parenthesis.\n";
		expect(PAREN);
		return result;
	}
	std::cout << "ERROR: Invalid token type for a factor. Got " << curToken.text << ", expected NUMLITERAL or PAREN.";
	exit( - 1);
}

int Interpreter::expr()
{
	//std::cout << curToken.text << "\n";
	int result = term();
	//Token left = Token(std::to_string(result), NUMLITERAL, result);

	while (curToken.text == "+" or curToken.text == "-")
	{
		Token op = expect(BINOPERATOR);
		
		if (op.text == "+")
		{
			result += term();
		}
		else
		{
			result -= term();
		}
		
		//result += term() * (-1 * (op.text == "-"));
	}
	return result;
}

int Interpreter::term()
{
	//std::cout << "term() called. Text: " << curToken.text << "\n";

	int result = factor();

	//std::cout << "lvalue: " << result << "\n";

	while (curToken.text == "*" or curToken.text == "/")
	{
		Token op = expect(BINOPERATOR);
		//int r = factor();
		/*
		if (op.text == "*")
		{
			result *= r;
		}
		else
		{
			//if (r == 0) { std::cout << "ERROR: Division by zero (" << result << "/" << r << "\n"; }
			//else
			result /= r;
		}
		*/
		int r = factor();
		result *= r - ((r - 1) * (op.text == "/"));
		result /= r - ((r - 1) * (op.text == "*"));
	}
	//std::cout << "term() result: " << result << std::endl;
	return result;
}

void Interpreter::interpret()
{
	//std::cout << "\nRezultat: " << expr() << "\n";
	int i = expr();
	
	//std::cout << i << "\n";
		/*
		Token left = expect(NUMLITERAL);

		Token op = expect(BINOPERATOR);

		Token right = expect(NUMLITERAL);

		if (op.text == "+")
		{
			std::cout << std::stoi(left.text) + std::stoi(right.text);
		}
		else
		{
			std::cout << std::stoi(left.text) - std::stoi(right.text);
		}
		*/
	//std::cout << left.text << std::endl;
}

void Interpreter::interpret(std::vector<Token> tkns)
{
	tokens = tkns;
	curTokenIndex = 0;
	curToken = tokens[curTokenIndex];
	//std::cout << "tokens[0] = " << tokens[0].text << "\n";
	interpret();
}


