#ifndef SCENE_HPP
#define	SCENE_HPP

#include <map>
#include <string>
#include "GameObject.hpp"
using namespace std;

typedef map<string,GameObject*> GameObjectMap;

class Scene {
public:
    Scene();
    Scene(const Scene& orig);
    virtual ~Scene();
    
    virtual void update();
    void draw(RenderWindow &win);
    
    void addGameObject(GameObject* go);
    GameObject* getGameObject(string name);
private:
    GameObjectMap gameObjects;
    int goID;
    string name;
    
};

#endif	/* SCENE_HPP */

