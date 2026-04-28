#include "AST.h"

runtimeVal AST::getValue(Node* node)
{
    //std::cout << "getting value of Node* at " << node << "\n";
    varNode* vn = nullptr;
    ifNode* in = nullptr;
    whileNode* wn = nullptr;
    subNode* sn = nullptr;
    funcCallNode* fcn = nullptr;
    runtimeVal whileTemp;
    int j = 0;
    int i = 0;
    switch (node->type) 
    {
    case NodeType::SUBFUNCTION:
        sn = dynamic_cast<subNode*>(node);
        //rv = {VarType::None, 0, ""};
        //for (i = 0; i < sn->nodes.size(); i++)
        //{
        //    std::cout << "[" << i << "]" << " : " << nodeTypeString(sn->nodes.at(i)->type) << "\n";
        //}
        //std::cout << "Size of subnode: " << sn->nodes.size() << "\n";
        //scopes.push_back({});

        scopes.push_back(variables.size());

        for (i = 0; i < sn->nodes.size(); i++)
        {
            //std::cout << "Handling node of index: " << i << " and type " << nodeTypeString(sn->nodes.at(i)->type) << "\n";

            j = getValue(sn->nodes.at(i)).intValue;

            //std::cout << "Got value in subfunction node: " << j << "\n";
        }
        while (variables.size() > scopes.back())
        {
            variables.pop_back();
        }
        scopes.pop_back();
        //std::cout << "Finished interpreting subnode, scopes.size() = " << scopes.size() << "\n";

        //definition_id = scopeStarts.at(scopeStarts.size() -1);
        //while (variables.size() > definition_id)
        //{
            //variables.pop_back();
        //}

        return {VarType::Int, j, ""};
        break;
    case NodeType::NUMBER:
        nn = dynamic_cast<numNode*>(node);
        //std::cout << "Getting value of numNode: " << nn->value << "\n";
        return {VarType::Int, nn->value, ""};
        break;
    case NodeType::OPERATION:
        on = dynamic_cast<opNode*>(node);
        return solveOperation(on->left, on->operation, on->right);
        //return getValue(on->left);
        break;
    case NodeType::VARCREATION:
        vn = dynamic_cast<varNode*>(node);
        addVariable("null");
        //variables.push_back({0});
        
        //std::cout << "done with varcreation node " << vn->varName << "\n";
        //printVariables();
        return { VarType::None,  vn->varID, ""};
        break;
    case NodeType::VARIABLE:
        vn = dynamic_cast<varNode*>(node);
        return {VarType::Int, getVariable(vn->varID)->value, ""};
        break;
    case NodeType::IFSTMT:
        in = dynamic_cast<ifNode*>(node);
        //std::cout << "Analyzing ifstmt...\n";
        if (getValue(in->condition).intValue > 0)
        {
            //std::cout << "Checked value of ifstmt, running body\n";
            return getValue(in->body);
        }
        else if (in->next != nullptr)
        {
            return getValue(in->next);
        }
        else
        {
            return { VarType::Int, 0, "" };
        }
        break;
    case NodeType::WHILESTMT:
        wn = dynamic_cast<whileNode*>(node);
        while (getValue(wn->condition).intValue)
        {
            whileTemp = { VarType::Int, getValue(wn->body).intValue, ""};
        }
        return whileTemp;
        break;
    case NodeType::FUNCTIONCALL:
        fcn = dynamic_cast<funcCallNode*>(node);
        //std::cout << "Called function node: " << fcn->funcName << "\n";
        return callFunction(fcn);
        break;
    default:
        std::cout << "ERROR: UNDEFINED NODE TYPE.\n";
        exit(-1);
        return {VarType::None, 0, ""};
        break;
    }
}

