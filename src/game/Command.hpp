#pragma once
#include <iostream>
#include <functional>
#include "Scenes/SceneNode.hpp"
#include "Category.hpp"
struct Command
{
    Command(){}
    Command(Category::Type cat) : category(cat) {}
    std::function<void(SceneNode&,sf::Time)> action;
    unsigned int category;
};
