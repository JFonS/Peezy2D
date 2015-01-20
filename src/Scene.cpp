#include "include/Scene.hpp"
#include "include/Node.hpp"
#include "include/Debug.hpp"

Scene::Scene(string n) {
  Node::name = n;
}

void Scene::onUpdate(float dt) {}

void Scene::onDraw(RenderTarget& target, const Transform& transform){
}

void Scene::draw(RenderTarget& target) {
  Transform inverseCamera = camera.getInverse();
  childrenOrder.sort(zIndexSort);
  for (auto p : childrenOrder) p->draw(target, inverseCamera);
}
