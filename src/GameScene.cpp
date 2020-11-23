#include "GameScene.hpp"

#include <GLFW/glfw3.h>
#include "ServiceLocator.hpp"
#include "World.hpp"
#include "Input.hpp"
#include "IslandsMap.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "Plane.hpp"
#include "ResourcesPaths.hpp"
#include "WindowInfo.hpp"
#include "../proj.win/opengl_sample/opengl_sample/Ship.hpp"
#include "SceneManager.hpp"
#include "StartScene.hpp"
#include "../proj.win/opengl_sample/opengl_sample/GameController.hpp"


GameScene::GameScene()
    :_world(NULL), _camera(NULL), _background(NULL)
{
}

void GameScene::load()
{
    // saves all the entities to be updated and rendered
    _world = new World();

    // setup the ortho camera
    _camera = new Camera();
    float ar = ServiceLocator::get().getWindowInfo().getAspectRatio();
    _camera->setOrthoParams(ar * -100.f, ar * 100.f, -100.f, 100.f, -100.0f, 100.f);
    _camera->setLookAt(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.0f, 0.f));

    // procedural creation of islands
    IslandsMap* islandsMap = new IslandsMap();
    GameController* controller = new GameController();
    controller->setIslands(*islandsMap);
    islandsMap->setGameController(*controller);

    addEntity(islandsMap);

    _islandMap = islandsMap;
    // player logic
    Player* player = new Player();
    player->setIslandMap(*islandsMap);
    player->setCamera(*_camera);
    player->setGameScene(*this);
    addEntity(player);

    // background screen
    _background = new Plane();
    _background->setTextureByName(ResourcesPaths::kBackgroundImg);
    _background->setPosition(glm::vec3(0.f));
    _background->setScale(glm::vec3(200.f * ar, 200.f, 1.f));
}

GameScene::~GameScene()
{
    if (_camera)
    {
        delete _camera;
        _camera = NULL;
    }
    if (_world) {
        delete _world;
        _camera = NULL;
    }
}

void GameScene::update()
{
    Input& input = ServiceLocator::get().getInput();
    _world->update();

    input.update();
}

void GameScene::render()
{
    // set camera view projection matrix mode
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(&_camera->getViewProjection()[0][0]);

    // change to model view mode
    glMatrixMode(GL_MODELVIEW);

    glm::mat4 planeLocalToWorld = _background->getModel();
    glLoadMatrixf(&planeLocalToWorld[0][0]);
    _background->render();
    _world->render();
}

void GameScene::addEntity(GameEntity* entity)
{
    assert(entity);
    _world->addEntity(entity);
}

void GameScene::removeEntity(GameEntity* entity)
{
    assert(entity);
    _world->removeEntity(entity);
}
