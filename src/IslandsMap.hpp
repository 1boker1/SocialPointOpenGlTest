#ifndef __opengl_sample__IslandsMap__
#define __opengl_sample__IslandsMap__

#include "GameEntity.hpp"
#include "Tags.hpp"
#include <vector>
#include <glm/glm.hpp>

class Island;
class GameController;

class IslandsMap : public GameEntity
{	
public:
	typedef std::vector<Island*> Islands;
    
private:
	Islands _islands;
    
	GameController* _gameController;
    
public:
	void load();
    
	Island* getTouchedIsland(const glm::vec3& point);
	void setGameController(GameController& controller);
	void getIslandsByOwnerTag(Islands& out, Tag tag);
	
	int getNonPlayerIslands();

};

#endif /* defined(__opengl_sample__IslandsMap__) */
