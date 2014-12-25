
/* 
 * File:   Scene.cpp
 * Author: jfons
 * 
 * Created on December 25, 2014, 7:44 PM
 */

#include "Scene.hpp"
#include "GameObject.hpp"

Scene::Scene(): name("none"), goID(0) {
}

Scene::~Scene() {
    for (auto p : gameObjects) delete p.second;
}

void Scene::addGameObject(GameObject* go) {
    gameObjects.insert(pair<string,GameObject*>(go->getName(),go));
}

void Scene::update() {}

void Scene::draw(RenderWindow &win) {
    for (auto p : gameObjects) win.draw(*p.second);
}
