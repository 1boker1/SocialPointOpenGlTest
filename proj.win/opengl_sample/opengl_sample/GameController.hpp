#include <IslandsMap.hpp>

class GameController 
{
	IslandsMap* _islands;

public:
	GameController();
	~GameController();

	void setIslands(IslandsMap& islands);
	bool shouldGameEnd();

	void endGame();
private:

};

