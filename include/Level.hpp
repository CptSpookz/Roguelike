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
};

class Level {
  public:
    Level();

    Level(sf::RenderWindow&);

    void draw(sf::RenderWindow&);

    int addTile(std::string, TILE);

    void generate();

    void createPath(int, int);

    void createRooms(int);

    void calculateWalls();

    void setColor(int, int, int, int);

    bool isSolid(int, int);

    Tile* getTile(sf::Vector2f);

  private:
    Tile m_grid[GRID_HEIGHT][GRID_WIDTH];

    int m_textureIDs[static_cast<int>(TILE::COUNT)];

    int m_roomNumber;

    sf::Vector2i m_origin;
};

#endif