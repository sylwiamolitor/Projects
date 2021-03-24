#pragma once


#pragma once
#ifndef _INTERFACE_H
#define _INTERFACE_H
#include <SFML/Graphics.hpp>
#include <iostream>



class Interface : public sf::Transformable, public sf::Drawable
{
	protected:
		sf::Text text;/**@param text tekst, ktory zostanie przekazany do konstruktora*/
		sf::Font font;/**@param font typ czcionki - arial*/
		sf::Vector2f position;/**@param position pozycja w oknie - wektor dwoch wspolrzednych*/
		sf::RectangleShape frame;/**@param frame ramka, potrzebna przy przyciskach i planszach*/

	public:
		virtual	void draw(sf::RenderTarget &target, sf::RenderStates states) const {};/**metoda rysujaca obiekt*/
};

class Button :  public Interface
{
	public:
		Button() {};
		Button(std::string text, sf::Font& font, int characterSize, sf::Vector2f position);/**konstruktor*/
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;/**metoda rysujaca obiekt*/
		

};

class Board : public Interface
{

	public:
		Board() {};
		Board(sf::Font& font, sf::Vector2f position);/**konstruktor*/
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;/**metoda rysujaca obiekt*/

};

class Field : public Board
{

	public:
		Field(sf::Font& font, sf::Vector2f position);/**konstruktor*/
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;/**metoda rysujaca obiekt*/

};

class Count_Score : public Button
{
	public:
		Count_Score(std::string text, sf::Font& font, int characterSize, sf::Vector2f position);/**konstruktor*/
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;/**metoda rysujaca obiekt*/
		void setString(std::string text);/**metoda umozliwiajaca zmiane wyniku*/


};

#endif