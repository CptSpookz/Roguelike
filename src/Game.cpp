#include <Game.hpp>
#include <iostream>

Game::Game(sf::RenderWindow* window):
m_window(*window),
m_gameState(GAME_STATE::MAIN_MENU),
m_level(Level(*window)),
m_blackBar(sf::RectangleShape(sf::Vector2f(window->getSize().x, 36))){
  m_view.reset(sf::FloatRect(0, 0, 500, 500));

  m_window.setFramerateLimit(60);
  m_window.setView(m_view);

  if(!m_uiFont.loadFromFile("../resources/font/uiFont.ttf")){
    std::cout << "Erro ao carregar a fonte" << std::endl;
  }

  // botões do menu inicial
  auto outlineButton = TextureManager::addTexture("../resources/sprites/buttons/spr_outline_button.png");
  auto warriorBorder = TextureManager::addTexture("../resources/sprites/buttons/spr_warrior_border.png");
  auto mageBorder = TextureManager::addTexture("../resources/sprites/buttons/spr_mage_border.png");
  auto archerBorder = TextureManager::addTexture("../resources/sprites/buttons/spr_archer_border.png");
  auto thiefBorder = TextureManager::addTexture("../resources/sprites/buttons/spr_thief_border.png");
  auto paladinBorder = TextureManager::addTexture("../resources/sprites/buttons/spr_paladin_border.png");
  auto valkyrieBorder = TextureManager::addTexture("../resources/sprites/buttons/spr_valkyrie_border.png");

  m_menuButtons.setOutline(TextureManager::getTexture(outlineButton));
  m_menuButtons.addButton(m_window, TextureManager::getTexture(warriorBorder));
  m_menuButtons.addButton(m_window, TextureManager::getTexture(mageBorder));
  m_menuButtons.addButton(m_window, TextureManager::getTexture(archerBorder));
  m_menuButtons.addButton(m_window, TextureManager::getTexture(thiefBorder));
  m_menuButtons.addButton(m_window, TextureManager::getTexture(paladinBorder));
  m_menuButtons.addButton(m_window, TextureManager::getTexture(valkyrieBorder));

  m_enemyList.push_back(new Enemy(10));

  loadUI();

  m_level.generate();

  m_hero.setPosition(m_level.getActualTileLocation(1, 1).x, m_level.getActualTileLocation(1, 1).y);
}

void Game::run(){
  float currentTime = m_gameClock.restart().asSeconds();

  while(m_window.isOpen()){
    sf::Event event;
    while(m_window.pollEvent(event)){
      if(event.type == sf::Event::Closed)
        m_window.close();
      if(m_gameState == GAME_STATE::MAIN_MENU){
        menuButtonsEvent(event);
      }
    }

    float newTime = m_gameClock.getElapsedTime().asSeconds();
    float timeDelta = std::max(0.f, newTime - currentTime);
    currentTime = newTime;

    update(timeDelta);

    draw(timeDelta);
  }
}

void Game::update(float delta){
  sf::Vector2i zero(0, 0);
  sf::Vector2i healthSize(240*m_hero.getHP()/m_hero.getMaxHP(), 16);
  sf::Vector2i manaSize(240*m_hero.getMP()/m_hero.getMaxMP(), 16);

  if(m_gameState == GAME_STATE::GAME_RUN && m_hero.getHP() == 0)
    m_gameState = GAME_STATE::GAME_END;

  switch(m_gameState){
    case GAME_STATE::MAIN_MENU:

      break;

    case GAME_STATE::GAME_RUN:
      m_healthBar.setTextureRect(sf::IntRect(zero, healthSize));
      m_manaBar.setTextureRect(sf::IntRect(zero, manaSize));

      m_hero.update(m_level, delta);

      m_view.setCenter(m_hero.getCenterPosition());
      m_window.setView(m_view);

      for(Enemy* enemy: m_enemyList){
        enemy->calculateSteps(m_level, m_hero.getPosition());
        enemy->update(delta);
      }

      updateUI(m_view);

      break;

    case GAME_STATE::GAME_END:

      break;
  }
}

void Game::draw(float delta){
  m_window.clear(sf::Color::Black);

  switch(m_gameState){
    case GAME_STATE::MAIN_MENU:
      m_menuButtons.draw(m_window);
      break;
    case GAME_STATE::GAME_RUN:
      // renderiza o mapa
      m_level.draw(m_window);

      m_hero.draw(m_window, delta);

      for(Enemy* enemy: m_enemyList){
        enemy->draw(m_window);
      }

      // renderiza a ui
      drawUI();

      break;
    case GAME_STATE::GAME_END:
      // código do fim de jogo
      break;
  }

  m_window.display();
}

