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

const Transform & GameObject::getNodeTransform() { return Sprite::getTransform(); }

Rect<float> GameObject::getLocalBB()
{
    Rect<float> r;
    r.left   = getPosition().x;
    r.top    = getPosition().y;
    r.width  = Sprite::getTexture()->getSize().x;
    r.height = Sprite::getTexture()->getSize().y;
    return r;
}
