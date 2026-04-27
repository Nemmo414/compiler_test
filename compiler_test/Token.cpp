#include "Token.h"

Token::Token(std::string txt, tokenType typ)
{
	text = txt;
	type = typ;
}

Token::Token(std::string txt, tokenType typ, int val)
{
	text = txt;
	type = typ;
	value = val;
	//std::cout << "Created token: " << txt << "; " << typ << "; " << val << ";\n";
}

Token::Token()
{
	text = "EOF";
	type = tokenType::EOFTOKEN;
}
