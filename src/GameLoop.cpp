#include <Game.hpp>

#define WINDOW_WIDTH 10
#define WINDOW_HEIGHT 10

int main(){
  std::srand(time(NULL));

  Game game = Game(new sf::RenderWindow(sf::VideoMode(1360, 768), "roguelike"/*, sf::Style::Fullscreen*/));

  game.run();

  /*sf::RenderWindow window(sf::VideoMode(200, 200), "roguelike");

  sf::Texture texture;
  if(!texture.loadFromFile("../resources/sprites/tile/floor.png"))
    return 0;

  sf::Sprite sprite;
  sprite.setTexture(TextureManager::getTexture(2));

  while(window.isOpen()){
    window.clear(sf::Color::Black);

    window.draw(sprite);

    window.display();
  }*/

  return 0;
}
