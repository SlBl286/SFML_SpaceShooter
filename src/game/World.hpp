#pragma once
#include <Entities/Aircraft.hpp>
#include <Resource.hpp>
#include <array>
#include <Scenes/SpriteNode.hpp>
class World : private sf::NonCopyable
{
    // data
public:
    typedef ResourceHolder<sf::Texture, ResourceId::Textures> TextureHolder;
    typedef ResourceHolder<sf::Font, ResourceId::Font> FontHolder;

private:
    enum Layer
    {
        Background,
        Air,
        LayerCount
    };

private:
    sf::RenderWindow &mWindow;
    sf::View mWorldView;
    TextureHolder mTextures;
    SceneNode mSceneGraph;
    std::array<SceneNode *, LayerCount> mSceneLayers;
    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrollSpeed;
    Aircraft *mPlayerAircraft;

    // function
private:
    void loadTextures();
    void buildScene();

public:
    explicit World(sf::RenderWindow &window);
    void update(sf::Time dt);
    void draw();

    ~World();
};

World::World(sf::RenderWindow &window) : mWindow(window),
                                         mWorldView(window.getDefaultView()),
                                         mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f),
                                         mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y),
                                         mPlayerAircraft(nullptr)
{
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures()
{
    mTextures.load(ResourceId::Textures::Eagle, "assets/images/playerShip1_blue.png");
    mTextures.load(ResourceId::Textures::Raptor, "assets/images/Enemies/enemyRed1.png");
    mTextures.load(ResourceId::Textures::Desert, "assets/images/Backgrounds/darkPurple.png");
    mTextures.load(ResourceId::Textures::Enemy, "assets/images/Enemies/enemyRed1.png");
}
void World::buildScene()
{
    for (size_t i = 0; i < LayerCount; i++)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move((layer)));
    }
    sf::Texture &texture = mTextures.get(ResourceId::Textures::Desert);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(sf::Vector2f(0,-100.f));
    mSceneLayers[Air]->attachChild(std::move(leader));
    std::unique_ptr<Aircraft> leftEscort(
        new Aircraft(Aircraft::Raptor, mTextures));
    leftEscort->setPosition(-80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(leftEscort));
    std::unique_ptr<Aircraft> rightEscort(
        new Aircraft(Aircraft::Raptor, mTextures));
    rightEscort->setPosition(80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(rightEscort));
}
void World::update(sf::Time dt)
{
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
    sf::Vector2f position = mPlayerAircraft->getPosition();

    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    if (position.x <= mWorldBounds.left + 150 || position.x >= mWorldBounds.left + mWorldBounds.width - 150)
    {
        velocity.x = -velocity.x;
        mPlayerAircraft->setVelocity(velocity);
    }
    mSceneGraph.update(dt);
}
void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}
World::~World()
{
}
