#pragma once
#include "../../Resource.hpp"
#include "../../Scenes/SceneNode.hpp"
#include "../../ResourceEnum.hpp"

class Entity : public SceneNode
{
    // data
public:
private:
    sf::Vector2f mVelocity;
    // function
private:
    virtual void updateCurrent(sf::Time dt);

public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;

    Entity();
    ~Entity();
};
void Entity::updateCurrent(sf::Time dt)
{
    move(mVelocity * dt.asSeconds());
}
void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}
void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{

    return mVelocity;
}

Entity::Entity()
{
}

Entity::~Entity()
{
}
