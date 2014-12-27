
/* 
 * File:   Scene.cpp
 * Author: jfons
 * 
 * Created on December 25, 2014, 7:44 PM
 */

#include "Scene.hpp"
#include "GameObject.hpp"
#include "Debug.hpp"

Scene::Scene(): name("none"), goID(0) {
    drawingOrder = GameObjectList();
}

Scene::~Scene() {
    for (auto p : gameObjects) delete p.second;
}


void Scene::addGameObject(GameObject* go) {
    string name = go->getName();
    
    if (name == "none") {
        name = "go"; 
        name.append(to_string(goID));
        ++goID;
    }
    
    gameObjects.insert(pair<string,GameObject*>(name,go));
    
    drawingOrder.push_front(go);
}

GameObject* Scene::getGameObject(string name) {
    return NULL;
}
void Scene::update(Time dt) {   
}

void Scene::_update(Time dt) {
    for (auto p : drawingOrder) p->update(dt);
    update(dt);
}

void Scene::draw(RenderWindow &win) {
    drawingOrder.sort(zIndexSort);
    for (auto p : drawingOrder) win.draw(*p);
}

bool Scene::zIndexSort(const GameObject* first, const GameObject* second) {
    return first->getIndex() <= second->getIndex();
}
