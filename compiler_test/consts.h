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
	PUSH = 300,
	ADDVAR = 301,
	PUSHFROMVAR = 302,
	ADDSCOPE = 303,
	ENDSCOPE = 304,
	EDIT = 305,
	END = 306,
	ADD = 307,
	SUB = 308,
	MUL = 309,
	DIV = 310,
	PRINT = 311
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

