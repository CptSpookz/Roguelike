#include <TextureManager.hpp>

std::map<sf::String, std::pair<int, std::unique_ptr<sf::Texture> > > TextureManager::m_textures;
int TextureManager::m_currentId = 0;

TextureManager::TextureManager(){}

int TextureManager::addTexture(sf::String filePath){
  auto it = m_textures.find(filePath);

  if(it != m_textures.end())
    return it->second.first;

  m_currentId++;

  std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
  if(!texture->loadFromFile(filePath))
    return -1;

  m_textures.insert(std::make_pair(filePath, std::make_pair(m_currentId, std::move(texture))));

  return m_currentId;
}

void TextureManager::removeTexture(int textureId){
  for(auto it = m_textures.begin(); it != m_textures.end(); ++it){
    if(it->second.first == textureId){
      m_textures.erase(it->first);
    }
  }
}

sf::Texture& TextureManager::getTexture(int textureId){
  for(auto it = m_textures.begin(); it != m_textures.end(); ++it){
    if(it->second.first == textureId){
      return *it->second.second;
    }
  }
}
