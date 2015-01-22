#include "../include/GameObject.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Debug.hpp"
#include <stdlib.h>

GameObject::GameObject(): textureName("none") {
  name = "none";
  zIndex = 0;
}

GameObject::GameObject(string n): textureName("none") {
  name = n;
  zIndex = 0;
}

GameObject::~GameObject()
{
  DbgWarning("destroyed");
  ResourceManager::deleteTexture(textureName);
}

void GameObject::setTexture(string texture) {
  ResourceManager::deleteTexture(textureName);
  Sprite::setTexture(ResourceManager::getTexture(texture));
  textureName = texture;
}

void GameObject::onDraw(RenderTarget& target, const Transform& transform) {
  target.draw(*this, transform);
}

void GameObject::onUpdate(float dt){}

const Transform & GameObject::getNodeTransform() { return Sprite::getTransform();}

Rect<float> GameObject::getBoundingBox()
{
    return getLocalBounds();
}

void GameObject::onKeyDown(PEvent &e) {}

void GameObject::onMouseEnter(PEvent &e){}

void GameObject::onMouseExit(PEvent &e){}

void GameObject::onMouseOver(){}
