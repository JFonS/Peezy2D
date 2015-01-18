#ifndef PEEZYWIN_HPP
#define PEEZYWIN_HPP

#include "Debug.hpp"
#include "Scene.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace std;
using namespace sf;

typedef map<string,Scene*> SceneMap;

class PeezyWin {
public:
  PeezyWin(Vector2i size);

  void addScene(Scene* sc);
  void setActiveScene(string scName);
private:
  void _loop();
   
  virtual void startUp();
  virtual void loop(float dt);
  
  RenderWindow* window;
  SceneMap scenes;
  Scene* activeScene;
};

#endif
