#ifndef LEVEL_HPP
#define LEVEL_HPP


// Roguelike
#include <TextureManager.hpp>
#include <Util.hpp>

// SFML
#include <SFML/Graphics.hpp>

// std
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

#define GRID_WIDTH 21
#define GRID_HEIGHT 21

#define TILE_SIZE 50

struct Tile {
  TILE type;
  int columnIndex;
  int rowIndex;
  sf::Sprite sprite;
  int H;
  int G;
  int F;
  Tile* parentNode;
};

class Level {
  public:
    Level();

    Level(sf::RenderWindow&);

    void draw(sf::RenderWindow&);

    void reset();

    int addTile(std::string, TILE);

    void generate();

    void createPath(int, int);

    void createRooms(int);

    void calculateWalls();

    void setColor(int, int, int, int);

    void resetNodes();

    sf::Vector2u getSize();

    sf::Vector2f getActualTileLocation(int, int);

    bool isSolid(int, int);

    bool isFloor(Tile*);

    Tile* getTile(sf::Vector2f);

    Tile* getTile(int, int);

    sf::Vector2f getRandomSpawnLocation();

    int getRoomNumber();

  private:
    Tile m_grid[GRID_HEIGHT][GRID_WIDTH];

    int m_textureIDs[static_cast<int>(TILE::COUNT)];

    int m_roomNumber;

    sf::Vector2i m_origin;
};

#endif
