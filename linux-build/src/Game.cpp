#include <Game.hpp>
#include <iostream>
#include <string>

sf::Music m_track;

Game::Game(sf::RenderWindow* window):
m_window(*window),
m_gameState(GAME_STATE::MAIN_MENU),
m_level(Level(*window)),
m_blackBar(sf::RectangleShape(sf::Vector2f(window->getSize().x, 36))),
m_healthPotion(Potion(POTION_TYPE::HP_POT)),
m_damagePotion(Potion(POTION_TYPE::ATK_POT)),
m_defensePotion(Potion(POTION_TYPE::DEF_POT)),
m_speedPotion(Potion(POTION_TYPE::SPD_POT)){
  m_view.reset(sf::FloatRect(0, 0, 500, 500));

  m_window.setFramerateLimit(60);
  m_window.setView(m_view);

  if(!m_uiFont.loadFromFile("../resources/font/uiFont.ttf")){
    std::cout << "Erro ao carregar a fonte" << std::endl;
  }

  // titulo do jogo
  auto titleId = TextureManager::addTexture("../resources/sprites/ui/spr_title.png");
  sf::Vector2u titleSize = TextureManager::getTexture(titleId).getSize();
  sf::Vector2u windowSize = m_window.getSize();
  m_title.setTexture(TextureManager::getTexture(titleId));
  m_title.setOrigin(titleSize.x/2, titleSize.y/2);
  m_title.setPosition(windowSize.x/2, windowSize.y/2 - 150);

  // tutorial do jogo
  auto controlsId = TextureManager::addTexture("../resources/sprites/ui/spr_controls.png");
  sf::Vector2u controlsSize = TextureManager::getTexture(controlsId).getSize();
  m_controls.setTexture(TextureManager::getTexture(controlsId));
  m_controls.setOrigin(controlsSize.x/2, controlsSize.y/2);
  m_controls.setPosition(windowSize.x/2, windowSize.y/2 + 150);

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

  setMusic(m_gameState);

  loadUI();

  m_level.generate();

  m_hero.setPosition(m_level.getActualTileLocation(1, 1).x, m_level.getActualTileLocation(1, 1).y);

  populateLevel();
}

