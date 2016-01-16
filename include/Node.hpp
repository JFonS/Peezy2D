#ifndef NODE_HPP
#define	NODE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <list>
#include "../include/PEvent.hpp"
#include "../include/Debug.hpp"

using namespace sf;
using namespace std;

class Node;

typedef map<string,Node*> NodeMap;
typedef list<Node*> NodeList;

class Node
{

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

  Rect<float> getGlobalBB();
  virtual Rect<float> getLocalBB() = 0;

  float getLocalWidth()  { return getLocalBB().width;  }
  float getLocalHeight() { return getLocalBB().height; }
  float getWidth()  { return getGlobalBB().width;  }
  float getHeight() { return getGlobalBB().height; }
  float getLeft()   { return getGlobalBB().left;   }
  float getTop()    { return getGlobalBB().top;    }
  bool  collidesWith(Node *go) { return getGlobalBB().intersects(go->getGlobalBB()); }

protected: 

  NodeMap children;
  NodeList childrenOrder;

  string name;
  int zIndex, childID;
  bool mouseIsOver;

  virtual void onDraw(RenderTarget& target, const Transform& transform) = 0;

  virtual void onUpdate(float dt) {}
  virtual void onKeyDown(PEvent &e){}
  virtual void onKeyUp(PEvent &e){}

  virtual void onMouseEnter(PEvent &e){}
  virtual void onMouseExit(PEvent &e){}
  virtual void onMouseOver(PEvent &e){}
  virtual void onMouseMove(PEvent &e){}
  virtual void onMouseDown(PEvent &e){}
  virtual void onMouseUp(PEvent &e){}

  static bool zIndexSort(const Node* first, const Node* second);

  virtual const Transform& getNodeTransform() = 0;
  Vector2f globalToLocal(Vector2f pos);
  Vector2f localToGlobal(Vector2f pos);

private:

  bool isMouseOver(const Vector2f mousePos);
};

#endif	/* NODE_HPP */

