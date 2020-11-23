#include "GameController.hpp"
#include "IslandsMap.hpp"
#include <ServiceLocator.hpp>
#include <StartScene.hpp>
#include <SceneManager.hpp>

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::setIslands(IslandsMap& islands)
{
	_islands = &islands;
}

bool GameController::shouldGameEnd()
{
	return _islands->getNonPlayerIslands() <= 0;
}

void GameController::endGame()
{
	ServiceLocator::get().getSceneManager().loadScene(new StartScene());
}
