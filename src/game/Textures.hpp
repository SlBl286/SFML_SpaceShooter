#pragma
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
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
        const sf::Texture& get(Textures::ID id) const;
        sf::Texture &get(Textures::ID id);
    };

    void TextureHolder::load(Textures::ID id, const std::string &filename)
    {
        std::unique_ptr<sf::Texture> texture(new sf::Texture());
        texture->loadFromFile(filename);
        mTextureMap.insert(std::make_pair(id, std::move(texture)));
    }
    sf::Texture &TextureHolder::get(Textures::ID id)
    {
        auto found = mTextureMap.find(id);
        return *found->second;
    }

} // namespace Texture
