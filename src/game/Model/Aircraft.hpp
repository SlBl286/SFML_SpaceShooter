#pragma once
#include "Extends/Base.hpp"
#include "src\game\Resources.hpp"
#include "src/game/ResourceID.hpp"
class Aircraft : public Entity
{
public:
    typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
    enum class Type
    {
        Eagle,
        Raptor,
    };

public:
    Textures::ID toTextureID(Aircraft::Type type)
    {
        switch (type)
        {
        case Aircraft::Type::Eagle:
            return Textures::ID::Eagle;
        case Aircraft::Type::Raptor:
            return Textures::ID::Raptor;
        }
    }
    explicit Aircraft(Type type, const TextureHolder &textures);
    virtual void drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates states) const;

private:
    Type mType;
    sf::Sprite mSprite;
    
};

Aircraft::Aircraft(Type type, const TextureHolder &textures) : mType(type), mSprite(textures.get(toTextureID(type)))
{

    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const
{
    target.draw(mSprite, states);
}