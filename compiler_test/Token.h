#pragma once
#include <string>
#include "consts.h"
#include <iostream>

class Token
{
public:
	std::string text = "";
	int value = 0;
	tokenType type;
	Token(std::string txt, tokenType typ);
	Token(std::string txt, tokenType typ, int val);
	Token();
};

