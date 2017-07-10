#include <Game.hpp>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

int main(){
  std::srand(time(NULL));

  Game game = Game(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "rand()venture", sf::Style::Close));

  game.run();

  return 0;
}
