#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int TILE_WIDTH = 64;
int TILE_HEIGHT = 32;
sf::Vector2f CENTER_TILE_COORDINATE = {31, 2};
int SCREEN_WIDTH = 1980;
int SCREEN_HEIGHT = 1080;

struct VisibleGrid {
    int data[60][60];
};

sf::Vector2f gridToScreen(float x, float y, int tileWidth, int tileHeight);
sf::ConvexShape generateTile(int tileWidth, int tileHeight, sf::Color color);
VisibleGrid generateTileMap();
void drawTileMap(sf::RenderWindow& window, VisibleGrid& grid, int tileWidth, int tileHeight, sf::ConvexShape& tile);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1980, 1080), "Isometric land", sf::Style::Fullscreen);

    float x = CENTER_TILE_COORDINATE.x;
    float y = CENTER_TILE_COORDINATE.y;

    sf::ConvexShape tileShape = generateTile(TILE_WIDTH, TILE_HEIGHT, sf::Color::Green);
    tileShape.setPosition(CENTER_TILE_COORDINATE);

    sf::Vector2f tileApex = gridToScreen(x,y,TILE_WIDTH,TILE_HEIGHT);

    sf::Font font;
    font.loadFromFile("JetBrainsMono-Regular.ttf");
    sf::Text coordinateText;
    coordinateText.setFont(font);

    coordinateText.setColor(sf::Color::Green);
    coordinateText.setPosition(500.0f,500.0f);
    
    bool inputEnable = false;

    VisibleGrid grid = generateTileMap();
    sf::ConvexShape whiteTileShape = generateTile(TILE_WIDTH, TILE_HEIGHT, sf::Color::Magenta);

    sf::View view;
    view.reset(sf::FloatRect(SCREEN_WIDTH/2 - 600, SCREEN_HEIGHT/2 - 300, 1200, 600));
    window.setView(view);

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
        drawTileMap(window, grid, TILE_WIDTH, TILE_HEIGHT, whiteTileShape);
        window.draw(coordinateText);
        window.draw(tileShape);
        window.display();
    }

    return 0;
}

sf::Vector2f gridToScreen(float x, float y, int tileWidth, int tileHeight){
    float sx = (x - y) * (tileWidth / 2);
    float sy = (x + y) * (tileHeight / 2);
    return {sx, sy};
}

sf::ConvexShape generateTile(int tileWidth, int tileHeight, sf::Color color){
    sf::ConvexShape tileShape;
    tileShape.setPointCount(4);
    // Top corner apex
    tileShape.setPoint(0, sf::Vector2f(0, 0));
    // Right corner
    tileShape.setPoint(1, sf::Vector2f(tileWidth/2, tileHeight/2));
    // Bottom corner
    tileShape.setPoint(2, sf::Vector2f(0.0f, tileHeight));
    // Left corner
    tileShape.setPoint(3, sf::Vector2f(-tileWidth/2, tileHeight/2));
    tileShape.setFillColor(color);
    return tileShape;
}

VisibleGrid generateTileMap() {
    VisibleGrid grid;
    for (int i = 0; i < 60; ++i) {
        for (int j = 0; j < 60; ++j) {
            if(i%2 == 0 && j%2 == 0){
                grid.data[i][j] = 1; // White tile
            } else {
                grid.data[i][j] = 0; // Black tile
            }
        }
    }
    return grid;
}

void drawTileMap(sf::RenderWindow& window, VisibleGrid& grid, int tileWidth, int tileHeight, sf::ConvexShape& tile) {
    for (int i = 0; i < 60; ++i) {
        for (int j = 0; j < 60; ++j) {
            if (grid.data[i][j] == 1) {
                tile.setPosition(gridToScreen(i + 3, j - 28, tileWidth, tileHeight));
                window.draw(tile);
            }
        }
    }
}
