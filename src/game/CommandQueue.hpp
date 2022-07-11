#pragma once
#include "Command.hpp"
#include <queue>
class CommandQueue
{
    // data
public:
private:
    std::queue<Command> mQueue;

public:
    void push(const Command &command);
    bool isEmpty() const;
    Command pop();
    CommandQueue(/* args */);
    ~CommandQueue();
};

CommandQueue::CommandQueue(/* args */)
{
}

CommandQueue::~CommandQueue()
{
}
