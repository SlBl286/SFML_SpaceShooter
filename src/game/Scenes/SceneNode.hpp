#pragma once
#include "../Resource.hpp"
#include <vector>
#include "../Category.hpp"
struct Command;
class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    // data
public:
    typedef std::unique_ptr<SceneNode> Ptr;

private:
    std::vector<Ptr> mChildren;
    SceneNode *mParent;
    // function
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
    virtual void updateChildren(sf::Time dt);
    virtual unsigned int getCategory() const;

public:
    void onCommand(Command &command, sf::Time dt);
    void update(sf::Time dt);
    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode &node);
    sf::Transform getWorldTransform() const;
    sf::Vector2f getWorldPosition() const;
    SceneNode();
    ~SceneNode();
};
#include "../Command.hpp"
sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode *node = this; node != nullptr; node = node->mParent)
    {
        transform = node->getTransform() * transform;
    }

    return transform;
}
sf::Vector2f SceneNode::getWorldPosition() const
{
    return SceneNode::getWorldTransform() * sf::Vector2f();
}
void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}
void SceneNode::updateCurrent(sf::Time)
{
}
void SceneNode::updateChildren(sf::Time dt)
{
    for (const Ptr &child : mChildren)
        child->update(dt);
}
void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
}
void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);
    for (const Ptr &child : mChildren)
    {
        child->draw(target, states);
    }
}
void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr &p) -> bool
                              { return p.get() == &node; });
    assert(found != mChildren.end());
    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}
unsigned int SceneNode::getCategory() const
{
    return Category::Scene;
}

void SceneNode::onCommand(Command &command, sf::Time dt)
{
    if (command.category & getCategory())
        command.action(*this, dt);
    for (auto &&child : mChildren)
    {
        child->onCommand(command, dt);
    }
}
SceneNode::SceneNode() : mParent(nullptr)
{
}

SceneNode::~SceneNode()
{
}
