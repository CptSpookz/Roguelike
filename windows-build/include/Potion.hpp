#ifndef POTION_HPP
#define POTION_HPP

// Roguelike
#include <Object.hpp>
#include <Hero.hpp>
#include <DataStructures.hpp>

class Potion : public Object {
protected:
    //potion type
    POTION_TYPE m_type;

    //potion state
    bool m_isUsed;

    //potion textures' index array
    int m_textureIDs[static_cast<int>(POTION_STATE::COUNT)];

    //potion current texture index
    int m_currentTexID;

public:
    Potion(POTION_TYPE);

    void use(Hero&);
    void refill();
    void update(float);
    void draw(sf::RenderWindow&);

    void setPosition(double,double);
    bool isUsed() const {return m_isUsed;};
};

#endif
