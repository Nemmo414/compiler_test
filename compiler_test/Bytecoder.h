#pragma once
#include <vector>
#include "consts.h"

class Bytecoder
{


	std::vector<int> code;
	std::vector<int> stack;
	std::vector<int> varList;
	std::vector<int> scopes;
	std::vector<int> stackSizes;

public:
	void cleanup();
	void setCode(std::vector<int> c);
	void execute();

	std::string sayBytecode();
};

