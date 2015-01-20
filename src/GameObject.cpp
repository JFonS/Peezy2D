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
  sprite.setTexture(ResourceManager::getTexture(texture));
  textureName = texture;
}

void GameObject::onDraw(RenderTarget& target, const Transform& transform) const {
  target.draw(sprite, transform);
}
void GameObject::onUpdate(float dt){}
