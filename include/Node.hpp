#ifndef NODE_HPP
#define	NODE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <list>
#include "PEvent.hpp"

using namespace sf;
using namespace std;

class Node;

typedef map<string,Node*> NodeMap;
typedef list<Node*> NodeList;

class Node {
public:
  Node();
  Node(string name);
  Node(const Node& orig);
  virtual ~Node();
      
  string getName() const;
  void setIndex(int z);
  int getIndex() const;
    
  void addChild(Node* go);
  Node* getChild(string name);
  void removeChild(string name);
  void removeChild(Node* go);
  void draw(RenderTarget& target, const Transform& parentTransform);
  void update(float dt);
  
  void onEvent(PEvent &e);

protected: 

  NodeMap children;
  NodeList childrenOrder;

  string name;
  int zIndex, childID;
  bool mouseIsOver;

  virtual void onDraw(RenderTarget& target, const Transform& transform) = 0;
  virtual const Transform & getNodeTransform();

  virtual void onUpdate(float dt) = 0;
  virtual void onKeyDown(PEvent &e){}
  virtual void onKeyUp(PEvent &e){}

  virtual void onMouseEnter(PEvent &e){}
  virtual void onMouseExit(PEvent &e){}
  virtual void onMouseOver(){}
  virtual void onMouseMove(PEvent &e){}
  virtual void onMouseDown(PEvent &e){}
  virtual void onMouseUp(PEvent &e){}

  virtual Rect<float> getBoundingBox();

  static bool zIndexSort(const Node* first, const Node* second);

private:

  bool isMouseOver(const Vector2f mousePos);
};

#endif	/* NODE_HPP */

