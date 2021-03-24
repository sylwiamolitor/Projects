
#pragma once
#ifndef _GRAPHICOBJECT_H
#define _GRAPHICOBJECT_H
#include <SFML/Graphics.hpp>
#include <iostream>


class Graphic_Object : public sf::Transformable, public sf::Drawable
{
	protected:
		sf::Text text; /**@param text znak - X- trafiony statek, *- pudlo, O- statek nietrafiony*/
		sf::Font font; /**@param font typ czcionki - arial*/
		sf::Vector2f position; /**@param position pozycja w oknie - wektor dwoch wspolrzednych*/
	public:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {};
};

class Ship : public Graphic_Object
{
	public:
		void change_Ship(std::string state_of_ship);/**metoda zmieniajaca typ statku na jeden z trzech mozliwych @param state_of_ship X- trafiony statek, *- pudlo, O- statek nietrafiony,  argument state_of_ship, ktory przyjmuje nowy stan statku*/
		Ship(std::string state_of_ship, sf::Font& font, sf::Vector2f position);/**konstruktor ustawiajacy statek w konsoli*/
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;/**metoda rysujaca statek*/
};
#endif