#pragma
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>
namespace Textures
{
    enum class ID
    {
        Lanscape,
        Airplane,
        Missile
    };
    class TextureHolder
    {
    private:
        std::map<Textures::ID,
                 std::unique_ptr<sf::Texture>>
            mTextureMap;

    public:
        void load(Textures::ID id, const std::string &filename);
        const sf::Texture &get(Textures::ID id) const;
        sf::Texture &get(Textures::ID id);
    };

    void TextureHolder::load(Textures::ID id, const std::string &filename)
    {
        std::unique_ptr<sf::Texture> texture(new sf::Texture());
        if (!texture->loadFromFile(filename))
            throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
        auto inserted = mTextureMap.insert(std::make_pair(id, std::move(texture)));
        assert(inserted.second);
    }
    sf::Texture &TextureHolder::get(Textures::ID id)
    {
        auto found = mTextureMap.find(id);
        return *found->second;
    }

} // namespace Texture
