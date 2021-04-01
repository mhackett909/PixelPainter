#include "Rectangle.h"
const float Rectangle::WIDTH = 10; //20
const float Rectangle::HEIGHT = 10;
Rectangle::Rectangle(sf::Vector2f pos) : sf::RectangleShape({ WIDTH, HEIGHT }) {
	setPosition(pos);
	setFillColor(sf::Color::White);
}
