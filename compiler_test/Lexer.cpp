#include "Lexer.h"

Lexer::Lexer(std::string src)
{
	source = src;
	formatSource();
	std::cout << "source: " << source << "\n";
	curChar = ' ';
	curPos = -1;
	eat();
}

Token Lexer::getToken()
{
	bool hungry = true;

	skipWhitespace();
	Token token;
	std::string ch = "";
	switch (curChar)
	{
	case('+'):
		if(peek() == '=')
		{ 
			token = Token("+=", tokenType::BINOPERATOR);
			eat();
			hungry = false;
		}
		else
		{
			token = Token("+", tokenType::BINOPERATOR);
		}
		break;
	case('-'):
		if (peek() == '=')
		{
			token = Token("-=", tokenType::BINOPERATOR);
			eat();
			hungry = false;
		}
		else
		{
			token = Token("-", tokenType::BINOPERATOR);
		}
		break;
	case('*'):
		token = Token("*", tokenType::BINOPERATOR);
		break;
	case('/'):
		token = Token("/", tokenType::BINOPERATOR);
		break;
	case('='):
		if (peek() == '=')
		{
			token = Token("==", tokenType::BINOPERATOR);
			eat();
			//eat();
			//hungry = false;
			std::cout << "Found == token\n";
		}
		else
		{
			token = Token("=", tokenType::BINOPERATOR);
			std::cout << "Found = token\n";
		}
		break;
	case('>'):
		if (peek() == '=')
		{
			token = Token(">=", tokenType::BINOPERATOR);
			eat();
		}
		else
		{
			std::cout << "Found > token.\n";
			token = Token(">", tokenType::BINOPERATOR);
		}
		break;
	case('<'):
		if (peek() == '=')
		{
			token = Token("<=", tokenType::BINOPERATOR);
			eat();
		}
		else
		{
			std::cout << "Found < token.\n";
			token = Token("<", tokenType::BINOPERATOR);
		}
		break;
	case('!'):
		if (peek() == '=')
		{
			token = Token("!=", tokenType::BINOPERATOR);
			eat();
		}
		else
		{
			token = Token("!", tokenType::BINOPERATOR);
		}
		break;
	case('('):
	case(')'):
		ch = "";
		ch.push_back(curChar);
		token = Token(ch, tokenType::PAREN);
		break;
	case('{'):
		token = Token("{", tokenType::CURVYBRACKET_LEFT);
		break;
	case('}'):
		token = Token("}", tokenType::CURVYBRACKET_RIGHT);
		break;
	case(';'):
		token = Token(";", tokenType::SEMICOLON);
		std::cout << "Found semicolon.\n";
		break;

	default:
		if (isalpha(curChar))
		{
			std::string s = "";
			//s += curChar;
			while (isalnum(curChar))
			{
				s += curChar;
				eat();
				hungry = false;
			}
			token = Token(s, tokenType::IDENTIFIER);
		}
		else if (isdigit(curChar))
		{
			std::string s = "";
			//s += curChar;
			//eat();
			while (isdigit(curChar))
			{
				//std::cout << "curChar is " << curChar << "\n";
				s += curChar;
				eat();
				hungry = false;
			}
			//std::cout << "STOI(s) = " << std::stoi(s) << "\n";
			int num = std::stoi(s);
			token = Token(s, tokenType::NUMLITERAL, num);
		}
		else
		{
			token = Token("EOF", tokenType::EOFTOKEN);
		}

	}
	if (hungry)
	{
		eat();
	}

	return token;
}

std::vector<Token> Lexer::tokenize()
{
	std::vector<Token> tokens = {};
	Token t = getToken();

	while (t.type != tokenType::EOFTOKEN)
	{
		tokens.push_back(t);
		//std::cout << t.text << "\n";
		t = getToken();
	}

	return tokens;
}

std::vector<std::vector<Token>> Lexer::tokenizeMultipleLines()
{
	std::vector<std::vector<Token>> vec;
	while (getToken().type != EOFTOKEN)
	{
		vec.push_back(tokenize());
	}
	return vec;
}

void Lexer::eat()
{
	curPos++;
	if (curPos >= source.length())
	{
		curChar = '\0';
	}
	else
	{
		curChar = source[curPos];
	}
}

char Lexer::peek()
{
	if (curPos + 1 >= source.length())
	{
		return '\0';
	}
	return source[curPos + 1];
}

void Lexer::skipWhitespace()
{
	//skipComments();
	while (isspace(curChar))
	{
		eat();
	}
}

void Lexer::skipComments()
{
	if (curChar == '/' and peek() == '/')
	{
		while (curChar != '\r\n' and curChar != '\n')
		{
			std::cout << "Eating " << curChar << "\n";
			eat();
		}
	}
}

void Lexer::formatSource()
{
	int multicommentDepth = 0;
	std::string source2 = "";
	for (int i = 0; i < source.size(); i++)
	{
		if (source.at(i) == '/' and source.at(i + 1) == '/')
		{
			while (source.at(i) != '\n' and source.at(i) != '\n\r')
			{
				i++;
			}
		}
		if (source.at(i) == '/' and source.at(i + 1) == '*')
		{
			i += 2;
			multicommentDepth++;
		}
		if (source.at(i) == '*' and source.at(i + 1) == '/')
		{
			i += 2;
			multicommentDepth--;
		}
		if (multicommentDepth == 0)
		{
			source2 += source.at(i);
		}

	}
	source = source2;
}