runtimeVal AST::solveOperation(Node* left, OperationType type, Node* right)
{
    //std::cout << "Solving operation...\n";
    varNode* _vn = nullptr;
    Variable* var = nullptr;
    runtimeVal rv;
    int id;
    switch (type)
    {
    case OperationType::Addition:
        rv = { VarType::Int, (getValue(left).intValue + getValue(right).intValue), ""};
        break;
    case OperationType::Subtraction:
        rv = { VarType::Int, (getValue(left).intValue - getValue(right).intValue), "" };
        break;
    case OperationType::Multiplication:
        rv = { VarType::Int, (getValue(left).intValue * getValue(right).intValue), "" };
        break;
    case OperationType::Division:
        rv = { VarType::Int, (getValue(left).intValue / getValue(right).intValue), "" };
        break;
    case OperationType::CheckEquals:
        //std::cout << "CHECKED EQUALS" << (getValue(left).intValue == getValue(right).intValue) << "\n";
        rv = { VarType::Int, (getValue(left).intValue == getValue(right).intValue), "" };
        break;
    case OperationType::CheckNotEquals:
        rv = { VarType::Int, (getValue(left).intValue != getValue(right).intValue), "" };
        break;
    case OperationType::CheckLesser:
        //std::cout << "CHECKED LESSER" << (getValue(left).intValue < getValue(right).intValue) << "\n";
        rv = { VarType::Int, (getValue(left).intValue < getValue(right).intValue), "" };
        break;
    case OperationType::CheckGreater:
        rv = { VarType::Int, (getValue(left).intValue > getValue(right).intValue), "" };
        break;
    case OperationType::CheckLesserOrEqual:
        rv = { VarType::Int, (getValue(left).intValue <= getValue(right).intValue), "" };
        break;
    case OperationType::CheckGreaterOrEqual:
        rv = { VarType::Int, (getValue(left).intValue >= getValue(right).intValue), "" };
        break;
    case OperationType::Assignment:
        _vn = dynamic_cast<varNode*>(left);
        id = getValue(_vn).intValue;
        var = getVariable(_vn->varID);
        var->value = getValue(right).intValue;
        //_vn->varValue = getValue(right);
        rv = {VarType::Int, var->value, ""};
        break;
    default:
        std::cout << "ERROR: UNKNOWN OPERATION TYPE: " << type << "\n";
        exit(-1);
    }
    //std::cout << "Solved operation: " << rv.intValue << "\n";

    //if (rv.intValue == 0)
    {
       // rv.intValue = -1;
    }

    return rv;
}

Token AST::expect(tokenType type)
{
    Token ret;
    if (curToken.type == type)
    {
        ret = curToken;
        curToken = getNextToken();
    }
    else
    {
        std::cout << "Wrong token type! Got " << curToken.text << " of type " << tokenTypeString(curToken.type) <<
            " , expected " << tokenTypeString(type) << "\n";
        ret = Token("EOF", EOFTOKEN);
        exit(-1);
    }
    return ret;
}

Token AST::peek()
{
    if (curTokenIndex < tokens.size())
    {
        return tokens[curTokenIndex + 1];
    }
    return Token("EOF", EOFTOKEN);;
}

Token AST::getNextToken()
{
    curTokenIndex++;
    if (curTokenIndex < tokens.size())
    {
        return tokens[curTokenIndex];
    }
    return Token("EOF", EOFTOKEN);
    std::cout << "Returned eof due to size issues.\n";
}

int AST::nextID()
{
    //definition_id++;
    //return definition_id;
    return 0;
}

void AST::addVariable(std::string name)
{
    //std::cout << "Adding varibale stage 1\n";
    int i;
    for (i = 0; i < Keywords.size(); i++)
    {
        if (Keywords.at(i) == name)
        {
            std::cout << "ERROR: Variable name cannot be a keyword. (" << name << ")\n";
            exit(-1);
        }
    }
    
    for (i = 0; i < takenVarNames.size(); i++)
    {
        //std::cout << "i " << i << " j " << j << "\n";
        if (takenVarNames.at(i) == name)
        {
            std::cout << "ERROR: Variable name already exists. (" << name << ")\n";
            exit(-1);
        }
    }
    
    //std::cout << "Adding varibale stage 2\n";
    Variable* v = new Variable;
    //v->name = name;
    //takenVarNames.push_back(name);
    v->value = -1;
    variables.push_back(v); 
    //std::cout << "Created variable " << variables.size() - 1 << ".\n";
}

