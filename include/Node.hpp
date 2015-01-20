#ifndef NODE_HPP
#define	NODE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <list>
using namespace sf;
using namespace std;

class Node;

typedef map<string,Node*> NodeMap;
typedef list<Node*> NodeList;

class Node {
public:
  Node();
  Node(string texture);
  Node(const Node& orig);
 // ~Node();
      
  string getName() const;
  void setIndex(int z);
  int getIndex() const;
    
  void addChild(Node* go);
  Node* getChild(string name);
  void removeChild(string name);
  void removeChild(Node* go);
  void draw(RenderTarget& target, const Transform& parentTransform);
  void update(float dt);
  
  virtual void onUpdate(float dt) = 0;

protected:    
  virtual void onDraw(RenderTarget& target, const Transform& transform) = 0;
  Transform myTransform;

  string name;
  int zIndex;
   
  int childID;
  NodeMap children;
  NodeList childrenOrder;

  static bool zIndexSort(const Node* first, const Node* second);
};

#endif	/* NODE_HPP */

