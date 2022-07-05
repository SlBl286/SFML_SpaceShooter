#pragma once
#include <map>
#include <string>
#include <iostream>
#include <assert.h>
#include <SFML/Graphics.hpp>

template <typename Resource, typename Identifier>
class ResourceHolder
{
private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;

public:
    ResourceHolder();
    ~ResourceHolder();
    void load(Identifier id, const std::string &filename);
    template <typename Parameter>
    void load(Identifier id, const std::string &filename, const Parameter &secondParam);
    Resource &get(Identifier id);
    const Resource &get(Identifier id) const;
};

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder()
{
}
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    auto inserted = mResourceMap.insert(std::make_pair(
        id, std::move(resource)));
    assert(inserted.second);
}
template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &filename, const Parameter &secondParam)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, secondParam))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    auto inserted = mResourceMap.insert(std::make_pair(
        id, std::move(resource)));
    assert(inserted.second);
}
template <typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = mResourceMap.find(id);
    return *found->second;
}
template <typename Resource, typename Identifier>
const Resource &ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = mResourceMap.find(id);
    return *found->second;
}
template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::~ResourceHolder()
{
}
