#include <GLFW/glfw3.h>

#include "ServiceLocator.hpp"
#include "Input.hpp"
#include "WindowInfo.hpp"
#include "SceneManager.hpp"
#include "StartScene.hpp"
#include "Time.hpp"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input& input = ServiceLocator::get().getInput();
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if (action == GLFW_PRESS) 
    {
        input.setKeyPressed(key);
    }
}

static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{   
    Input& input = ServiceLocator::get().getInput();
    
    if(action == GLFW_PRESS) 
    {
        input.setMouseButtonPressed(button);
    }
}

void run()
{   
    // create a OpenGL window with GLFW library
    GLFWwindow* window;
    
    glfwSetErrorCallback(error_callback);
    
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
	int xres = 640;
	int yres = 480;
    window = glfwCreateWindow(xres, yres, "OpenGL Test", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, key_callback);
    
    glfwSetMouseButtonCallback(window, mouse_callback);
    
    // save window info to be used in the game
	ServiceLocator::get().getWindowInfo().init(window, xres, yres);
    
    // stores the input events catched from glfw callbacks, every frame all the key events are cleared
    Input& input = ServiceLocator::get().getInput();
    
	// load the first scene before starting the main loop
	SceneManager& sceneMng = ServiceLocator::get().getSceneManager();
	sceneMng.loadScene(new StartScene());
    
    // main loop
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
		Time::update();
		sceneMng.update();
		sceneMng.render();
        input.update(); // reset input events
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // destroy all game services
    ServiceLocator::get().destroy();
    
    glfwDestroyWindow(window);
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

int main(int argc, const char * argv[])
{
    run();
    
    return 0;
}
