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

  m_hero.setPosition(1.3*TILE_SIZE, 1.3*TILE_SIZE);

  // botões do menu inicial
  auto outlineButton = TextureManager::addTexture("../resources/sprites/buttons/spr_outline_button.png");
  auto defaultBorder = TextureManager::addTexture("../resources/sprites/buttons/spr_default_border.png");

  m_menuButtons.setOutline(TextureManager::getTexture(outlineButton));
  m_menuButtons.addButton(m_window, TextureManager::getTexture(defaultBorder));
  m_menuButtons.addButton(m_window, TextureManager::getTexture(defaultBorder));
  m_menuButtons.addButton(m_window, TextureManager::getTexture(defaultBorder));
  m_menuButtons.addButton(m_window, TextureManager::getTexture(defaultBorder));
  m_menuButtons.addButton(m_window, TextureManager::getTexture(defaultBorder));

  loadUI();

  m_level.generate();
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
  sf::Vector2i manaSize(240*100/100, 16);

  if(m_gameState == GAME_STATE::GAME_RUN && m_hero.getHP() == 0)
    m_gameState = GAME_STATE::GAME_END;

  switch(m_gameState){
    case GAME_STATE::MAIN_MENU:

      break;

    case GAME_STATE::GAME_RUN:
      m_healthBar.setTextureRect(sf::IntRect(zero, healthSize));
      m_manaBar.setTextureRect(sf::IntRect(zero, manaSize));

      m_attackValue.setString(std::to_string(m_hero.getDmg()));
      m_speedValue.setString(std::to_string(m_hero.getMovSpd()));

      m_hero.update(m_level, delta);

      m_view.setCenter(m_hero.getCenterPosition());
      m_window.setView(m_view);

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

  // status
  // texturas
  auto attackStatId = TextureManager::addTexture("../resources/sprites/ui/attack_stat.png");
  auto defenseStatId = TextureManager::addTexture("../resources/sprites/ui/defense_stat.png");
  auto speedStatId = TextureManager::addTexture("../resources/sprites/ui/speed_stat.png");
  auto luckStatId = TextureManager::addTexture("../resources/sprites/ui/luck_stat.png");

  // sprites
  m_attackStat.setTexture(TextureManager::getTexture(attackStatId));
  m_attackStat.setPosition(10, m_window.getSize().y - 26);
  m_defenseStat.setTexture(TextureManager::getTexture(defenseStatId));
  m_defenseStat.setPosition(148, m_window.getSize().y - 26);
  m_speedStat.setTexture(TextureManager::getTexture(speedStatId));
  m_speedStat.setPosition(296, m_window.getSize().y - 26);
  m_luckStat.setTexture(TextureManager::getTexture(luckStatId));
  m_luckStat.setPosition(444, m_window.getSize().y - 26);

  // texto
  m_attackValue.setFont(m_uiFont);
  m_attackValue.setString("3.5");
  m_attackValue.setCharacterSize(22);
  m_attackValue.setFillColor(sf::Color::White);
  m_attackValue.setPosition(31, m_window.getSize().y - 33);

  m_defenseValue.setFont(m_uiFont);
  m_defenseValue.setString("4.5");
  m_defenseValue.setCharacterSize(22);
  m_defenseValue.setFillColor(sf::Color::White);
  m_defenseValue.setPosition(169, m_window.getSize().y - 33);

  m_speedValue.setFont(m_uiFont);
  m_speedValue.setString("6.5");
  m_speedValue.setCharacterSize(22);
  m_speedValue.setFillColor(sf::Color::White);
  m_speedValue.setPosition(317, m_window.getSize().y - 33);

  m_luckValue.setFont(m_uiFont);
  m_luckValue.setString("0.0");
  m_luckValue.setCharacterSize(22);
  m_luckValue.setFillColor(sf::Color::White);
  m_luckValue.setPosition(465, m_window.getSize().y - 33);
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
  m_blackBar.setPosition(left, down - 36);
  m_attackStat.setPosition(left + 10, down - 26);
  m_attackValue.setPosition(left + 31, down - 33);
  m_defenseStat.setPosition(left + 148, down - 26);
  m_defenseValue.setPosition(left + 169, down - 33);
  m_speedStat.setPosition(left + 296, down - 26);
  m_speedValue.setPosition(left + 317, down - 33);
  m_luckStat.setPosition(left + 444, down - 26);
  m_luckValue.setPosition(left + 465, down - 33);
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

  // Status
  m_window.draw(m_attackStat);
  m_window.draw(m_defenseStat);
  m_window.draw(m_speedStat);
  m_window.draw(m_luckStat);

  m_window.draw(m_attackValue);
  m_window.draw(m_defenseValue);
  m_window.draw(m_speedValue);
  m_window.draw(m_luckValue);
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
