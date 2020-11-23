#include "Island.hpp"

#include "ServiceLocator.hpp"
#include "Input.hpp"
#include "IScene.hpp"
#include "Plane.hpp"
#include "GUIText.hpp"
#include "Time.hpp"
#include "MathUtils.hpp"
#include "ResourcesPaths.hpp"
#include "../proj.win/opengl_sample/opengl_sample/Ship.hpp"
#include "../proj.win/opengl_sample/opengl_sample/GameController.hpp"
#include <random>

Island::Island()
	:GameEntity(Tag::ISLAND), _ownerTag(Tag::NEUTRAL), _gameController(NULL), _plane(NULL), _guiText(NULL)
	, _unitsIncrementStep(0.5f), _units(0), _isSelected(false), _IncrementTimer(0.f)
{
}

Island::~Island()
{
	if (_plane)
	{
		delete _plane;
	}

	if (_guiText)
	{
		delete _guiText;
	}
}

void Island::load()
{
	_plane = new Plane();
	_plane->load();

	_guiText = new GUIText();
	_guiText->init(10, 10, ResourcesPaths::kTextAtlas);
	_guiText->setPosition(glm::vec3(-0.48f, -0.6f, 0.f));
	_guiText->setScale(glm::vec3(1.f));
	_maxUnits = (int)getScale().x;

	updateView();
}

void Island::update()
{
	if (_ownerTag != Tag::NEUTRAL)
	{
		produceShips();
	}
}

bool Island::isPointInside(const glm::vec3& point)
{
	glm::vec3 cursorDir = point - getPosition();

	float distToPoint = glm::length(cursorDir);

	// check whether the point is inside the cicle inside the island's square (side x and y are the same value)
	if (distToPoint <= getScale().x)
	{
		return true;
	}

	return false;
}

void Island::setOwnerByTag(Tag newOwer)
{
	_ownerTag = newOwer;

	updateView();
}

Tag Island::getOwnerTag()
{
	return _ownerTag;
}

int Island::getAmountOfShips()
{
	return _units;
}

float Island::getRadius()
{
	return getScale().x * 0.5f;
}

void Island::conquered(Tag owner)
{
	setOwnerByTag(owner);

	if (_gameController->shouldGameEnd())
	{
		_gameController->endGame();
	}
}

void Island::setAmountOfShips(int amount)
{
	_units = amount;

	if (_units > _maxUnits)
		_units = _maxUnits;

	updateText();
}

void Island::updateView()
{
	std::string textureName = ResourcesPaths::kNeutralIslandImg;

	if (_ownerTag == Tag::IA)
	{
		if (_isSelected)
		{
			textureName = ResourcesPaths::kEnemyIslandSelectedImg;
		}
		else {
			textureName = ResourcesPaths::kEnemyIslandImg;
		}
	}
	if (_ownerTag == Tag::PLAYER)
	{
		if (_isSelected)
		{
			textureName = ResourcesPaths::kPlayerIslandSelectedImg;
		}
		else {
			textureName = ResourcesPaths::kPlayerIslandImg;
		}
	}

	if (_plane)
	{
		_plane->setTextureByName(textureName);
	}

	updateText();
}

void Island::updateText()
{
	_guiText->setText(std::to_string(_units));
}

void Island::sendShips(Island& island)
{
	for (int x = 0; x < getAmountOfShips(); x++)
	{
		Ship* newShip = new Ship();

		float xPosition = MathUtils::rand(-1.f, 1.f);
		float yPosition = MathUtils::rand(-1.f, 1.f);

		glm::vec3 position = getPosition() + glm::normalize(glm::vec3(xPosition, yPosition, 0)) * getRadius();

		newShip->setPosition(position);
		newShip->setTarget(island);
	}

	setAmountOfShips(0);
}

void Island::render()
{
	// be sure the matrix model is set to modelview to not override GL_PROJECTION (camera settings)
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 planeLocalToWorld = getModel() * _plane->getModel();
	glLoadMatrixf(&planeLocalToWorld[0][0]);
	_plane->render();

	glm::mat4 textLocalToWorld = getModel() * _guiText->getModel();
	glLoadMatrixf(&textLocalToWorld[0][0]);
	_guiText->render();
}

void Island::setIsSelected(bool isSelected)
{
	_isSelected = isSelected;

	updateView();
}

void Island::setGameController(GameController& gameController)
{
	_gameController = &gameController;
}

void Island::produceShips()
{
	_IncrementTimer += Time::getDeltatime();

	if (_IncrementTimer >= _unitsIncrementStep && _units < _maxUnits)
	{
		_units++;
		_IncrementTimer = 0.0f;

		updateText();
	}
}
