#include "sfml_util.h"

void byteCodeToText(std::vector<int> code, std::vector<highlightableText>& text, sf::Font& font)
{
	bool eatNumber = false;
	
	for (int i = 0; i < code.size(); i++)
	{
		bool eol = false;
		std::string str = "";
		if (eatNumber == true)
		{
			str = std::to_string(code.at(i)) + "\n";
			eatNumber = false;
		}
		else
		{
			switch (code.at(i))
			{
			case InstructionType::PUSH:
				str += "PUSH ";
				eatNumber = true;
				break;
			case InstructionType::PUSHFROMVAR:
				str += "PUSHFROMVAR ";
				i++;
				str += std::to_string(code.at(i)) + "\n";
				break;
			case InstructionType::EDIT:
				str += "EDIT ";
				eatNumber = true;
				break;
			case InstructionType::JMP_IF:
				str += "JMP_IF ";
				eatNumber = true;
				break;
			case InstructionType::JMP:
				str += "JMP ";
				eatNumber = true;
				break;
			case InstructionType::ENDSCOPE:
				str += "ENDSCOPE ";
				eatNumber = true;
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
			case InstructionType::CHK_EQ:
				str += "CHK_EQ\n";
				break;
			case InstructionType::CHK_NEQ:
				str += "CHK_NEQ\n";
				break;
			case InstructionType::CHK_LES:
				str += "CHK_LES\n";
				break;
			case InstructionType::CHK_LESORE:
				str += "CHK_LESORE\n";
				break;
			case InstructionType::CHK_GRT:
				str += "CHK_GRT\n";
				break;
			case InstructionType::CHK_GRTORE:
				str += "CHK_GRTORE\n";
				break;
			case InstructionType::PRINT:
				str += "PRINT\n";
				break;
			case InstructionType::END:
				str += "END\n";
				break;

			default:
				std::cout << "ERROR: Unknown operation type.\n";
				//exit(-1);
				//std::cout << "String so far: \n";
				//return str + std::to_string(code.at(i)) + " <-[ERROR HERE]";
				break;
			}
		}
		
		if (str.back() == '\n')
		{
			str.pop_back();
			eol = true;
		}
		else
		{
			eol = false;
		}

		sf::Text t;
		t.setString(str);
		t.setFont(font);
		t.setCharacterSize(32.f);
		t.setFillColor(sf::Color(215, 215, 217));
		sf::RectangleShape rec;
		rec.setFillColor(sf::Color::Black);
		rec.setSize({ t.getLocalBounds().getSize().x + 2, t.getLocalBounds().getSize().y + 2 });
		rec.setPosition({t.getGlobalBounds().getPosition().x - 1, t.getGlobalBounds().getPosition().y - 1 });

		text.push_back({t, rec, eol});
	}
}

void highlightableText::setPosition(sf::Vector2f pos)
{
	text.setPosition(pos);
	bgRect.setPosition({ text.getGlobalBounds().getPosition().x - 1, text.getGlobalBounds().getPosition().y - 1 });
}
