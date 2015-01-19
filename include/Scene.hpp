#ifndef SCENE_HPP
#define	SCENE_HPP

#include <map>
#include <string>
#include <list>
#include "Node.hpp"

using namespace std;

typedef map<string,Node*> NodeMap;
typedef list<Node*> NodeList;

class Scene {
public:

    Scene(string name);
    virtual ~Scene();
    
    virtual void update(float dt); 
    void _update(float dt);
    void draw(RenderTarget &win);
    
    void addNode(Node* go);
    Node* getNode(string name);
   
    string getName();

private:
    NodeMap gameObjects;
    NodeList drawingOrder;

    string name;
    int goID;
    static bool zIndexSort(const Node* first, const Node* second);
};

#endif	/* SCENE_HPP */

