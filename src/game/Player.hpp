#pragma once
#include "CommandQueue.hpp"
class Player
{
private:
    /* data */
public:
    void handleEvent(const sf::Event &event, CommandQueue &commands);
    void hanldeRealtimeInput(CommandQueue &commands);
    Player(/* args */);
    ~Player();
};
void Player::handleEvent(const sf::Event &event, CommandQueue &commands){

}
void Player::hanldeRealtimeInput(CommandQueue &commands){


}
Player::Player(/* args */)
{
}

Player::~Player()
{
}
