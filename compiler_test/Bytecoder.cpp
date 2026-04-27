#include "Bytecoder.h"
#include <iostream>

void Bytecoder::cleanup()
{
	stack = {};
	varList = {};
	scopes = {};
}

void Bytecoder::setCode(std::vector<int> c)
{
	code = c;
}

void Bytecoder::execute()
{
	cleanup(); //ocisti ostatke koda od ranije, ako postoje
	int i = 0;
	//int n = 0;

	while (code.at(i) != InstructionType::END)
	{
		switch (code.at(i))
		{
		int a, b;
		case InstructionType::PUSH:
			i++;
			stack.push_back(code.at(i));
			break;
		case InstructionType::ADDVAR:
			varList.push_back(0);
			break;
		case InstructionType::PUSHFROMVAR: //TODO: Ovo
			i++;
			a = code.at(i);
			b = varList.at(a);
			stack.push_back(b);
			break;
		case InstructionType::ADDSCOPE:
			stackSizes.push_back(stack.size());
			break;
		case InstructionType::ENDSCOPE:
			std::cout << "ENDING SCOPE.\n";
			std::cout << "VARIABLES: " << varList.size() << "\n";
			i++; // pojede argument, tj. broj promenjivih ne racunajuci prethodni scope
			std::cout << "Code at i: " << code.at(i) << "\n";
			//a = 0;
			while (varList.size() > code.at(i))
			{
				std::cout << "Variable [" << varList.size() - 1 << "]: " << varList.back() << "\n";
				varList.pop_back();
			}
			while (stack.size() > stackSizes.back())
			{
				stack.pop_back();
			}
			stackSizes.pop_back();
			std::cout << "Ended scope.\n";
			break;
		case InstructionType::EDIT: //TODO: I ovo
			//i++ ce morati da "pojede" ID tj. sledeci element (ovo sam napisao pre nego sto sam legao da se setim)
			i++;
			a = code.at(i);
			//std::cout << "code.at(i) is " << code.at(i) << "\n";
			//std::cout << "Editing var at id " << a << " of " << varList.size() << "\n";
			varList.at(a) = stack.back();
			stack.pop_back();
			//std::cout << "Edited var at id " << a << " of " << varList.size() << "\n";
			break;
		case InstructionType::ADD:
			a = stack.back();
			stack.pop_back();
			a += stack.back();
			stack.pop_back();
			stack.push_back(a);
			break;
		case InstructionType::SUB:
			a = stack.back();
			stack.pop_back();
			b = stack.back();
			stack.pop_back();
			stack.push_back(b - a);
			break;
		case InstructionType::MUL:
			a = stack.back();
			stack.pop_back();
			a *= stack.back();
			stack.pop_back();
			stack.push_back(a);
			break;
		case InstructionType::DIV:
			a = stack.back();
			stack.pop_back();
			b = stack.back();
			stack.pop_back();
			stack.push_back(b / a);
			break;
		case InstructionType::PRINT:
			std::cout << stack.back() << "\n";
			break;
		default:
			break;
		}

		i++;
		//std::cout << "i increased to " << i << "\n";
	}
	//std::cout << "Finished execution.\n";
	//std::cout << "Finished execution, final value is " << stack.back() << ".\n";
}

std::string Bytecoder::sayBytecode()
{
	std::string str;
	for (int i = 0; i < code.size(); i++)
	{
		switch (code.at(i))
		{
		case InstructionType::PUSH:
			str += "PUSH ";
			i++;
			str += std::to_string(code.at(i)) + "\n";
			break;
		case InstructionType::PUSHFROMVAR:
			str += "PUSHFROMVAR ";
			i++;
			str += std::to_string(code.at(i)) + "\n";
			break;
		case InstructionType::EDIT:
			str += "EDIT ";
			i++;
			str += std::to_string(code.at(i)) + "\n";
			break;
		case InstructionType::ENDSCOPE:
			str += "ENDSCOPE ";
			i++;
			str += std::to_string(code.at(i)) + "\n";
			break;
		case InstructionType::ADDSCOPE:
			str += "ADDSCOPE\n";
			break;
		case InstructionType::ADDVAR:
			str += "ADDVAR\n";
			break;
		case InstructionType::ADD:
			str += "ADD\n";
			break;
		case InstructionType::SUB:
			str += "SUB\n";
			break;
		case InstructionType::MUL:
			str += "MUL\n";
			break;
		case InstructionType::DIV:
			str += "DIV\n";
			break;
		case InstructionType::PRINT:
			str += "PRINT\n";
			break;
		case InstructionType::END:
			str += "END\n";
			break;

		default:
			std::cout << "ERROR: Unknown operation type.\n";
			exit(-1);
			break;
		}
	}
	return str;
}