bool AST::isVarNameValid(std::string name)
{
    for (int i = 0; i < Keywords.size(); i++)
    {
        if (Keywords.at(i) == name)
        {
            return false;
        }
    }
    return true;
}

/*
bool AST::checkVariableExists(std::string name)
{
    int i;
    for (i = 0; i < Keywords.size(); i++)
    {
        if (Keywords.at(i) == name)
        {
            std::cout << "ERROR: Variable name cannot be a keyword. (" << name << ")\n";
            exit(-1);
        }
    }
    for (i = 0; i < scopes.size(); i++)
    {
        for (int j = 0; j < scopes.at(i).variables.size(); j++)
        {
            if (scopes.at(i).variables.at(j)->name == name)
            {
                return true;
            }
        }
    }
    return false;
}
*/

Variable* AST::getVariable(int id)
{
    //std::cout << "Getting variable from id " << id << "...\n";
    if (id > variables.size())
    {
        std::cout << "ERROR: Variable ID out of scope.\n";
        exit(-1);
    }
    //std::cout << "Found, value of var[" << id << "] is " << variables.at(id)->value << "\n";
    return variables.at(id);

    /*
    for (int i = 0; i < scopes.size(); i++)
    {
        for (int j = 0; j < scopes.at(i).variables.size(); j++)
        {
            if (scopes.at(i).variables.at(j)->name == name)
            {
                return scopes.at(i).variables.at(j);
            }
        }
    }
    std::cout << "ERROR: No variable named " << name << " exists.\n";
    exit(-1);
    */
}

int AST::getVariableID(std::string name)
{
    
    for (int i = 0; i < takenVarNames.size(); i++)
    {
        if (takenVarNames.at(i) == name)
        {
            return i;
        }
    }
    std::cout << "ERROR: No variable named " << name << " exists.\n";
    exit(-1);
    
    return 0;
}

Node* AST::factor()
{
    //std::cout << "Current token type in factor: " << tokenTypeString(curToken.type) << "\n";
    if (curToken.type == tokenType::NUMLITERAL)
    {
        numNode* n = new numNode;
        n->type = NodeType::NUMBER;
        n->value = curToken.value;
        //std::cout << "Created numNode of value " << n->value << "\n";
        expect(tokenType::NUMLITERAL);
        NodesInNoParticularOrder.push_back(n);
        return n;
    }
    else if (curToken.type == tokenType::PAREN and curToken.text == "(")    //ovo ce mi trebati
    {
        expect(tokenType::PAREN);
        Node* n = expr();
        expect(tokenType::PAREN);

        return n;
    }
    else if (curToken.type == tokenType::IDENTIFIER and curToken.text == "int")
    {
        expect(tokenType::IDENTIFIER);
        std::string text = curToken.text;
        for (int i = 0; i < takenVarNames.size(); i++) 
        {
            if (takenVarNames.at(i) == text) 
            {
                std::cout << "ERROR: Variable named " << text << " is already defined.\n"; 
                exit(-1); 
            }
        }
        expect(tokenType::IDENTIFIER);
        varNode* v = new varNode;
        v->type = NodeType::VARCREATION;
        takenVarNames.push_back(text); 
        v->varID = takenVarNames.size() - 1; 
        //v->varID = 0; //TEMP
        std::cout << "Created varNode (creation) for varID " << v->varID << ", number of variables is " << variables.size() << "\n";
        //v->varName = text;
        //std::cout << "Created varNode of name " << v->varName << " (variable creation) \n";
        NodesInNoParticularOrder.push_back(v);
        return v;
    }
    else if (curToken.type == tokenType::IDENTIFIER and isVarNameValid(curToken.text))
    {
        if (peek().type == tokenType::PAREN and peek().text == "(")
        {
            funcCallNode* f = new funcCallNode;
            f->type = NodeType::FUNCTIONCALL;
            f->funcName = curToken.text;
            expect(IDENTIFIER);
            expect(tokenType::PAREN);
            f->args = assignment();
            expect(tokenType::PAREN);
            return f;
        }
        else
        {
            varNode* v = new varNode;
            v->type = NodeType::VARIABLE;
            v->varID = getVariableID(curToken.text);

            expect(tokenType::IDENTIFIER);

            //std::cout << "Created varNode of name " << v->varName << " (existing variable reference) \n";
            NodesInNoParticularOrder.push_back(v);
            return v;
        }

    }
    else if (curToken.type == tokenType::IDENTIFIER and curToken.text == "if")
    {
        //std::cout << "Found if.\n";
        Node* in = getIfSTMT();
        return in;
    }
    else if (curToken.type == tokenType::IDENTIFIER and curToken.text == "while")
    {
        //std::cout << "Found while.\n";
        Node* in = getWhileSTMT();
        return in;
    }
    else
    {
        std::cout << "ERROR: Invalid token type for a factor. Got " << tokenTypeString(curToken.type) << ": " << curToken.text << ", expected NUMLITERAL or PAREN.";
        exit(-1);
    }

}

