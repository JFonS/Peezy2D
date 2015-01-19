#include "include/Scene.hpp"
#include "include/Node.hpp"
#include "include/Debug.hpp"

Scene::Scene(string n): name(n), goID(0) {
    drawingOrder = NodeList();
}

Scene::~Scene() {
    for (auto p : gameObjects) delete p.second;
}

void Scene::addNode(Node* go) {
    string name = go->getName();
    
    if (name == "none") {
        name = "go"; 
        name.append(to_string(goID));
        ++goID;
    }
    
    gameObjects.insert(pair<string,Node*>(name,go));
    DbgLog("Added " << name << " to " << this->name);  
    drawingOrder.push_front(go);
}

Node* Scene::getNode(string name) {
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

void Scene::draw(RenderTarget &win) {
    drawingOrder.sort(zIndexSort);
    for (auto p : drawingOrder) p->Node::draw(win, Transform::Identity);
}

bool Scene::zIndexSort(const Node* first, const Node* second) {
    return first->getIndex() <= second->getIndex();
}

string Scene::getName() { return name; }
