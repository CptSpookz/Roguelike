#ifndef BUTTONLIST_HPP
#define BUTTONLIST_HPP

// Roguelike
#include <DataStructures.hpp>

// SFML
#include <SFML/Graphics.hpp>

class ButtonList {
  public:
    ButtonList();

    void setOutline(sf::Texture&);

    void addButton(sf::RenderWindow&, sf::Texture&);

    void setTextureIndex(int, sf::Texture&);

    void draw(sf::RenderWindow&);

    void toNext();

    void toPrevious();

    int getIndex();

  protected:
    void centerHorizontal(sf::RenderWindow&);

  private:
    // lista de sprite dos botões
    LinkedList<sf::Sprite*> m_buttonSprites;

    // sprite do outline de seleção
    sf::Sprite m_outlineSprite;

    // indice do número atual
    int m_actualIndex;
};

#endif
