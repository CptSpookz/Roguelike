#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <map>
#include <memory>
#include <utility>
#include <SFML/Graphics.hpp>

class TextureManager {
  public:
    TextureManager();

    static int addTexture(sf::String);

    static void removeTexture(int);

    static sf::Texture& getTexture(int);

  private:
    static std::map<sf::String, std::pair<int, std::unique_ptr<sf::Texture> > > m_textures;
    static int m_currentId;
};

#endif
