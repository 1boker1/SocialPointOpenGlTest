#include "Ship.hpp"

#include "Plane.hpp"
#include "Time.hpp"
#include "MathUtils.hpp"
#include "ResourcesPaths.hpp"
#include <ServiceLocator.hpp>
#include "IScene.hpp"

Ship::Ship()
	:GameEntity(Tag::PLAYER), _ownerTag(Tag::PLAYER), _plane(NULL), _Speed(15)
{
	ServiceLocator::get().getCurrentScene().addEntity(this);

	setScale(glm::vec3(5.0f, 5.0f, 1.0f));
}

Ship::~Ship()
{
	if (_plane)
	{
		delete _plane;
	}
}

void Ship::setTarget(Island& _Island)
{
	_TargetIsland = &_Island;
	_Direction = glm::normalize(_TargetIsland->getPosition() - getPosition());
}

void Ship::update()
{
	setPosition(getPosition() + (_Direction * _Speed * Time::getDeltatime()));

	if (closeEnough())
		conquer();
}

bool Ship::closeEnough()
{
	if (glm::length(_TargetIsland->getPosition() - getPosition()) < _TargetIsland->getRadius())
	{
		return true;
	}

	return false;
}

void Ship::conquer()
{
	if (_TargetIsland->getOwnerTag() != _ownerTag)
	{
		if (_TargetIsland->getAmountOfShips() > 0)
		{
			_TargetIsland->setAmountOfShips(_TargetIsland->getAmountOfShips() - 1);
		}
		else
		{
			_TargetIsland->conquered(_ownerTag);
		}
	}
	else
	{
		_TargetIsland->setAmountOfShips(_TargetIsland->getAmountOfShips() + 1);
	}

	ServiceLocator::get().getCurrentScene().removeEntity(this);
}

void Ship::load()
{
	_plane = new Plane();
	_plane->load();

	updateView();
}

void Ship::render()
{
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 planeLocalToWorld = getModel() * _plane->getModel();
	glLoadMatrixf(&planeLocalToWorld[0][0]);
	_plane->render();
}

void Ship::updateView()
{
	std::string textureName = ResourcesPaths::kShipImg;

	if (_plane)
	{
		_plane->setTextureByName(textureName);
	}
}