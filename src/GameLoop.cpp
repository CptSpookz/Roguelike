#include <Game.hpp>

int main(){
  Game game = Game(new sf::RenderWindow(sf::VideoMode(200, 200), "roguelike"));

  game.run();

  return 0;
}
