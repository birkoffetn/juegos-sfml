#ifndef __GRAPHIC_LEVEL_HPP__
#define __GRAPHIC_LEVEL_HPP__

#include "Level.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class GraphicLevel : public Level, public sf::Drawable
{
public:
    GraphicLevel();
    void loadFromFile(const std::string &filename) override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void onMove(Point point, Point next) override;

private:
    sf::Texture texture;
    std::vector<sf::Sprite> mWorld;
    std::vector<sf::Sprite> mBoxes;
    sf::Sprite mMan;
};

#endif