void Game::run(){
  float currentTime = m_gameClock.restart().asSeconds();

  while(m_window.isOpen()){
    sf::Event event;
    while(m_window.pollEvent(event)){
      if(event.type == sf::Event::Closed){
        m_window.close();
      }
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
  /*sf::Vector2i manaSize(240*m_hero.getMP()/m_hero.getMaxMP(), 16);*/

  if(m_gameState == GAME_STATE::GAME_RUN && m_hero.getHP() == 0){
    m_gameState = GAME_STATE::GAME_END;
  }

  if(m_gameState == GAME_STATE::GAME_RUN && m_liveEnemies == 0){
    m_track.stop();
    setMusic(m_gameState);
    m_track.play();
    m_level.generate();
    populateLevel();
    m_hero.setPosition(m_level.getActualTileLocation(1, 1).x, m_level.getActualTileLocation(1, 1).y);
    m_hero.setHP(m_hero.getMaxHP());
    m_healthPotion.refill();
    m_damagePotion.refill();
    m_defensePotion.refill();
    m_speedPotion.refill();
  }

  /*if(m_gameState == GAME_STATE::BOSS_FIGHT && m_hero.getHP() == 0){
    m_gameState = GAME_STATE::GAME_END;
  }*/

  keyboardUpdate();

  switch(m_gameState){
    case GAME_STATE::MAIN_MENU:

      break;

    case GAME_STATE::GAME_RUN:
      m_healthBar.setTextureRect(sf::IntRect(zero, healthSize));
      /*m_manaBar.setTextureRect(sf::IntRect(zero, manaSize));*/

      m_hero.update(m_level, delta);

      m_view.setCenter(m_hero.getCenterPosition());
      m_window.setView(m_view);

      updateProjectiles(delta);

      updateEnemy(delta);

      updateUI(m_view, delta);
      break;

    case GAME_STATE::BOSS_FIGHT:
      if (!m_track.getStatus()){
        m_track.play();
      }
    //TODO: desenhar o boss, mudar os tiles de wall pra floor
    break;

    case GAME_STATE::GAME_END:
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        m_gameState = GAME_STATE::MAIN_MENU;
        m_window.setView(m_window.getDefaultView());
      }
    break;
  }
}

void Game::draw(float delta){
  switch(m_gameState){
    case GAME_STATE::MAIN_MENU:
      // fundo cinza na tela do menu
      m_window.clear(sf::Color(49,47,44));
      // titulo do jogo
      m_window.draw(m_title);
      // controles do jogo
      m_window.draw(m_controls);
      // botões do menu
      m_menuButtons.draw(m_window);
    break;
    case GAME_STATE::GAME_RUN:
      m_window.clear(sf::Color::Black);
      // renderiza o mapa
      m_level.draw(m_window);

      m_hero.draw(m_window, delta);

      for(const auto& enemy: m_enemyList){
        enemy->Object::draw(m_window, delta);
      }

      for(const auto& projectile: m_playerProjectiles){
        projectile->draw(m_window);
      }

      // renderiza a ui
      drawUI();

    break;
    case GAME_STATE::BOSS_FIGHT:
      //TODO: transformar paredes em chão e renderizar o boss
    break;
    case GAME_STATE::GAME_END:
      //TODO: tela de fim de jogo
      m_window.clear(sf::Color(49,47,44));

      m_window.draw(m_gameOver);
      m_window.draw(m_pressReset);
      m_window.draw(m_enemiesFinal);
      m_window.draw(m_roomFinal);
    break;
  }

  m_window.display();
}

void Game::loadUI(){
  // barra preta
  m_blackBar.setPosition(0, m_window.getSize().y - 36);
  m_blackBar.setFillColor(sf::Color::Black);

  // inimigos mortos
  auto enemiesKilledId = TextureManager::addTexture("../resources/sprites/ui/spr_enemies_killed.png");
  m_enemiesKilled.setTexture(TextureManager::getTexture(enemiesKilledId));
  m_enemiesKilled.setPosition(260, 10);

  m_numberEnemies.setFont(m_uiFont);
  m_numberEnemies.setFillColor(sf::Color::White);
  m_numberEnemies.setCharacterSize(16);

  // carrega as texturas das barras e altera os sprites
  // texturas
  auto barOutlineId = TextureManager::addTexture("../resources/sprites/ui/outline_bar.png");
  auto healthBarId = TextureManager::addTexture("../resources/sprites/ui/health_bar.png");
  /*auto manaBarId = TextureManager::addTexture("../resources/sprites/ui/mana_bar.png");*/

  // sprites
  // barra de vida
  m_healthBarOutline.setTexture(TextureManager::getTexture(barOutlineId));
  m_healthBarOutline.setPosition(10, 10);
  m_healthBar.setTexture(TextureManager::getTexture(healthBarId));
  m_healthBar.setPosition(10, 10);
  // barra de mana
  /*m_manaBarOutline.setTexture(TextureManager::getTexture(barOutlineId));
  m_manaBarOutline.setPosition(10, 36);
  m_manaBar.setTexture(TextureManager::getTexture(manaBarId));
  m_manaBar.setPosition(10, 36);*/

  // poções
  m_healthPotion.setPosition(100, m_window.getSize().y - 55);
  m_damagePotion.setPosition(200, m_window.getSize().y - 55);
  m_defensePotion.setPosition(350, m_window.getSize().y - 55);
  m_speedPotion.setPosition(450, m_window.getSize().y - 55);

  // Textos da tela de Game over
  m_gameOver.setFont(m_uiFont);
  m_gameOver.setFillColor(sf::Color::White);
  m_gameOver.setCharacterSize(40);
  m_gameOver.setString("Fim de jogo");

  auto gameOverBounds = m_gameOver.getLocalBounds();
  m_gameOver.setOrigin(gameOverBounds.left + gameOverBounds.width/2.0f, gameOverBounds.top + gameOverBounds.height/2.0f);

  m_pressReset.setFont(m_uiFont);
  m_pressReset.setFillColor(sf::Color::White);
  m_pressReset.setCharacterSize(40);
  m_pressReset.setString("Aperte R");

  auto pressResetBounds = m_pressReset.getLocalBounds();
  m_pressReset.setOrigin(pressResetBounds.left + pressResetBounds.width/2.0f, pressResetBounds.top + pressResetBounds.height/2.0f);

  m_enemiesFinal.setFont(m_uiFont);
  m_enemiesFinal.setFillColor(sf::Color::White);
  m_enemiesFinal.setCharacterSize(40);

  m_roomFinal.setFont(m_uiFont);
  m_roomFinal.setFillColor(sf::Color::White);
  m_roomFinal.setCharacterSize(40);
}

void Game::updateUI(sf::View view, float delta){
  auto viewTranslation = view.getCenter() - view.getSize()/2.f;
  auto left = viewTranslation.x;
  auto top = viewTranslation.y;
  auto down = view.getSize().y + top;

  // inimigos mortos
  m_enemiesKilled.setPosition(left + 260, top + 10);
  m_numberEnemies.setPosition(left + 286, top + 6);
  m_numberEnemies.setString(std::to_string(m_enemiesDead));

  // Barras no topo
  m_healthBarOutline.setPosition(left + 10, top + 10);
  m_healthBar.setPosition(left + 10, top + 10);

  /*m_manaBarOutline.setPosition(left + 10, top + 36);
  m_manaBar.setPosition(left + 10, top + 36);*/

  // Status no fundo
  m_blackBar.setPosition(left, down - 35);
  m_healthPotion.update(delta);
  m_healthPotion.setPosition(left + 50, down - 55);
  //m_manaPotion.setPosition();
  m_damagePotion.update(delta);
  m_damagePotion.setPosition(left + 150, down - 55);
  m_defensePotion.update(delta);
  m_defensePotion.setPosition(left + 350, down - 55);
  m_speedPotion.update(delta);
  m_speedPotion.setPosition(left + 450, down - 55);

  // textos da tela de game over
  m_gameOver.setPosition(left + 250, top + 130);
  m_pressReset.setPosition(left + 250, top + 210);

  m_enemiesFinal.setString("Inimigos mortos: " + std::to_string(m_enemiesDead));
  auto enemiesBound = m_enemiesFinal.getLocalBounds();
  m_enemiesFinal.setOrigin(enemiesBound.left + enemiesBound.width/2.0f, enemiesBound.top + enemiesBound.height/2.0f);
  m_enemiesFinal.setPosition(left + 250, top + 290);

  m_roomFinal.setString("Andar final: " + std::to_string(m_level.getRoomNumber()));
  auto roomBound = m_roomFinal.getLocalBounds();
  m_roomFinal.setOrigin(roomBound.left + roomBound.width/2.0f, roomBound.top + roomBound.height/2.0f);
  m_roomFinal.setPosition(left + 250, top + 370);
}

void Game::drawUI(){
  // barra preta
  m_window.draw(m_blackBar);

  // inimigos mortos
  m_window.draw(m_enemiesKilled);
  m_window.draw(m_numberEnemies);

  // barras
  // vida
  m_window.draw(m_healthBarOutline);
  m_window.draw(m_healthBar);
  // mana
  /*m_window.draw(m_manaBarOutline);
  m_window.draw(m_manaBar);*/

  // poções
  m_healthPotion.draw(m_window);
  //m_manaPotion.draw(m_window);
  m_damagePotion.draw(m_window);
  m_defensePotion.draw(m_window);
  m_speedPotion.draw(m_window);
}

void Game::setMusic(GAME_STATE state){
  std::string label;
  switch (state) {
    case GAME_STATE::MAIN_MENU:
      label = "level_";
    break;
    case GAME_STATE::GAME_RUN:
      label = "level_";
    break;
    case GAME_STATE::BOSS_FIGHT:
      label = "boss_";
    break;
  }

  int trackNum = rand() % 5 + 1;

  std::string trackPath = "../resources/music/"+ label + std::to_string(trackNum) + ".wav";

  if(!m_track.openFromFile(trackPath)){
    std::cout << "Erro ao carregar musica!" << std::endl;
  }

  m_track.setVolume(75);
  m_track.setLoop(true);
}

void Game::menuButtonsEvent(sf::Event event){
  if(event.type == sf::Event::KeyPressed){
    if(event.key.code == sf::Keyboard::Right){
      m_menuButtons.toNext();
    }else if(event.key.code == sf::Keyboard::Left){
      m_menuButtons.toPrevious();
    }else if(event.key.code == sf::Keyboard::Return){
      resetLevel();
      auto heroClass = static_cast<HERO_CLASS>(m_menuButtons.getIndex());
      m_hero.initHero(heroClass);
      switch(heroClass){
        case HERO_CLASS::WARRIOR:
          m_projectileTextureID = TextureManager::addTexture("../resources/sprites/projectiles/spr_blade.png");
          break;
        case HERO_CLASS::MAGE:
          m_projectileTextureID = TextureManager::addTexture("../resources/sprites/projectiles/spr_magic_ball.png");
          break;
        case HERO_CLASS::ARCHER:
          m_projectileTextureID = TextureManager::addTexture("../resources/sprites/projectiles/spr_arrow.png");
          break;
        case HERO_CLASS::THIEF:
          m_projectileTextureID = TextureManager::addTexture("../resources/sprites/projectiles/spr_shuriken.png");
          break;
        case HERO_CLASS::PALADIN:
          m_projectileTextureID = TextureManager::addTexture("../resources/sprites/projectiles/spr_hammer.png");
          break;
        case HERO_CLASS::VALKYRIE:
          m_projectileTextureID = TextureManager::addTexture("../resources/sprites/projectiles/spr_spear.png");
          break;
      }
      m_track.play();
      m_enemiesDead = 0;
      m_gameState = GAME_STATE::GAME_RUN;
    }
  }
}

void Game::keyboardUpdate(){
  sf::Vector2f playerPosition = m_hero.getPosition();
  if(m_hero.canAttack()){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
      sf::Vector2f direction = {0, -1};
      std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(TextureManager::getTexture(m_projectileTextureID), 200, 5, direction, playerPosition);
      m_playerProjectiles.push_back(std::move(proj));
      m_hero.attack();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
      sf::Vector2f direction = {0, 1};
      std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(TextureManager::getTexture(m_projectileTextureID), 200, 5, direction, playerPosition);
      m_playerProjectiles.push_back(std::move(proj));
      m_hero.attack();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
      sf::Vector2f direction = {1, 0};
      std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(TextureManager::getTexture(m_projectileTextureID), 200, 5, direction, playerPosition);
      m_playerProjectiles.push_back(std::move(proj));
      m_hero.attack();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
      sf::Vector2f direction = {-1, 0};
      std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(TextureManager::getTexture(m_projectileTextureID), 200, 5, direction, playerPosition);
      m_playerProjectiles.push_back(std::move(proj));
      m_hero.attack();
    }
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
    m_healthPotion.use(m_hero);
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
    m_damagePotion.use(m_hero);
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
    m_defensePotion.use(m_hero);
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
    m_speedPotion.use(m_hero);
}

void Game::updateProjectiles(float delta){
  auto projectileIterator = m_playerProjectiles.begin();
  while(projectileIterator != m_playerProjectiles.end()){
    Projectile& proj = **projectileIterator;

    proj.update(delta);

    auto projTile = m_level.getTile(proj.getPosition());
    if(!m_level.isFloor(projTile) || !proj.isAlive())
      projectileIterator = m_playerProjectiles.erase(projectileIterator);
    else{
      bool projDestroy = false;
      auto enemyIterator = m_enemyList.begin();
      while(enemyIterator != m_enemyList.end()){
        Enemy& enemy = **enemyIterator;

        auto enemyTile = m_level.getTile(enemy.getPosition());
        if(projTile == enemyTile){
          enemy.takeDamage(m_hero.getDmg());
          projectileIterator = m_playerProjectiles.erase(projectileIterator);
          projDestroy = true;
          break;
        }else
          ++enemyIterator;
      }
      if(!projDestroy){
        ++projectileIterator;
      }
    }
  }
}

void Game::updateEnemy(float delta){
  auto enemyIterator = m_enemyList.begin();
  while(enemyIterator != m_enemyList.end()){
    Enemy& enemy = **enemyIterator;

    if(calculateDistance(m_hero.getPosition(), enemy.getPosition()) < 200.0f){
      enemy.calculateSteps(m_level, m_hero.getPosition());
    }

    enemy.update(delta);
    if(!enemy.isAlive()){
      enemyIterator = m_enemyList.erase(enemyIterator);
      m_liveEnemies--;
      m_enemiesDead++;
    }
    else{
      auto enemyTile = m_level.getTile(enemy.getPosition());
      auto heroTile = m_level.getTile(m_hero.getPosition());
      if(enemyTile == heroTile && m_hero.canDamage()){
        m_hero.takeDamage(enemy.getBaseDmg());
      }
      ++enemyIterator;
    }
  }
}

void Game::populateLevel(){
  auto numEnemies = rand() % (MIN_ENEMIES + (m_level.getRoomNumber() - 1) * 5) + (MAX_ENEMIES - MIN_ENEMIES + (m_level.getRoomNumber() - 1) * 5);
  m_liveEnemies = numEnemies;
  for(int i = 0; i < numEnemies; i++){
    std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
    auto spawnLocation = m_level.getRandomSpawnLocation();
    enemy->setPosition(spawnLocation.x, spawnLocation.y);

    m_enemyList.push_back(std::move(enemy));
  }
}

void Game::resetLevel(){
  m_enemyList.clear();
  m_playerProjectiles.clear();
  m_level.reset();
  m_level.generate();
  populateLevel();
  m_hero.reset();
  m_healthPotion.refill();
  m_damagePotion.refill();
  m_defensePotion.refill();
  m_speedPotion.refill();
  m_hero.setPosition(m_level.getActualTileLocation(1, 1).x, m_level.getActualTileLocation(1, 1).y);
}

double Game::calculateDistance(sf::Vector2f firstPos, sf::Vector2f secondPos){
  return sqrt((firstPos.x-secondPos.x)*(firstPos.x-secondPos.x)+(firstPos.y-secondPos.y)*(firstPos.y-secondPos.y));
}
