#ifndef SCENE_HPP
#define	SCENE_HPP

#include <map>
#include <string>
#include <list>
#include "GameObject.hpp"

using namespace std;

typedef map<string,GameObject*> GameObjectMap;
typedef list<GameObject*> GameObjectList;

class Scene {
public:

    Scene(string name);
    virtual ~Scene();
    
    virtual void update(float dt); 
    void _update(float dt);
    void draw(RenderWindow *win);
    
    void addGameObject(GameObject* go);
    GameObject* getGameObject(string name);
   
    string getName();

private:
    GameObjectMap gameObjects;
    GameObjectList drawingOrder;

    string name;
    int goID;
    static bool zIndexSort(const GameObject* first, const GameObject* second);
};

#endif	/* SCENE_HPP */

