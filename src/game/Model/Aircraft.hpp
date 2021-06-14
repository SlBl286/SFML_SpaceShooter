#pragma once

#include "Extends/Base.hpp"

class Aircraft : public Entity
{
public:
    enum class Type
    {
        Eagle,
        Raptor,
    };

public:
    explicit Aircraft(Type type);

private:
    Type mType;
};

Aircraft::Aircraft(Type type) : mType(type)
{
    
}