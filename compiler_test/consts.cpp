#include "consts.h"


std::string tokenTypeString(tokenType t)
{
	switch (t)
	{
	case EOFTOKEN:
		return "EOF";
		break;
	case SEMICOLON:
		return "Semicolon";
		break;
	case BINOPERATOR:
		return "Binary operator";
		break;
	case IDENTIFIER:
		return "Identifier";
	case NUMLITERAL:
		return "Numeric Literal";
		break;
	case PAREN:
		return "Parenthesis";
		break;
	case CURVYBRACKET_LEFT:
		return "Curvy bracket (left)";
		break;
	case CURVYBRACKET_RIGHT:
		return "Curvy bracket (right)";
		break;
	default:
		return "UNDEFINED TOKEN TYPE";
		break;
	}
}

std::string nodeTypeString(NodeType n)
{
	switch (n)
	{
	case NodeType::IFSTMT:
		return "IF STATEMENT";
		break;
	case NodeType::NUMBER:
		return "NUMBER";
		break;
	case NodeType::OPERATION:
		return "OPERATION";
		break;
	case NodeType::SUBFUNCTION:
		return "SUBFUBCTION";
		break;
	case NodeType::VARCREATION:
		return "VARCREATION";
		break;
	case NodeType::VARIABLE:
		return "VARIABLE";
		break;
	case NodeType::WHILESTMT:
		return "WHILE STATEMENT";
		break;
	case NodeType::FUNCTIONCALL:
		return "FUNCTION CALL";
		break;
	default:
		std::cout << "ERROR: Unknown node type: " << n << "\n";
		exit(-1);
		break;

	}
}

std::string operationTypeString(OperationType t)
{
	switch (t)
	{
	case Addition:
		return "Addition";
		break;
	case Subtraction:
		return "Subtraction";
		break;
	case Multiplication:
		return "Multiplication";
		break;
	case Division:
		return "Division";
		break;
	case CheckEquals:
		return "Equality comparison";
		break;
	default:
		return "ERROR: Unknown OperationType.";
		break;
	}
}

OperationType operationFromString(std::string str)
{
	if(str == "+")
	{
		return OperationType::Addition;
	}
	if (str == "-")
	{
		return OperationType::Subtraction;
	}
	if (str == "*")
	{
		return OperationType::Multiplication;
	}
	if (str == "/")
	{
		return OperationType::Division;
	}
	if (str == "==")
	{
		return OperationType::CheckEquals;
	}
	if (str == "!=")
	{
		return OperationType::CheckNotEquals;
	}
	if (str == "<")
	{
		return OperationType::CheckLesser;
	}
	if (str == "<=")
	{
		return OperationType::CheckLesserOrEqual;
	}
	if (str == ">")
	{
		return OperationType::CheckGreater;
	}
	if (str == ">=")
	{
		return OperationType::CheckGreaterOrEqual;
	}
	std::cout << "ERROR: unknown operation string: " << str << "\n";
}
