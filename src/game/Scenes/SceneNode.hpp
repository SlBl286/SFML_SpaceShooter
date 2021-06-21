#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <assert.h>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    enum class Layer
    {
        Background,
        Air,
        LayerCount
    };

public:
    SceneNode();
    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode &node);
    void update(sf::Time dt);

private:
    //method
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const final;
    virtual void drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
    void updateChildren(sf::Time dt);
    //data
    std::vector<Ptr> mChildren;
    SceneNode *mParent;
};

void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(),
                              [&](Ptr &p) -> bool
                              { return p.get() == &node; });
    assert(found != mChildren.end());
    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::draw(sf::RenderTarget &target,
                     sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);

    for (auto itr = mChildren.begin();
         itr != mChildren.end(); ++itr)
    {
        (*itr)->draw(target, states);
    }
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
    {
        child->update(dt);
    }
}