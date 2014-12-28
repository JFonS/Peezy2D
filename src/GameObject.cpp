/* 
 * File:   GameObject.cpp
 * Author: jfons
 * 
 * Created on December 25, 2014, 12:13 PM
 */

#include "include/GameObject.hpp"
#include "include/ResourceManager.hpp"

GameObject::GameObject(): textureName("none"), name("none"), zIndex(0) {}

GameObject::~GameObject() {
    ResourceManager::deleteTexture(textureName);
}

void GameObject::update(Time dt) {
  rotate(20*dt.asSeconds());
}

void GameObject::setTexture(string texture) {
    ResourceManager::deleteTexture(textureName);
    Sprite::setTexture(ResourceManager::getTexture(texture));
    textureName = texture;
}

string GameObject::getName() const { return name; }

int GameObject::getIndex() const { return zIndex; }

void GameObject::setIndex(int z) { zIndex = z; }
