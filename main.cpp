#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int TILE_WIDTH = 64;
int TILE_HEIGHT = 32;

sf::Vector2f gridToScreen(int x, int y, int tileWidth, int tileHeight);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1255, 200), "SFML works!", sf::Style::Fullscreen);

    int x = 0;
    int y = 0;

    sf::ConvexShape tileShape;
    tileShape.setPointCount(4);
    // Top corner apex
    tileShape.setPoint(0, sf::Vector2f(0, 0));
    // Right corner
    tileShape.setPoint(1, sf::Vector2f(TILE_WIDTH/2, TILE_HEIGHT/2));
    // Bottom corner
    tileShape.setPoint(2, sf::Vector2f(0.0f, TILE_HEIGHT));
    // Left corner
    tileShape.setPoint(3, sf::Vector2f(-TILE_WIDTH/2, TILE_HEIGHT/2));
    tileShape.setPosition({x,y});

    sf::Vector2f tileApex = gridToScreen(x,y,TILE_WIDTH,TILE_HEIGHT);

    sf::Font font;
    font.loadFromFile("JetBrainsMono-Regular.ttf");
    sf::Text coordinateText;
    coordinateText.setFont(font);

    coordinateText.setColor(sf::Color::Green);
    coordinateText.setPosition(500.0f,500.0f);
    
    bool inputEnable = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type ==  sf::Event::KeyReleased){
                inputEnable = true;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }

        if(inputEnable){

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                y--;
                inputEnable = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                y++;
                inputEnable = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                x--;
                inputEnable = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                x++;
                inputEnable = false;
            }
        }

        window.clear();
        // UPDATE

        sf::Vector2f tileApex = gridToScreen(x,y,TILE_WIDTH,TILE_HEIGHT);
        tileShape.setPosition(tileApex);

        std::stringstream ss;
        ss << "x: " << x << " y: " << y;
        coordinateText.setString(ss.str());

        // DRAWING ZONE
        window.draw(coordinateText);
        window.draw(tileShape);
        window.display();
    }

    return 0;
}

sf::Vector2f gridToScreen(int x, int y, int tileWidth, int tileHeight){
    float sx = (x - y) * (tileWidth / 2);
    float sy = (x + y) * (tileHeight / 2);
    return {sx, sy};
}
