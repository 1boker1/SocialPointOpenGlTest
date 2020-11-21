#include "Player.hpp"
#include "Tags.hpp"
#include "ServiceLocator.hpp"
#include "Input.hpp"
#include "IslandsMap.hpp"
#include "Camera.hpp"
#include <cassert>

Player::Player()
:GameEntity(Tag::PLAYER), _islandMap(NULL), _camera(NULL)
{
}

void Player::setIslandMap(IslandsMap& islandMap)
{
	_islandMap = &islandMap;
}

void Player::setCamera(Camera& camera)
{
	_camera = &camera;
}

void Player::update()
{
	Input& input = ServiceLocator::get().getInput();
    
	if (input.getMouseButtonBecomesPressed(0))
	{
		glm::vec3 cursorWorldPos = input.getCursorWorldPos(*_camera);
        
		assert(_islandMap);
		Island* island = _islandMap->getTouchedIsland(cursorWorldPos);
        
		if (island)
		{
			onIslandTouched(*island);
		}
		else
		{
			clearSelectedIslands();
		}
	}
}

void Player::addSelectedIsland(Island& island)
{
    VIslands::iterator it = std::find(_islandsSelected.begin(), _islandsSelected.end(), &island);
    
    if(_islandsSelected.end() == it)
    {
        _islandsSelected.push_back(&island);
    }
}

void Player::clearSelectedIslands()
{
	for (Island* island: _islandsSelected)
	{
		island->setIsSelected(false);
	}
    
	_islandsSelected.clear();
}

void Player::onIslandTouched(Island& island)
{
    if(0 == _islandsSelected.size())
    {
        if(Tag::NEUTRAL != island.getOwnerTag())
        {
            setTag(island.getOwnerTag());
            island.setIsSelected(true);
            addSelectedIsland(island);
        }
    }
    else if(island.getOwnerTag() == getTag())
    {
        island.setIsSelected(true);
        addSelectedIsland(island);
    }
}
