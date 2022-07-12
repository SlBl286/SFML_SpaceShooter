#pragma once
#include "Extend/Entity.hpp"

class Aircraft : public Entity
{
    // data
public:
    typedef ResourceHolder<sf::Texture, ResourceId::Textures> TextureHolder;
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
    ResourceId::Textures toTextureID(Aircraft::Type type);
    virtual unsigned int getCategory() const;

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
    mSprite.setScale(0.5f, 0.5f);
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
   
}
ResourceId::Textures Aircraft::toTextureID(Aircraft::Type type)
{
    switch (type)
    {
    case Aircraft::Eagle:
        return ResourceId::Textures::Eagle;
    case Aircraft::Raptor:
        return ResourceId::Textures::Raptor;
    default:
        break;
    }
}
unsigned int Aircraft::getCategory() const
{
    switch (mType)
    {
    case Eagle:
        return Category::PlayerAircraft;

    default:
        return Category::EnemyAircraft;
    }
}
Aircraft::~Aircraft()
{
}
