#include "Level.hpp"
#include "GraphicLevel.hpp"

#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
    Level level;
    level.loadFromFile("assets/level.txt");
    char option;
    do
    {
        level.showInConsole();
        cout << " ===> ";
        option = getch();
        cout << "\n";
        switch (option)
        {
        case 'w':
            level.move(Level::Up);
            break;
        case 's':
            level.move(Level::Down);
            break;
        case 'a':
            level.move(Level::Left);
            break;
        case 'd':
            level.move(Level::Right);
            break;
        }
    } while (option != 'q');

    GraphicLevel graphicLevel;
    graphicLevel.loadFromFile("assets/level.txt");

    sf::RenderWindow window(sf::VideoMode(800, 600), "Sokoban");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    graphicLevel.move(Level::Up);
                    break;
                case sf::Keyboard::Down:
                    graphicLevel.move(Level::Down);
                    break;
                case sf::Keyboard::Left:
                    graphicLevel.move(Level::Left);
                    break;
                case sf::Keyboard::Right:
                    graphicLevel.move(Level::Right);
                    break;
                }
            }
        }
        window.clear();
        window.draw(graphicLevel);
        window.display();
    }
    return 0;
}
