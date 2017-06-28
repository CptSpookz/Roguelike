#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class TextureManager {
  public:
    sf::String mDirectory;

    static sf::Sprite* loadSpriteFromFile(sf::String);

  private:
};

#endif
