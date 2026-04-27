#pragma once
#include <vector>
#include <string>
#include "Lexer.h"
#include "consts.h"

struct runtimeVal
{
	VarType type;
	int intValue = 0;
	std::string stringValue;
};

struct Node
{
	NodeType type;
	inline virtual Node* get() { return this; };
};

struct numNode : public Node
{
	int value = 0;
};

struct stringNode : public Node
{
	std::string value = "";
};

struct opNode : public Node
{
	Node* left = nullptr;
	OperationType operation;
	Node* right = nullptr;
};

struct varNode : public Node
{
	//std::string varName = "";
	int varID = 0;
	//int varValue = -1;
};

struct funcCallNode : public Node
{
	std::string funcName;
	Node* args;
};

struct subNode : public Node
{
	std::vector<Node*> nodes;
};

struct ifNode : public Node
{
	Node* condition = nullptr;
	Node* body = nullptr;
	Node* next = nullptr;
};

struct whileNode : public Node
{
	Node* condition = nullptr;
	Node* body = nullptr;
};

struct Variable
{
	//std::string name = "variable";
	int value = 0;
};

struct ScopeOld
{
	std::vector<Variable*> variables;
};

struct Scope
{
	//int prevMaxID;
	int prevNameCount;
};

struct AST
{
	std::vector<std::string> programLog;
	std::vector<Variable*> variables;
	std::vector<int> scopes;
	std::vector<std::string> takenVarNames;
	std::vector<Node*> NodesInNoParticularOrder;
	runtimeVal getValue(Node* node);
	//int getValue2(Node* node);
	runtimeVal solveOperation(Node* left, OperationType type, Node* right);
	Node* root;
	numNode* nn;
	opNode* on;

	//----GENERATOR----
	std::vector<Token> tokens;
	Token curToken;
	int curTokenIndex = 0;
	Token expect(tokenType type);
	Token peek();
	Token getNextToken();

	int nextID();

	void addVariable(std::string name); //TODO: Ukloniti name parametar - funkcija treba samo da push_backuje praznu promenjivu
	bool isVarNameValid(std::string name);
	Variable* getVariable(int id);
	int getVariableID(std::string name);

	//int setVariableValue(std::string name, int value);

	Node* factor();
	Node* term();
	Node* expr();
	Node* checkEqual();
	Node* assignment();
	Node* getSub();
	Node* getIfSTMT();
	Node* getWhileSTMT();

	void deleteOldNodes();

	void generateAST(std::vector<Token> t);
	void generateAST();

	runtimeVal callFunction(funcCallNode* fcn);

	void printVariables();

	std::vector<int> varScopeList = {0};
	std::vector<int> listOfDeclaredVars;
	int varCount = 0;
	//std::string bytecodeString = "";
	void addToVec(std::vector<int>& v1, std::vector<int>& v2);
	//std::vector<int> nodesToBytecode(Node* n, bool isAsignee);
	std::vector<int> nodesToBytecode(Node* n, bool gettingValue); //gettingValue a ne getting ID
	bool alreadyDeclared(int id);

	int getVarCount();
};

