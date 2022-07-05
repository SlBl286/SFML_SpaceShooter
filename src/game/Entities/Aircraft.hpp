#pragma once
#include "Extend/Entity.hpp"

class Aircraft : public Entity
{
    // data
public:
    typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
    enum Type
    {
        Eagle,
        Raptor
    };

private:
    Type mType;
    sf::Sprite mSprite;
    // function
private:
    Textures::ID toTextureID(Aircraft::Type type);

public:
    explicit Aircraft(Type type, const TextureHolder &textures);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    ~Aircraft();
};

void Aircraft::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

Aircraft::Aircraft(Type type, const TextureHolder &textures) : mType(type), mSprite(textures.get(toTextureID(type)))
{
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}
Textures::ID Aircraft::toTextureID(Aircraft::Type type)
{
    switch (type)
    {
    case Aircraft::Eagle:
        return Textures::ID::Eagle;
    case Aircraft::Raptor:
        return Textures::ID::Raptor;
    default:
        break;
    }
}
Aircraft::~Aircraft()
{
}
