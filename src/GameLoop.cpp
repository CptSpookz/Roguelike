#include <Game.hpp>

#define WINDOW_WIDTH 10
#define WINDOW_HEIGHT 10

int main(){
  std::srand(time(NULL));

  Game game = Game(new sf::RenderWindow(sf::VideoMode(500, 500), "roguelike"/*, sf::Style::Fullscreen*/));

  game.run();

  return 0;
}

