#ifndef PEEZYWIN_HPP
#define PEEZYWIN_HPP

#include "../include/Debug.hpp"
#include "../include/Scene.hpp"
#include "../include/MovieClip.hpp"
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
  void play();

  static void pushScene(Scene* sc);
  static void popScene();
  static void changeScene(Scene* sc);
  static Scene* peekScene();

protected:
  void _loop();
   
  virtual void startUp();
  virtual void loop(float dt);
  
  RenderWindow* window;
  static SceneStack scenes;
};

#endif
