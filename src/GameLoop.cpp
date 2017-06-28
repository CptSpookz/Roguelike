#include <SFML/Graphics.hpp>

int main(){
  sf::RenderWindow window(sf::VideoMode(200, 200), "Roguelike");

  while(window.isOpen()){

    window.clear();
    window.display();
  }

  return 0;
}
