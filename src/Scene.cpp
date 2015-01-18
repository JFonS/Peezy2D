#include "include/Scene.hpp"
#include "include/GameObject.hpp"
#include "include/Debug.hpp"

Scene::Scene(string n): name(n), goID(0) {
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
    DbgLog("Added " << name << " to " << this->name);  
    drawingOrder.push_front(go);
}

GameObject* Scene::getGameObject(string name) {
  if (gameObjects.find(name) != gameObjects.end()) {
    return gameObjects[name];
  } else {
    DbgWarning("The object doesn't exist");
  }
  return NULL;
}

void Scene::update(float dt) {}

void Scene::_update(float dt) {
  for (auto p : drawingOrder) p->update(dt);
  update(dt);
}

void Scene::draw(RenderWindow *win) {
    drawingOrder.sort(zIndexSort);
    for (auto p : drawingOrder) win->draw(*p);
}

bool Scene::zIndexSort(const GameObject* first, const GameObject* second) {
    return first->getIndex() <= second->getIndex();
}

string Scene::getName() { return name; }
