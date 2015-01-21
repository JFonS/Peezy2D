#ifndef PEEZYWIN_HPP
#define PEEZYWIN_HPP

#include "../include/Debug.hpp"
#include "../include/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <stack>

using namespace std;
using namespace sf;

typedef stack<Scene*> SceneStack;

class PeezyWin {
public:
  PeezyWin(Vector2i size);
  virtual ~PeezyWin();

  void pushScene(Scene* sc);
  void popScene();
  void changeScene(Scene* sc);
  Scene* peekScene();

private:
  void _loop();
   
  virtual void startUp();
  virtual void loop(float dt);
  
  RenderWindow* window;
  SceneStack scenes;
};

#endif
