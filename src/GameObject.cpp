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

void GameObject::update(float dt) {
//  rotate(20*dt);
}

void GameObject::setTexture(string texture) {
    ResourceManager::deleteTexture(textureName);
    Sprite::setTexture(ResourceManager::getTexture(texture));
    textureName = texture;
}

void GameObject::onDraw(RenderTarget& target, const Transform& transform) const {
  target.draw(*this, transform);
}
