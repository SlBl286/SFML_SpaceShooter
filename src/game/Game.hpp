#pragma once

#include "Textures.hpp"
namespace Qy
{
    class Game
    {
    private:
        // data
        sf::RenderWindow mWindow;
        Textures::TextureHolder textures;
        sf::Sprite playerPlane;
        sf::Time TimePerFrame;
        bool isMovingUp, isMovingDown, isMovingRight, isMovingLeft;
        float playerSpeed = 200.f;
        // method
        void processEvents();
        void update(sf::Time deltaTime);
        void render();
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    public:
        Game(float FPS = 60.f);
        ~Game();
        void run();
    };
    Game::Game(float FPS) : mWindow(sf::VideoMode(480, 640), "Space Shooter", sf::Style::Close), TimePerFrame(sf::seconds(1.f / FPS)),
                            isMovingUp(false), isMovingDown(false), isMovingRight(false), isMovingLeft(false), playerPlane()
    {
        textures.load(Textures::ID::Airplane, "assets/images/playerShip1_blue.png");
        playerPlane.setTexture(textures.get(Textures::ID::Airplane));
        playerPlane.setScale(0.5f, 0.5f);
        // playerPlane.setTextureRect(sf::IntRct(16, 0, 16, 24));
        playerPlane.setPosition(640 / 2 - 20, 480 / 2 - 20);
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
            while (timeFromLastUpdate > TimePerFrame)
            {
                timeFromLastUpdate -= TimePerFrame;
                processEvents();
                update(TimePerFrame);
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
            isMovingUp = isPressed;
        }

        else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
        {
            isMovingDown = isPressed;
        }

        else if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
        {
            isMovingLeft = isPressed;
        }

        else if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
        {
            isMovingRight = isPressed;
        }
    }
    void Game::update(sf::Time deltaTime)
    {
        sf::Vector2f movement(0.f, 0.f);
        if (isMovingUp)
            movement.y -= playerSpeed;
        if (isMovingDown)
            movement.y += playerSpeed;
        if (isMovingLeft)
            movement.x -= playerSpeed;
        if (isMovingRight)
            movement.x += playerSpeed;
        playerPlane.move(movement * deltaTime.asSeconds());
    }
    void Game::render()
    {
        mWindow.clear();
        mWindow.draw(playerPlane);
        mWindow.display();
    }

} // namespace Qy