Node* AST::term()
{
    Node* l = factor();
    Token t;
    while (curToken.text == "*" or curToken.text == "/")
    {
        t = curToken;
        expect(BINOPERATOR);

        opNode* n = new opNode;
        n->type = NodeType::OPERATION;

        if (t.text == "*")
        {
            n->operation = OperationType::Multiplication;
        }
        else
        {
            n->operation = OperationType::Division;
        }
        n->left = l;
        n->right = factor();
        NodesInNoParticularOrder.push_back(n);
        l = n;
    }

    return l;
}

Node* AST::expr()
{
    Node* l = term();
    Token t;

    while (curToken.text == "+" or curToken.text == "-")
    {
        t = curToken;
        expect(BINOPERATOR);

        opNode* n = new opNode;
        n->type = NodeType::OPERATION;

        if (t.text == "+")
        {
            n->operation = OperationType::Addition;
        }
        else
        {
            n->operation = OperationType::Subtraction;
        }
        n->left = l;
        n->right = term();
        NodesInNoParticularOrder.push_back(n);
        l = n;
    }
    return l;
}

Node* AST::checkEqual()
{
    Node* l = expr();
    Token t;

    while (curToken.type == tokenType::BINOPERATOR and (curToken.text == "==" or curToken.text == "!="
        or curToken.text == ">" or curToken.text == ">=" or curToken.text == "<" or curToken.text == "<="))
    {
        t = curToken;
        expect(BINOPERATOR);
        opNode* n = new opNode;
        n->type = NodeType::OPERATION;
        //n->operation = OperationType::CheckEquals;
        n->operation = operationFromString(t.text);
        n->left = l;

        n->right = expr();
        NodesInNoParticularOrder.push_back(n);
        l = n;
    }
    return l;
}

Node* AST::assignment()
{
    Node* l = checkEqual();
    Token t;

    while (curToken.text == "=")
    {
        t = curToken;
        expect(BINOPERATOR);

        opNode* n = new opNode;
        n->type = NodeType::OPERATION;
        n->operation = OperationType::Assignment;
        n->left = l;
        n->right = checkEqual();
        NodesInNoParticularOrder.push_back(n);
        l = n;
    }
    return l;
}