void Game::loadUI(){
  // barra preta
  m_blackBar.setPosition(0, m_window.getSize().y - 36);
  m_blackBar.setFillColor(sf::Color::Black);

  // carrega as texturas das barras e altera os sprites
  // texturas
  auto barOutlineId = TextureManager::addTexture("../resources/sprites/ui/outline_bar.png");
  auto healthBarId = TextureManager::addTexture("../resources/sprites/ui/health_bar.png");
  auto manaBarId = TextureManager::addTexture("../resources/sprites/ui/mana_bar.png");

  // sprites
  // barra de vida
  m_healthBarOutline.setTexture(TextureManager::getTexture(barOutlineId));
  m_healthBarOutline.setPosition(10, 10);
  m_healthBar.setTexture(TextureManager::getTexture(healthBarId));
  m_healthBar.setPosition(10, 10);
  // barra de mana
  m_manaBarOutline.setTexture(TextureManager::getTexture(barOutlineId));
  m_manaBarOutline.setPosition(10, 36);
  m_manaBar.setTexture(TextureManager::getTexture(manaBarId));
  m_manaBar.setPosition(10, 36);

  // poções
  auto healthPotionId = TextureManager::addTexture("../resources/sprites/ui/spr_health_potion.png");
  auto manaPotionId = TextureManager::addTexture("../resources/sprites/ui/spr_mana_potion.png");
  auto defensePotionId = TextureManager::addTexture("../resources/sprites/ui/spr_defense_potion.png");
  auto speedPotionId = TextureManager::addTexture("../resources/sprites/ui/spr_speed_potion.png");

  m_healthPotion.setTexture(TextureManager::getTexture(healthPotionId));
  m_healthPotion.setPosition(10, m_window.getSize().y - 55);
  m_manaPotion.setTexture(TextureManager::getTexture(manaPotionId));
  m_manaPotion.setPosition(155, m_window.getSize().y - 55);
  m_defensePotion.setTexture(TextureManager::getTexture(defensePotionId));
  m_defensePotion.setPosition(300, m_window.getSize().y - 55);
  m_speedPotion.setTexture(TextureManager::getTexture(speedPotionId));
  m_speedPotion.setPosition(445, m_window.getSize().y - 55);
}

void Game::updateUI(sf::View view){
  auto viewTranslation = view.getCenter() - view.getSize()/2.f;
  auto left = viewTranslation.x;
  auto top = viewTranslation.y;
  auto down = view.getSize().y + top;

  // Barras no topo
  m_healthBarOutline.setPosition(left + 10, top + 10);
  m_healthBar.setPosition(left + 10, top + 10);

  m_manaBarOutline.setPosition(left + 10, top + 36);
  m_manaBar.setPosition(left + 10, top + 36);

  // Status no fundo
  m_blackBar.setPosition(left, down - 35);
  m_healthPotion.setPosition(left + 10, down - 55);
  m_manaPotion.setPosition(left + 155, down - 55);
  m_defensePotion.setPosition(left + 300, down - 55);
  m_speedPotion.setPosition(left + 445, down - 55);
}

void Game::drawUI(){
  // barra preta
  m_window.draw(m_blackBar);

  // barras
  // vida
  m_window.draw(m_healthBarOutline);
  m_window.draw(m_healthBar);
  // mana
  m_window.draw(m_manaBarOutline);
  m_window.draw(m_manaBar);

  // poções
  m_window.draw(m_healthPotion);
  m_window.draw(m_manaPotion);
  m_window.draw(m_defensePotion);
  m_window.draw(m_speedPotion);
}

void Game::menuButtonsEvent(sf::Event event){
  if(event.type == sf::Event::KeyPressed){
    if(event.key.code == sf::Keyboard::Right){
      m_menuButtons.toNext();
    }else if(event.key.code == sf::Keyboard::Left){
      m_menuButtons.toPrevious();
    }else if(event.key.code == sf::Keyboard::Return){
      m_hero.initHero(static_cast<HERO_CLASS>(m_menuButtons.getIndex()));
      m_gameState = GAME_STATE::GAME_RUN;
    }
  }
}
