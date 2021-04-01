#include <C:\SFML-2.5.1\include\SFML\Graphics.hpp>
#include <array>
#include <iostream>
#include <cassert>
#include "Rectangle.h"
const unsigned int GRID_HEIGHT   = 48; //24
const unsigned int GRID_WIDTH    = 48;
const float        GRID_PADDING  = 1.0f; 
const unsigned int WINDOW_WIDTH  = 528;
const unsigned int WINDOW_HEIGHT = 528;
const std::string  TITLE = "Pixel Painter 1.0";
typedef std::array< std::array<Rectangle*, GRID_WIDTH>, GRID_HEIGHT> RectangleGrid;
void createGrid(RectangleGrid&, float);
void drawGrid(sf::RenderWindow&, const RectangleGrid&);
void eraseGrid(RectangleGrid&);
void clearGrid(RectangleGrid&);
sf::Color parseKeyboardInput(const sf::Keyboard::Key&);
Rectangle *parseMouseInput(const sf::Vector2i&, const RectangleGrid&);
int main() {
    assert(GRID_HEIGHT > 0);
    assert(GRID_WIDTH > 0);
    assert(GRID_PADDING > 0.0f);
    Rectangle help = Rectangle({ 0,0 });
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE, sf::Style::Close); //not resizable
    RectangleGrid rectangles;
    createGrid(rectangles, GRID_PADDING); // Initialize the rectangles
    sf::Color paintColor = sf::Color::Black;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed) paintColor = parseKeyboardInput(event.key.code);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                Rectangle *clickedRectangle = parseMouseInput(sf::Mouse::getPosition(window), rectangles);
                if(clickedRectangle != nullptr) clickedRectangle->setFillColor(paintColor);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                Rectangle* clickedRectangle = parseMouseInput(sf::Mouse::getPosition(window), rectangles);
                if (clickedRectangle != nullptr) clickedRectangle->setFillColor(sf::Color::White);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                Rectangle* clickedRectangle = parseMouseInput(sf::Mouse::getPosition(window), rectangles);
                if (clickedRectangle != nullptr) eraseGrid(rectangles);
            }
        }
        window.clear(sf::Color::Black);
        drawGrid(window, rectangles);
        window.display();
    }
    clearGrid(rectangles);
    return 0;
}
void createGrid(RectangleGrid &r, float rectanglePadding) {
    float pos_x, pos_y, incWidth, incHeight;
    pos_x = pos_y = rectanglePadding;
    incWidth = Rectangle::WIDTH + rectanglePadding;
    incHeight = Rectangle::HEIGHT + rectanglePadding;
    for (int x = 0; x < GRID_HEIGHT; x++) {
        for (int y = 0; y < GRID_WIDTH; y++) {
            r[x][y] = new Rectangle({pos_x, pos_y});
            pos_x += incWidth;
        }
        pos_x = rectanglePadding;
        pos_y += incHeight;
    }
}
void drawGrid(sf::RenderWindow &window, const RectangleGrid &r) {
    for (int x = 0; x < GRID_HEIGHT; x++)
        for (int y = 0; y < GRID_WIDTH; y++) 
            window.draw(*r[x][y]);
    return;
}
void eraseGrid(RectangleGrid &r) {
    for (int x = 0; x < GRID_HEIGHT; x++)
        for (int y = 0; y < GRID_WIDTH; y++)
            r[x][y]->setFillColor(sf::Color::White);
}
void clearGrid(RectangleGrid &r) {
    for (int x = 0; x < GRID_HEIGHT; x++) {
        for (int y = 0; y < GRID_WIDTH; y++) {
            delete r[x][y];
            r[x][y] = nullptr;
        }
    }
    return;
}
sf::Color parseKeyboardInput(const sf::Keyboard::Key &k) {
    sf::Color color;
    switch (k) {
    case 27:
        color = sf::Color(192, 192, 192);
        break;
    case 28:
        color = sf::Color::Yellow;
        break;
    case 29:
        color = sf::Color(255, 153, 51);
        break;
    case 30:
        color = sf::Color(0, 255, 0);
        break;
    case 31:
        color = sf::Color(0, 128, 0);
        break;
    case 32:
        color = sf::Color::Cyan;
        break;
    case 33:
        color = sf::Color::Blue;
        break;
    case 34:
        color = sf::Color::Red;
        break;
    case 35:
        color = sf::Color::Magenta;
        break;
    case 26:
        color = sf::Color(153, 51, 255);
        break;
    default:
        color = sf::Color::Black;
    }
    return color;
}
Rectangle* parseMouseInput(const sf::Vector2i &localPosition, const RectangleGrid &r){
    Rectangle *ptr;
    int magicNum = ptr->WIDTH+GRID_PADDING;
    if (localPosition.x % magicNum == 0 || localPosition.y % magicNum == 0) ptr = nullptr;
    else if (localPosition.x < 0 || localPosition.y < 0) ptr = nullptr;
    else if (localPosition.x > WINDOW_WIDTH || localPosition.y > WINDOW_HEIGHT) ptr = nullptr;
    else ptr = r[localPosition.y / magicNum][localPosition.x / magicNum];
    return ptr;
}