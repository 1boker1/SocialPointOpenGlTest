#include "Tags.hpp"
#include "GameEntity.hpp"
#include <Island.hpp>

class Plane;
class Island;
class GameController;

class Ship : public GameEntity
{
	Plane* _plane;
	Island* _TargetIsland;
	Tag _ownerTag;

	float _Speed;
	glm::vec3 _Direction;

public:
	Ship();
	~Ship();

	void load();
	void update();
	void render();

	void setTarget(Island& _island);

private:
	void updateView();
	bool closeEnough();
	void conquer();
};

