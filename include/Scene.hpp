#ifndef SCENE_HPP
#define	SCENE_HPP

#include <map>
#include <string>
#include <list>
#include "Node.hpp"

using namespace std;

typedef map<string,Node*> NodeMap;
typedef list<Node*> NodeList;

class Scene: public Node {
public:
  Scene(string name);
  virtual ~Scene();
    
  virtual void onUpdate(float dt); 
  void draw(RenderTarget& target); 
  Transform camera;   
  
  Vector2i sceneToWin(Vector2i pos);
  Vector2i winToScene(Vector2i pos);
private:
  virtual void onDraw(RenderTarget& target, const Transform& transform);
  
};

#endif	/* SCENE_HPP */

