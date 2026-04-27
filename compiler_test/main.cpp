#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Interpreter.h"
#include "AST.h"
#include "Bytecoder.h"
//#include "fibonacci.h" ne brisi ovaj komentar, za uspomenu

int main()
{
    //std::cout << "starting\n";
    std::string fname = "Scripts/testScript5.txt";

    std::ifstream inputFile(fname);
    std::string source{ std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>() };
    //std::cout << source << "\n";
    /*
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file '" << fname << "'" << std::endl;
        return 1;
    }

    std::string line; 
    std::string source = "";

    
    while (std::getline(inputFile, line)) {
        std::cout << "Read line: " << line << std::endl;
        source += line;
    }

    inputFile.close();
    */

    std::vector<int> code = {InstructionType::PUSH, 5, InstructionType::ADDVAR, InstructionType::EDIT, 0,
                             InstructionType::PUSH, 3, InstructionType::ADDVAR, InstructionType::EDIT, 1,
                             InstructionType::PUSHFROMVAR, 1, InstructionType::EDIT, 0, InstructionType::PUSHFROMVAR,
                             0, InstructionType::PRINT, InstructionType::END};

    //return 0;

    //std::string source = "5 == 3; 2 + 1; int x = 5; x = 10; int y = x + 3;";
    //std::string source = "13+ (2+7 ) -3 * 2 +(1 - (2*2) +3 * (8-5) *4);";
    //std::string source = "3* (2+7 ) /3 * (2) + (1 - (2*2)) + 3";
    //std::string source = "((2 + 1) * 2) - 3 * ((1-1)) + 1";
    Lexer lexer(source);
    //Interpreter interpreter({ Token("t",tokenType::BINOPERATOR)});
    //interpreter.interpret();
    std::vector<Token> sourceTokens = lexer.tokenize();


    
    AST ast;
    ast.generateAST(sourceTokens);
    auto bcode = ast.nodesToBytecode(ast.root, true);
    bcode.push_back(InstructionType::END);
    //ast.bytecodeString += "END";
    //std::cout << ast.bytecodeString << "\n";
    for (int i = 0; i < bcode.size(); i++)
    {
        //std::cout << bcode.at(i) << "\n";
    }

    Bytecoder bc;
    bc.setCode(bcode);

    std::cout << "\nBytecode:\n";
    std::cout << bc.sayBytecode() << "\n";
    std::cout << "\nExecuting...\n";
    bc.execute();
    
    std::cout << "EXECUTION SUCCESSFUL.\n";
    
    
    sf::Clock* c = new sf::Clock;
    c->restart();

    //std::cout << "The AST runs the operation and gets: " << ast.getValue(ast.root).intValue << "\n\n";
    //std::cout << "Execution time: " << c->restart().asSeconds() << " second(s).\n";
    //std::cout << "Program Log: \n";
    //for (int i = 0; i < ast.programLog.size(); i++)
    //{
        //std::cout << ast.programLog.at(i);
    //}
    delete c;
    //std::cout << "Existing variables: \n";
    //for (int i = 0; i < ast.scopes.at(0).variables.size(); i++)
    //{
        //std::cout << ast.scopes.at(0).variables.at(i)->name << ": " << ast.scopes.at(0).variables.at(i)->value << ".\n";
    //}
    //std::cout << "The interpreter runs the operation and gets: ";
    //interpreter.interpret(sourceTokens);

    /*
    numNode n;
    n.type = NodeType::NUMBER;
    n.value = 5;
    opNode o1;
    o1.type = NodeType::OPERATION;
    o1.left = &n;
    o1.right = &n;
    o1.operation = OperationType::Addition;
    opNode o2;
    o2.type = NodeType::OPERATION;
    o2.left = &o1;
    o2.right = &n;
    o2.operation = OperationType::Subtraction;

    std::cout << "Value of N: " << ast.getValue(&o2) << "\n";
    */

    
    sf::Clock clock;
    float time;
    clock.restart();

    int repetitions = 750000;

    if (false)
    {
        std::cout << "Beginning " << repetitions << " repetitions of the AST: \n";

        for (int i = 0; i < repetitions; i++)
        {
            //std::cout << "[" << i + 1 << "]: \n";
            //ast.cleanup();
            int v = ast.getValue(ast.root).intValue;
        }

        time = clock.restart().asSeconds();
        std::cout << "Time elapsed for " << repetitions << " repetitions of the AST: " << time << " seconds.\n\n";
    

        std::cout << "Beginning " << repetitions << " repetitions of the bytecode machine: \n";

        for (int i = 0; i < repetitions; i++)
        {
            //std::cout << "[" << i + 1 << "]: \n";
            bc.execute();
        }

        time = clock.restart().asSeconds();
        std::cout << "Time elapsed for " << repetitions << " repetitions of the interpreter: " << time << " seconds.\n\n";

    }

    return 0;
    /*
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
    */
}
