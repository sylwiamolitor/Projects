#include "GraphicObject.h"

void Ship::change_Ship(std::string state_of_ship)
{
	Ship::text.setString(state_of_ship);
}

Ship::Ship(std::string state_of_ship, sf::Font & font, sf::Vector2f position)
{

	Ship::text.setString(state_of_ship);
	Ship::text.setFont(font);
	Ship::text.setCharacterSize(40);
	Ship::text.setPosition(position.x + 45, position.y + 45);
}

void Ship::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(text);
}
