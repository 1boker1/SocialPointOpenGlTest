#ifndef __opengl_sample__Island__
#define __opengl_sample__Island__

#include "Tags.hpp"
#include "GameEntity.hpp"

class Plane;
class Island;
class GUIText;
class GameController;

enum class IslandState
{
	NEUTRAL = 0,
	PLAYER,
	SELECTED_BY_PLAYER,
	IA,
    SELECTED_BY_IA
};

class IslandTouchDelegate
{
public:
	virtual void onIslandTouched(Island& island) = 0;
};

class Island : public GameEntity
{
	Plane* _plane;
    Tag _ownerTag;
	GUIText* _guiText;
	GameController* _gameController;
    
	bool _isSelected;
	int _maxUnits;
	int _units;
	float _unitsIncrementStep;
	float _IncrementTimer;
    
public:
    Island();
    ~Island();
    
    void load();
    void update();
    void render();
    
	bool isPointInside(const glm::vec3& point);
    
	void setOwnerByTag(Tag owner);
	Tag getOwnerTag();
	
	void setIsSelected(bool isSelected);
    
	void setGameController(GameController& gameController);

	void produceShips();
	void sendShips(Island& island);

	int getAmountOfShips();
	void setAmountOfShips(int amount);

	float getRadius();

	void conquered(Tag owner);

private:
	void updateView();
	void updateText();
};

#endif /* defined(__opengl_sample__Island__) */
