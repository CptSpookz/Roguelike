#ifndef _ITEM_HPP_
#define _ITEM_HPP_

// Roguelike
#include <Object.hpp>
#include <DataStructures.hpp>

// SFML
#include <SFML/Graphics.hpp>

class Item {
public:
    virtual void itemAction() = 0;

protected:
    Item();

	// item base Sprite
    sf::Sprite m_sprite;

    // item charges left
    int m_charges;
};

/*class ItemBag : public LinkedList<Item>{
private:
	int maxSlots;
public:
	ItemBag();
	bool isFull();
};*/

#endif