Node* AST::getSub()
{
    Node* n = nullptr;

    if (curToken.type == tokenType::CURVYBRACKET_LEFT)
    {
        scopes.push_back(takenVarNames.size()); 

        subNode* sn = new subNode;
        sn->type = NodeType::SUBFUNCTION;
        NodesInNoParticularOrder.push_back(sn);
        expect(tokenType::CURVYBRACKET_LEFT);
        while (curToken.type != tokenType::CURVYBRACKET_RIGHT)
        {
            sn->nodes.push_back(getSub());
            //std::cout << "Found token in getSub: " << tokenTypeString(curToken.type) << ".\n";
        }
        n = sn;
        expect(tokenType::CURVYBRACKET_RIGHT);
        //std::cout << "\nClosed subNode.\n";

        std::cout << "Finished lexing subnode, variable names: \n";
        while (takenVarNames.size() > scopes.at(scopes.size() - 1))
        {
            std::cout << takenVarNames.at(takenVarNames.size() - 1) << "\n";
            takenVarNames.pop_back();
        }
        scopes.pop_back();
        std::cout << "scopes.size() = " << scopes.size() << "\n";
        
        return n;
    }
    else
    {
        //std::cout << "\nFound non-sub line starting with:" << curToken.text << "\n";
        n = assignment();
        if (n->type != NodeType::SUBFUNCTION and n->type != NodeType::IFSTMT and n->type != NodeType::WHILESTMT)
        {
            expect(tokenType::SEMICOLON);
        }
 
        return n;
    }
    

}

Node* AST::getIfSTMT()
{
    std::cout << "Creating IF statement...[start]\n";
    ifNode* in = new ifNode;
    NodesInNoParticularOrder.push_back(in);
    in->type = IFSTMT;
    expect(IDENTIFIER);
    expect(PAREN);
    in->condition = assignment();
    expect(PAREN);
    std::cout << "Creating IF statement...[found condition]\n";
    in->body = getSub();
    std::cout << "Creating IF statement...[found body]\n";
    if (curToken.type == IDENTIFIER and curToken.text == "else")
    {
        std::cout << "Creating IF statement...[loking for else]\n";
        expect(IDENTIFIER);
        if (peek().type == IDENTIFIER and peek().text == "if")
        {
            in->next = getIfSTMT();
        }
        else
        {
            in->next = getSub();
        }
    }
    std::cout << "Creating IF statement...[done.]\n";
    
    return in;
}

Node* AST::getWhileSTMT()
{
    whileNode* wn = new whileNode;
    NodesInNoParticularOrder.push_back(wn);
    wn->type = WHILESTMT;
    expect(IDENTIFIER);
    expect(PAREN);
    wn->condition = assignment();
    expect(PAREN);
    wn->body = getSub();

    return wn;
}

void AST::deleteOldNodes()
{
    for (int i = 0; i < NodesInNoParticularOrder.size(); i++)
    {
        delete NodesInNoParticularOrder.at(i);
    }
}

void AST::generateAST(std::vector<Token> t)
{
    tokens = t;
    curTokenIndex = 0;
    curToken = tokens[curTokenIndex];
    generateAST();
}

void AST::generateAST()
{
    deleteOldNodes();
    root = getSub();
    std::cout << "\nFinished node creation.\n\n";
}

runtimeVal AST::callFunction(funcCallNode* fcn)
{ 
    if (fcn->funcName == "print")
    {
        int val = getValue(fcn->args).intValue;
        //std::cout << val << "\n";
        programLog.push_back(std::to_string(val) + "\n");
        return { VarType::Int, val, "null" };
    }
    return {VarType::None, 0, "null"};
}

void AST::printVariables()
{
    std::cout << "\nPRINTING VARIABLES:\n";
    std::cout << "Variables: " << variables.size() << "\n";
    //for (int i = 0; i < variables.size(); i++)
    //{
        //std::cout << "Vars in scope " << i << ": " << variables.at(i).size() << "\n";
        //for (int j = 0; j < scopes.at(i).variables.size(); j++)
        //{
            //std::cout << "[" << i << "]: " << variables.at(i)->name << ": " << variables.at(i)->value << "\n";
        //}
    //}
}

void AST::addToVec(std::vector<int>& v1, std::vector<int>& v2)
{
    for (int i = 0; i < v2.size(); i++)
    {
        v1.push_back(v2.at(i));
    }
}

