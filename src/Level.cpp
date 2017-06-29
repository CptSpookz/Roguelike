#include <Level.hpp>

Level::Level(){}

Level::Level(sf::RenderWindow& window){
  // Load floor textures
  this->addTile("../resources/sprites/tile/floor.png", TILE::FLOOR);
  this->addTile("../resources/sprites/tile/floor_alt.png", TILE::FLOOR_ALT);

  // Load wall textures
  std::cout << this->addTile("../resources/sprites/wall/wall_single.png", TILE::WALL_SINGLE);

  generate();
  createPath(1, 1);
}

void Level::draw(sf::RenderWindow& window){
  for(int i = 0; i < GRID_HEIGHT; i++){
    for(int j = 0; j < GRID_WIDTH; j++){
      window.draw(m_grid[i][j].sprite);
    }
  }
}

int Level::addTile(std::string filePath, TILE tileType){
  int textureID = TextureManager::addTexture(filePath);

  if(textureID < 0)
    return -1;
  else
    this->m_textureIDs[static_cast<int>(tileType)] = textureID;

  return textureID;
}

void Level::generate(){
  for(int i = 0; i < GRID_HEIGHT; i++){
    for(int j = 0; j < GRID_WIDTH; j++){
      if(i%2 && j%2){
        m_grid[i][j].type = TILE::EMPTY;
      }else{
        m_grid[i][j].sprite.setTexture(TextureManager::getTexture(m_textureIDs[static_cast<int>(TILE::WALL_SINGLE)]));
        m_grid[i][j].type = TILE::WALL_SINGLE;
      }
      m_grid[i][j].sprite.setPosition(TILE_SIZE*i, TILE_SIZE*j);
    }
  }
}

void Level::createPath(int columnIndex, int rowIndex){
    sf::Vector2i directions[] = {{2, 0}, {0, 2}, {-2, 0}, {0, -2}};
    std::random_shuffle(std::begin(directions), std::end(directions));
    for(int i = 0; i < 4; i++){
      auto newX = directions[i].x + columnIndex;
      auto newY = directions[i].y + rowIndex;

      if(m_grid[newX][newY].type == TILE::EMPTY){
        auto wallX = directions[i].x/2 + columnIndex;
        auto wallY = directions[i].y/2 + rowIndex;

        m_grid[newX][newY].type = TILE::FLOOR;
        m_grid[newX][newY].sprite.setTexture(TextureManager::getTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));

        m_grid[wallX][wallY].type = TILE::FLOOR;
        m_grid[wallX][wallY].sprite.setTexture(TextureManager::getTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));

        createPath(newX, newY);
      }
    }
}
