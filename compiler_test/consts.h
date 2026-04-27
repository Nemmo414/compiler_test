#pragma once
#include <string>
#include <vector>
#include <iostream>

enum tokenType
{
	EOFTOKEN,
	SEMICOLON,
	BINOPERATOR,
	IDENTIFIER,
	NUMLITERAL,
	PAREN,
	CURVYBRACKET_LEFT,
	CURVYBRACKET_RIGHT

};

enum NodeType
{
	SUBFUNCTION,
	NUMBER,
	OPERATION,
	VARCREATION,
	VARIABLE,
	IFSTMT,
	WHILESTMT,
	FUNCTIONCALL,
};

enum OperationType
{
	Addition,
	Subtraction,
	Multiplication,
	Division,
	CheckEquals,
	CheckNotEquals,
	CheckLesser,
	CheckLesserOrEqual,
	CheckGreater,
	CheckGreaterOrEqual,
	Assignment
};

enum VarType
{
	None,
	Int,
	String
};

enum InstructionType
{
	PUSH,
	ADDVAR,
	PUSHFROMVAR,
	ADDSCOPE,
	ENDSCOPE,
	EDIT,
	END,
	ADD,
	SUB,
	MUL,
	DIV,
	PRINT
};

const std::vector<std::string> 
Keywords = 
	{
		"int",
		"if",
		"else",
		"while"
	};


std::string tokenTypeString(tokenType t);
std::string nodeTypeString(NodeType n);
std::string operationTypeString(OperationType t);
OperationType operationFromString(std::string str);

