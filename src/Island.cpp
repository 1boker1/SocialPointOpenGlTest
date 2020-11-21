#include "Island.hpp"

#include "ServiceLocator.hpp"
#include "Input.hpp"
#include "IScene.hpp"
#include "Plane.hpp"
#include "GUIText.hpp"
#include "Time.hpp"
#include "MathUtils.hpp"
#include "ResourcesPaths.hpp"

Island::Island()
:GameEntity(Tag::ISLAND), _ownerTag(Tag::NEUTRAL), _gameController(NULL), _plane(NULL), _guiText(NULL)
, _lastTimeUnitsIncremented(0.f), _unitsIncrementStep(0.5f), _units(0), _isSelected(false)
{
}

Island::~Island()
{
    if(_plane)
    {
        delete _plane;
    }
    
    if(_guiText)
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
	_maxUnits = (int) getScale().x;
    
	updateView();
}

void Island::update()
{
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
    
    if(_plane)
    {
        _plane->setTextureByName(textureName);
    }
    
    updateText();
}

void Island::updateText()
{
	_guiText->setText(std::to_string(_units));
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
