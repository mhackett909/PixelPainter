#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <SFML/Graphics.hpp>
class Rectangle : public sf::RectangleShape {
public:
    Rectangle(sf::Vector2f pos);
    static const sf::Color DEFAULT_COLOR;
    static const float WIDTH;
    static const float HEIGHT;
};
#endif

