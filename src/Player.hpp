#ifndef __opengl_sample__Player__
#define __opengl_sample__Player__

#include "GameEntity.hpp"
#include "Island.hpp"
#include <vector>

class IslandsMap;
class Camera;
class GameScene;

class Player : public GameEntity, public IslandTouchDelegate
{
	typedef std::vector<Island*> VIslands;
	
    VIslands _islandsSelected;
	IslandsMap* _islandMap;
    Camera* _camera;
	GameScene* _Scene;
    
public:
	Player();
	void update();
    
	void setIslandMap(IslandsMap& islandMap);
    void setCamera(Camera& camera);
	void setGameScene(GameScene& _GameScene);

private:
	void onIslandTouched(Island& island);
	void onIslandTargeted(Island& island);
	void clearSelectedIslands();
    void addSelectedIsland(Island& island);
};


#endif /* defined(__opengl_sample__Player__) */
