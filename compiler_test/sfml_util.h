#pragma once
#include <SFML/Graphics.hpp>
#include "consts.h"


struct highlightableText
{
	sf::Text text;
	sf::RectangleShape bgRect;
	bool endOfLine;
	void setPosition(sf::Vector2f pos);
};

void byteCodeToText(std::vector<int> code, std::vector<highlightableText>& text, sf::Font& font);


