#include "IslandsMap.hpp"

#include <glm/glm.hpp>
#include "MathUtils.hpp"
#include "Island.hpp"

#include "ServiceLocator.hpp"
#include "World.hpp"
#include "Tags.hpp"
#include "IScene.hpp"

#include <cstdio>

void IslandsMap::load()
{
	IScene& scene = ServiceLocator::get().getCurrentScene();
    
	glm::vec2 grid(7, 7);
    
	glm::vec2 grid_size = glm::vec2(180, 180);
	glm::vec2 halfgrid_size = grid_size / 2.0f;
    
	glm::vec2 block_size = grid_size / grid;
	glm::vec2 block_halfSize = block_size / 1.5f;
	
	glm::vec2 minPos = -halfgrid_size + block_halfSize;
    
	Island* island = NULL;
	Island* islandIA = NULL;
    
	int counter = 0;
	for (int i = 0; i < grid.x; i++)
	{
		for (int j = 0; j < grid.y; j++)
		{
			bool skip = MathUtils::rand(0.f, 1.f) < 0.65f;
			if (skip)
			{
				continue;
			}
            
			island = new Island();
            
			if (0 == counter)
			{
				islandIA = island;
			}
			counter++;
            
			glm::vec2 pos(block_size.x*i, block_size.y*j);
            
			glm::vec2 finalPos = minPos + pos;
            
			glm::vec3 scale(MathUtils::rand(block_size.x / 3.f, block_size.x));
            
			island->setPosition(glm::vec3(finalPos.x, finalPos.y, 0.f));
			island->setScale(scale);
			island->setGameController(*_gameController);
            
			_islands.push_back(island);
            
			scene.addEntity(island);
		}
	}
    
	island->setOwnerByTag(Tag::PLAYER);
	islandIA->setOwnerByTag(Tag::IA);
}

Island* IslandsMap::getTouchedIsland(const glm::vec3& point)
{
	for (Island* island: _islands)
	{
		bool touched = island->isPointInside(point);
        
		if (touched)
		{
			return island;
		}
	}
    
	return NULL;
}

void IslandsMap::setGameController(GameController& controller)
{
	_gameController = &controller;
}

void IslandsMap::getIslandsByOwnerTag(Islands& out, Tag tag)
{
	for (Island* island : _islands)
	{
		if (tag == island->getOwnerTag())
		{
			out.push_back(island);
		}
	}
}

int IslandsMap::getNonPlayerIslands()
{
	int amount=0;
	for (Island* island : _islands)
	{
		if (island->getOwnerTag() != Tag::PLAYER)
		{
			amount++;
		}
	}
	return amount;
}
