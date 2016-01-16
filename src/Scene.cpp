#include "../include/Scene.hpp"
#include "../include/Node.hpp"
#include "../include/Debug.hpp"

Scene::Scene(string n)
{
  Node::name = n;
}

Scene::~Scene()
{
    DbgWarning("destroyed");
}

void Scene::onUpdate(float dt) {}

void Scene::onDraw(RenderTarget& target, const Transform& transform)
{
}

const Transform& Scene::getNodeTransform()
{
    return camera;
}

Rect<float> Scene::getLocalBB()
{
    return Rect<float>(.0f, .0f, .0f, .0f);
}

void Scene::draw(RenderTarget& target)
{
  Transform inverseCamera = camera.getInverse();
  childrenOrder.sort(zIndexSort);
  for (auto p : childrenOrder) p->draw(target, inverseCamera);
}


