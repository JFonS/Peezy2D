#include "include/GameObject.hpp"
#include "include/ResourceManager.hpp"
#include "Debug.hpp"

GameObject::GameObject(): textureName("none") {
  name = "none";
  zIndex = 0;
}

GameObject::~GameObject() {
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
