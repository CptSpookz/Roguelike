#include <Enemy.hpp>
#include <iostream>
#include <cmath>

Enemy::Enemy(){
  auto enemy = rand() % static_cast<int>(ENEMY_CLASS::COUNT);
  auto enemyClass = static_cast<ENEMY_CLASS>(enemy);
  sf::String enemyName;
  switch(enemyClass){
    case ENEMY_CLASS::SKELETON:
      enemyName = "skeleton";
      m_charMaxHp = rand() % 201 + 200; // Skeleton max hp = 200 + 0~200
      m_charHp = m_charMaxHp;
      m_charBaseDmg = rand() % 26 + 25; // Skeleton base damage = 25 + 0~25
      m_charBaseDef = 20;
      m_charSpeed = 75;
      break;
    case ENEMY_CLASS::GOBLIN:
      enemyName = "goblin";
      m_charMaxHp = rand() % 251 + 300; // Goblin max hp = 300 + 0~250
      m_charHp = m_charMaxHp;
      m_charBaseDmg = 25;
      m_charBaseDef = rand() % 21 + 20; // Goblin base defense = 20 + 0~20
      m_charSpeed = 100;
      break;
  }
  m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::addTexture("../resources/sprites/enemies/" + enemyName + "/spr_" + enemyName +"_walk_up.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::addTexture("../resources/sprites/enemies/" + enemyName + "/spr_" + enemyName +"_walk_down.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::addTexture("../resources/sprites/enemies/" + enemyName + "/spr_" + enemyName +"_walk_right.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::addTexture("../resources/sprites/enemies/" + enemyName + "/spr_" + enemyName +"_walk_left.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::addTexture("../resources/sprites/enemies/" + enemyName + "/spr_" + enemyName +"_idle_up.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::addTexture("../resources/sprites/enemies/" + enemyName + "/spr_" + enemyName +"_idle_down.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::addTexture("../resources/sprites/enemies/" + enemyName + "/spr_" + enemyName +"_idle_right.png");
  m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::addTexture("../resources/sprites/enemies/" + enemyName + "/spr_" + enemyName +"_idle_left.png");

  setSprite(TextureManager::getTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), 8, 12);
  m_currentTexID = static_cast<int>(ANIMATION_STATE::WALK_UP);

  m_sprite.setPosition(950, 950);
  m_sprite.setOrigin(15, 15);

  m_position = m_sprite.getPosition();
}

void Enemy::update(float delta){
  if(!m_targetPositions.empty()){

      sf::Vector2f targetLocation = m_targetPositions.front();
      m_velocity = sf::Vector2f(targetLocation.x - m_position.x, targetLocation.y - m_position.y);

      if(abs(m_velocity.x) < 10.f && abs(m_velocity.y) < 10.f){
        m_targetPositions.erase(m_targetPositions.begin());
      }else{
        float length = sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
        m_velocity.x /= length;
        m_velocity.y /= length;

        m_position.x += m_velocity.x * (m_charSpeed * delta);
        m_position.y += m_velocity.y * (m_charSpeed * delta);

        m_sprite.setPosition(m_position);
      }
   }else{
     m_velocity = sf::Vector2f(0, 0);
   }
   Char::update(delta);
}

void Enemy::calculateSteps(Level& level, sf::Vector2f playerPosition){
  // Create all variables.
	std::vector<Tile*> openList;
	std::vector<Tile*> closedList;
	std::vector<Tile*> pathList;
	std::vector<Tile*>::iterator position;
	Tile* currentNode;

	// Reset all nodes.
	level.resetNodes();

	// Store the start and goal nodes.
	Tile* startNode = level.getTile(m_position);
	Tile* goalNode = level.getTile(playerPosition);

	// Check we have a valid path to find. If not we can just end the function as there's no path to find.
	if (startNode == goalNode)
	{
		// Clear the vector of target positions.
		m_targetPositions.clear();

		// Exit the function.
		return;
	}

	// Pre-compute our H cost (estimated cost to goal) for each node.
	for (int i = 0; i < level.getSize().x; i++)
	{
		for (int j = 0; j < level.getSize().y; j++)
		{
			int rowOffset, heightOffset;
			Tile* node = level.getTile(i, j);

			heightOffset = abs(node->rowIndex - goalNode->rowIndex);
			rowOffset = abs(node->columnIndex - goalNode->columnIndex);

			node->H = heightOffset + rowOffset;
		}
	}

	// Add the start node to the open list.
	openList.push_back(startNode);

	// While we have values to check in the open list.
	while (!openList.empty())
	{
		// Find the node in the open list with the lowest F value and mark it as current.
		int lowestF = INT_MAX;

		for (Tile* tile : openList)
		{
			if (tile->F < lowestF)
			{
				lowestF = tile->F;
				currentNode = tile;
			}
		}

		// Remove the current node from the open list and add it to the closed list.
		position = std::find(openList.begin(), openList.end(), currentNode);
		if (position != openList.end()){
			openList.erase(position);
    }

		closedList.push_back(currentNode);

		// Find all valid adjacent nodes.
		std::vector<Tile*> adjacentTiles;
		Tile* node;

		// Top.
		node = level.getTile(currentNode->columnIndex, currentNode->rowIndex - 1);
		if ((node != nullptr) && (level.isFloor(node)))
		{
			adjacentTiles.push_back(level.getTile(currentNode->columnIndex, currentNode->rowIndex - 1));
		}

		// Right.
		node = level.getTile(currentNode->columnIndex + 1, currentNode->rowIndex);
		if ((node != nullptr) && (level.isFloor(node)))
		{
			adjacentTiles.push_back(level.getTile(currentNode->columnIndex + 1, currentNode->rowIndex));
		}

		// Bottom.
		node = level.getTile(currentNode->columnIndex, currentNode->rowIndex + 1);
		if ((node != nullptr) && (level.isFloor(node)))
		{
			adjacentTiles.push_back(level.getTile(currentNode->columnIndex, currentNode->rowIndex + 1));
		}

		// Left.
		node = level.getTile(currentNode->columnIndex - 1, currentNode->rowIndex);
		if ((node != nullptr) && (level.isFloor(node)))
		{
			adjacentTiles.push_back(level.getTile(currentNode->columnIndex - 1, currentNode->rowIndex));
		}

		// For all adjacent nodes.
		for (Tile* node : adjacentTiles)
		{
			// If the node is our goal node.
			if (node == goalNode)
			{
				// Parent the goal node to current.
				node->parentNode = currentNode;

				// Store the current path.
				while (node->parentNode != nullptr)
				{
					pathList.push_back(node);
					node = node->parentNode;
				}

				// Empty the open list and break out of our for loop.
				openList.clear();
				break;
			}
			else
			{
				// If the node is not in the closed list.
				position = std::find(closedList.begin(), closedList.end(), node);
				if (position == closedList.end())
				{
					// If the node is not in the open list.
					position = std::find(openList.begin(), openList.end(), node);
					if (position == openList.end())
					{
						// Add the node to the open list.
						openList.push_back(node);

						// Set the parent of the node to the current node.
						node->parentNode = currentNode;

						// Calculate G (total movement cost so far) cost.
						node->G = currentNode->G + 10;

						// Calculate the F (total movement cost + heuristic) cost.
						node->F = node->G + node->H;
					}
					else
					{
						// Check if this path is quicker that the other.
						int tempG = currentNode->G + 10;

						// Check if tempG is faster than the other. I.e, whether it's faster to go A->C->B that A->C.
						if (tempG < node->G)
						{
							// Re-parent node to this one.
							node->parentNode = currentNode;
						}
					}
				}
			}
		}
	}

	// Clear the vector of target positions.
	m_targetPositions.clear();

	// Store the node locations as the enemies target locations.
	for (Tile* tile : pathList)
	{
		m_targetPositions.push_back(level.getActualTileLocation(tile->columnIndex, tile->rowIndex));
	}

	// Reverse the target position as we read them from goal to origin and we need them the other way around.
	std::reverse(m_targetPositions.begin(), m_targetPositions.end());
}

void Enemy::takeDamage(double damage){
  m_charHp -= damage;
}

bool Enemy::isAlive(){
  return (m_charHp > 0);
}
