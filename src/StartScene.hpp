#ifndef __opengl_sample__EndScene__
#define __opengl_sample__EndScene__

#include "IScene.hpp"
#include <vector>
#include <string>

class Plane;
class GUIText;
class Camera;

class StartScene : public IScene
{   
    Camera* _camera;
	Plane* _plane;
    GUIText* _text;
    
    double _loadTime;
    float _waittingTime;
    
public:
    ~StartScene();
    StartScene();
	void load();
    
	void update();
	void render(); 

    bool isGameOver();

    void endGame();
};

#endif /* defined(__opengl_sample__EndScene__) */
