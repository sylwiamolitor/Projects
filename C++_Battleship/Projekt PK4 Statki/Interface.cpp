#include "Interface.h"

Button::Button(std::string text, sf::Font& font, int characterSize, sf::Vector2f position)
{
	Button::text.setString(text);
	Button::text.setFont(font);
	Button::text.setCharacterSize(characterSize);
	Button::text.setPosition(position.x+15, position.y);
	Button::frame.setPosition(position.x, position.y);
	Button::frame.setOutlineColor(sf::Color(250, 150, 100));
	Button::frame.setFillColor(sf::Color(150, 50, 250));
	Button::frame.setOutlineThickness(10);
	Button::frame.setSize(sf::Vector2f(500, 50));
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform(); 
	
	target.draw(frame);
	target.draw(text);
}


Board::Board(sf::Font& font, sf::Vector2f position)
{
	
	Board::frame.setPosition(position.x+45, position.y+45);
	Board::frame.setOutlineColor(sf::Color::White);
	Board::frame.setFillColor(sf::Color::Transparent);
	Board::frame.setOutlineThickness(1);
	Board::frame.setSize(sf::Vector2f(400,400));
	
}

void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(frame);
}

Field::Field(sf::Font & font, sf::Vector2f position)
{
	Field::frame.setPosition(position.x + 45, position.y + 45);
	Field::frame.setOutlineColor(sf::Color::White);
	Field::frame.setFillColor(sf::Color::Transparent);
	Field::frame.setOutlineThickness(0.5);
	Field::frame.setSize(sf::Vector2f(40, 40));
}

void Field::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(frame);
}

Count_Score::Count_Score(std::string text, sf::Font & font, int characterSize, sf::Vector2f position)
{
	Count_Score::text.setString(text);
	Count_Score::text.setFont(font);
	Count_Score::text.setCharacterSize(characterSize);
	Count_Score::text.setPosition(position.x + 15, position.y);
	Count_Score::frame.setPosition(position.x, position.y);
	Count_Score::frame.setOutlineColor(sf::Color(150, 50, 100));
	Count_Score::frame.setFillColor(sf::Color(10, 150, 250));
	Count_Score::frame.setOutlineThickness(5);
	Count_Score::frame.setSize(sf::Vector2f(100, 50));
}

void Count_Score::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(frame);
	target.draw(text);
}

void Count_Score::setString(std::string text)
{
	Count_Score::text.setString(text);
}
