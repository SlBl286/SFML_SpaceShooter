#pragma once

#include "Resource.hpp"
#include "Entities/Aircraft.hpp"
#include <World.hpp>
#include <Player.hpp>
namespace Qy
{
    class Game
    {
    private:
        // data
        sf::RenderWindow mWindow;
        sf::Time TimePerFrame;
        World mWorld;
        float playerSpeed;
        bool mIsPause;
        Player mPlayer;
        // method
        void processEvents();
        void update(sf::Time dt);
        void render();
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    public:
        Game(float FPS = 60.f);
        ~Game();
        void run();
    };
    Game::Game(float FPS) : mWindow(sf::VideoMode(480, 800), "Space Shooter", sf::Style::Close),
                            TimePerFrame(sf::seconds(1.f / FPS)),
                            mWorld(mWindow),
                            playerSpeed(200.f),
                            mIsPause(false)
    {
    }

    Game::~Game()
    {
    }
    void Game::run()
    {
        sf::Vector2i windowCenter(mWindow.getSize() / 2u);
        sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
        sf::Vector2i delta = windowCenter - mousePosition;
        sf::Mouse::setPosition(windowCenter, mWindow);
        sf::Clock clock;
        sf::Time timeFromLastUpdate = sf::Time::Zero;
        while (mWindow.isOpen())
        {

            processEvents();
            timeFromLastUpdate += clock.restart();

            while (timeFromLastUpdate > TimePerFrame)
            {
                timeFromLastUpdate -= TimePerFrame;
                processEvents();
                if (!mIsPause)
                    update(TimePerFrame);
            }

            render();
        }
    }
    void Game::processEvents()
    {
        CommandQueue &commands = mWorld.getCommandQueue();
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            mPlayer.handleEvent(event, commands);
            if (event.type == sf::Event::Closed)
                mWindow.close();
        }
        mPlayer.hanldeRealtimeInput(commands);
    }

    void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
    {
    }
    void Game::update(sf::Time dt)
    {
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y -= playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y -= playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y -= playerSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y -= playerSpeed;

        mWorld.update(dt);
    }
    void Game::render()
    {
        mWindow.clear();
        mWorld.draw();
        mWindow.setView(mWindow.getDefaultView());

        mWindow.display();
    }

} // namespace Qy
