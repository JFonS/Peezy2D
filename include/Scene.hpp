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
    Scene();
    Scene(const Scene& orig);
    virtual ~Scene();
    
    virtual void update(Time dt);
    void draw(RenderWindow &win);
    
    void addGameObject(GameObject* go);
    GameObject* getGameObject(string name);
    
private:
    GameObjectMap gameObjects;
    GameObjectList drawingOrder;
    

    void _update();

    int goID;
    string name;
    static bool zIndexSort(const GameObject* first, const GameObject* second);
};

#endif	/* SCENE_HPP */

