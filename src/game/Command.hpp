#pragma once
#include <iostream>
#include <functional>
namespace Category
{
    enum Type
    {
        None = 0,
        Scene = 1 << 0,
        PlayerAircraft = 1 << 1,
        AlliedAircraft = 1 << 2,
        EnemyAircraft = 1 << 3,
    };
} // namespace Category
struct Command
{
    Command(Category::Type cat) : category(cat) {}
    std::function<void(SceneNode&, sf::Time)> action;
    unsigned int category;
};