std::vector<int> AST::nodesToBytecode(Node* n, bool gettingValue)
{
    std::cout << "Turning a " << nodeTypeString(n->type) << " node into bytecode.\n";
    std::vector<int> bc = {};
    std::vector<int> vecL;
    std::vector<int> vecR;
    Node* currentNode = n;
    subNode* sn;
    numNode* nn;
    opNode* on;
    varNode* vn;
    int i = 0;
    int oldVarCount = 0;
    int oldVC2 = varCount;
    switch (currentNode->type)
    {
    case NodeType::SUBFUNCTION:
        bc.push_back(InstructionType::ADDSCOPE);
        //bytecodeString += "ADDSCOPE \n";
        oldVarCount = varScopeList.back();
        oldVC2 = varCount;
        varScopeList.push_back(0); //novi scope
        sn = dynamic_cast<subNode*>(currentNode);
        std::cout << "Number of nodes in sub: " << sn->nodes.size() << "\n";

        for (i = 0; i < sn->nodes.size(); i++)
        {
            std::cout << "  Compiling node " << i << "\n";
            vecL = nodesToBytecode(sn->nodes.at(i), false);
            //vecL = {InstructionType::PUSH, 1};
            //bc.insert(bc.end(), vecL.begin(), vecL.end());
            std::cout << "  Adding to vec...\n";
            addToVec(bc, vecL);
            std::cout << "  Done.\n";
        }
        std::cout << "Compiled whole sub\n";
        varScopeList.pop_back();
        std::cout << "Popped back VARSCOPELIST\n";
        bc.push_back(InstructionType::ENDSCOPE);
        bc.push_back(oldVarCount);
        varCount = oldVC2;
        //bytecodeString += "ENDSCOPE " + std::to_string(oldVarCount) + " \n";
        break;
    case NodeType::NUMBER:
        bc.push_back(InstructionType::PUSH);
        //bytecodeString += "PUSH ";
        nn = dynamic_cast<numNode*>(currentNode);
        bc.push_back(nn->value);
        //bytecodeString += (std::to_string(nn->value));
        //bytecodeString += "\n";
        break;
    case NodeType::VARIABLE:
        if (gettingValue == false)
        {
            
            //bc.push_back(InstructionType::PUSH);
            //bytecodeString += "PUSH ";
            vn = dynamic_cast<varNode*>(currentNode);
            bc.push_back(vn->varID);
            std::cout << "ACCESSING VARIABLE ID " << vn->varID << "--------------------------------\n";
        }
        else
        {
            bc.push_back(InstructionType::PUSHFROMVAR);
            //bytecodeString += "PUSHFROMVAR "; //todo: moze da bude i edit var
            vn = dynamic_cast<varNode*>(currentNode);
            bc.push_back(vn->varID);
            std::cout << "ACCESSING VARIABLE CONTENT AT ID " << vn->varID << "+++++++++++++++++++++++++++\n";
        }
        //bytecodeString += std::to_string(vn->varID) + " \n";
        std::cout << "DONE ACCESSING VARIABLE\n";
        break;
    case NodeType::VARCREATION:
        std::cout << "CREATED VARIABLE \n";
        vn = dynamic_cast<varNode*>(currentNode);
        //vn->varID
        //bc.push_back(InstructionType::PUSH);
        

        //PROBAJ : IF(VN->ID < VARSCOPELIST.BACK()) - znaci: ako je line int a; a je novi id i deklarise se, inace vraca id
        if (vn->varID == getVarCount())  //TODO: ovo nista ne valja, treba da doda ADDVAR ako je potreban tj. ako ova prom. jos nije dodata
        //if(false)
        {
            std::cout << "Accesing varID " << vn->varID << " in varcreation 00000000000000000000.\n";
            bc.push_back(InstructionType::ADDVAR); //ovde je problem, ne mora uvek ici addvar pre ovoga
            varCount++; // znaci: dodaje se nova promenjiva
        }
        else //INACE : znaci: ako je line int a = 10, a je vec poznat id zbog koda za case:assignment, pa se vraca id
        {
            //bc.push_back(varScopeList.back());
            std::cout << "PUSING BACK VARID: " << vn->varID << " -38921739821739128739813218739821379183792\n";
            bc.push_back(vn->varID);
            //bytecodeString += "PUSH " + std::to_string(varScopeList.back()) + " \n";
            //bytecodeString += std::to_string(varScopeList.back()) + " \n";
            //std::cout << "VARSCOPELIST BACK IS " << std::to_string(varScopeList.back()) + ">>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n";
            //bc.push_back(InstructionType::ADDVAR);
            //bytecodeString += "ADDVAR "; //todo: moze da treba i assignment

            //varScopeList.back()++;
        }

        std::cout << "Added variable creation to bytecode successfully.\n";
        break;
    case NodeType::OPERATION:
        on = dynamic_cast<opNode*>(currentNode);
        if (on->operation == OperationType::Assignment)
        {
            std::cout << " Compiling assignment.\n";
            vecR = nodesToBytecode(on->right, true);
            addToVec(bc, vecR);
            std::cout << " Compiled right side.\n";
            if (on->left->type == VARCREATION)
            {
                bc.push_back(InstructionType::ADDVAR);
                varCount++;
                std::cout << " Accesing varID " << varCount << " in operation assignment 00000000000000000000.\n";
                std::cout << " Compiled addvar in assignment.\n";
                //listOfDeclaredVars.push_back(varScopeList.back()++);
                //bytecodeString += "ADDVAR \n";
            }
            std::cout << " Pushing back EDIT.\n";
            bc.push_back(InstructionType::EDIT);
            //bytecodeString += "EDIT ";
            vecL = nodesToBytecode(on->left, true); // mozda promeniti u true?
            std::cout << " Compiled left side.\n";
            if (vecL[0] == InstructionType::PUSHFROMVAR and vecL.size() == 2)
            {
                //std::cout << "Found varpush on the right.\n";
                std::cout << " Found varpush on the right, not adding number " + std::to_string(vecL[1]) + "--------------------------.\n";
                bc.push_back(vecL[1]);
                //bytecodeString += std::to_string(vecL[1]);
            }
            std::cout << " Done and adding to vector...\n";
            addToVec(bc, vecL);
            std::cout << " Done and added to vector.\n";
            //bytecodeString += "\n";
        }
        else
        {
            std::cout << "  DOING A DIFFERENT OPERATION.\n";
            vecR = nodesToBytecode(on->right, true);         //RIGHT pre LEFT zbog oduzimanja i deljenja
            //bc.insert(bc.end(), vecR.begin(), vecR.end());
            addToVec(bc, vecR);
            vecL = nodesToBytecode(on->left, true);          //TRUE u oba slucaja jer kad npr. sabiramo ne treba id
            //bc.insert(bc.end(), vecL.begin(), vecL.end());
            addToVec(bc, vecL);
            switch (on->operation)
            {
            case OperationType::Addition:
                bc.push_back(InstructionType::ADD);
                //bytecodeString += "ADD ";
                break;
            case OperationType::Subtraction:
                bc.push_back(InstructionType::SUB);
                //bytecodeString += "SUB ";
                break;
            case OperationType::Multiplication:
                bc.push_back(InstructionType::MUL);
                //bytecodeString += "MUL ";
                break;
            case OperationType::Division:
                bc.push_back(InstructionType::DIV);
                //bytecodeString += "DIV ";
                break;
            }
            //bytecodeString += "\n";
            break;
    default:
        std::cout << "ERROR: Unsupported node type: " << nodeTypeString(currentNode->type) << "\n";
        exit(-1);
        }

    }

    std::cout << "Finished compiling a node of type " << nodeTypeString(currentNode->type) << " into bytecode.\n";
    //bc.push_back(InstructionType::END);
    //bytecodeString += "\n";
    return bc;
}

bool AST::alreadyDeclared(int id)
{
    bool t = false;
    for (int i = 0; i < listOfDeclaredVars.size(); i++)
    {
        if (listOfDeclaredVars.at(i) == id)
        {
            return true;
        }
    }
    return false;
}

int AST::getVarCount()
{
    /*
    int a = 0;
    for (int i = 0; i < varScopeList.size(); i++)
    {
        a += varScopeList.at(i);
    }
    std::cout << "VARCOUNT IS " << a << "\n";
    return a;
    */
    return varCount;
}
