#pragma once
#include <vector>
#include "consts.h"

class Bytecoder
{
public:
	std::vector<int> code;
	std::vector<int> stack;
	std::vector<int> varList;
	std::vector<int> scopes;
	std::vector<int> stackSizes;


	void cleanup();
	void setCode(std::vector<int> c);
	void execute();
	void executeButOnlyOne(int& i);
	

	std::string sayBytecode();
};

