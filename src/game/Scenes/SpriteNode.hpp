#pragma once

#include "./SceneNode.hpp"

class SpriteNode : public SceneNode
{
    // data
public:
private:
    sf::Sprite mSprite;
    // function
private:
    virtual void drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates states) const;

public:
    explicit SpriteNode(const sf::Texture &texture);
    SpriteNode(const sf::Texture &texture, const sf::IntRect &rect);
    ~SpriteNode();
};
void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
SpriteNode::SpriteNode(const sf::Texture &texture, const sf::IntRect &rect) : mSprite(texture, rect)
{
}
SpriteNode::SpriteNode(const sf::Texture &texture) : mSprite(texture)
{
}
SpriteNode::~SpriteNode()
{
}
