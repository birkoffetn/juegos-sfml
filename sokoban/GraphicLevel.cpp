#include "GraphicLevel.hpp"

GraphicLevel::GraphicLevel()
{
    texture.loadFromFile("assets/sprites.png");
}

void GraphicLevel::loadFromFile(const std::string &filename)
{
    Level::loadFromFile(filename);
    const auto &level = getLevel();
    for (int i = 0; i < int(level.size()); ++i)
    {
        for (int j = 0; j < int(level[i].size()); ++j)
        {
            if (level[i][j] == WALL)
            {
                sf::Sprite sprite(texture, sf::IntRect(0, 64, 64, 64));
                sprite.setPosition(j * 64, i * 64);
                mWorld.push_back(sprite);
            }
            else if (level[i][j] == BOX)
            {
                sf::Sprite sprite(texture, sf::IntRect(192, 128, 64, 64));
                sprite.setPosition(j * 64, i * 64);
                mBoxes.push_back(sprite);
            }
            else if (level[i][j] == MAN)
            {
                mMan.setTexture(texture);
                mMan.setTextureRect(sf::IntRect(362, 248, 37, 59));
                mMan.setOrigin(-14, -5);
                mMan.setPosition(j * 64, i * 64);
            }
        }
    }
    for (const auto &point : getEndPoints())
    {
        sf::Sprite sprite(texture, sf::IntRect(128, 384, 32, 32));
        sprite.setOrigin(-16, -16);
        sprite.setPosition(point.col * 64, point.row * 64);
        mWorld.push_back(sprite);
    }
}

void GraphicLevel::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &sprite : mWorld)
    {
        target.draw(sprite, states);
    }
    for (auto &sprite : mBoxes)
    {
        target.draw(sprite, states);
    }
    target.draw(mMan, states);
}

void GraphicLevel::onMove(Point point, Point next)
{
    if (mMan.getPosition() == sf::Vector2f(point.col * 64, point.row * 64))
    {
        mMan.setPosition(next.col * 64, next.row * 64);
        return;
    }
    for (auto &sprite : mBoxes)
    {
        if (sprite.getPosition() == sf::Vector2f(point.col * 64, point.row * 64))
        {
            sprite.setPosition(next.col * 64, next.row * 64);
            return;
        }
    }
}
