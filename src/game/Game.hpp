#pragma once

#include "Resources.hpp"
#include "ResourceID.hpp"

class Game
{
private:
    //data
    sf::RenderWindow mWindow;
    ResourceHolder<sf::Texture, Textures::ID> mTextures;
    sf::Sprite mPlayerPlane;
    sf::Time mTimePerFrame;
    bool mIsMovingUp, mIsMovingDown, mIsMovingRight, mIsMovingLeft;
    float mPlayerSpeed = 200.f;
    //method
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

public:
    Game(float FPS = 60.f);
    ~Game();
    void run();
};
Game::Game(float FPS ) : mWindow(sf::VideoMode(480, 640), "Space Shooter", sf::Style::Close), mTimePerFrame(sf::seconds(1.f / FPS)),
                               mIsMovingUp(false), mIsMovingDown(false), mIsMovingRight(false), mIsMovingLeft(false), mPlayerPlane()
{
    mTextures.load(Textures::ID::Eagle, "media\\assest\\spritesheets\\ship.png", sf::IntRect(32, 0, 16, 24));
    mPlayerPlane.setTexture(mTextures.get(Textures::ID::Eagle));
    mPlayerPlane.setScale(2.f, 2.f);
    mPlayerPlane.setPosition(480 / 2 - 20, 640 - 48);
}

Game::~Game()
{
}
void Game::run()
{
    sf::Clock clock;
    sf::Time timeFromLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        // sf::Time deltaTime = clock.restart();
        processEvents();
        timeFromLastUpdate += clock.restart();
        while (timeFromLastUpdate > mTimePerFrame)
        {
            timeFromLastUpdate -= mTimePerFrame;
            processEvents();
            update(mTimePerFrame);
        }

        render();
    }
}
void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;

        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;

        case sf::Event::Closed:
            mWindow.close();
            break;

        default:
            break;
        }
    }
}
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
    {
        mIsMovingUp = isPressed;
    }

    else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
    {
        mIsMovingDown = isPressed;
    }

    else if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
    {
        mIsMovingLeft = isPressed;
    }

    else if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
    {
        mIsMovingRight = isPressed;
    }
}
void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= mPlayerSpeed;
    if (mIsMovingDown)
        movement.y += mPlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= mPlayerSpeed;
    if (mIsMovingRight)
        movement.x += mPlayerSpeed;
    mPlayerPlane.move(movement * deltaTime.asSeconds());
}
void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayerPlane);
    mWindow.display();
}