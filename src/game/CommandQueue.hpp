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
    Command& pop();
    CommandQueue();
    ~CommandQueue();
};
void CommandQueue::push(const Command &command)
{
}
bool CommandQueue::isEmpty() const
{
}
Command& CommandQueue::pop()
{
    
}
CommandQueue::CommandQueue() 
{
}

CommandQueue::~CommandQueue()
{
}
