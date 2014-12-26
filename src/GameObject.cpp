/* 
 * File:   GameObject.cpp
 * Author: jfons
 * 
 * Created on December 25, 2014, 12:13 PM
 */

#include "GameObject.hpp"
#include "ResourceManager.hpp"

GameObject::GameObject(): textureName("none"), name("none"), zIndex(0) {}

GameObject::~GameObject() {
    ResourceManager::deleteTexture(textureName);
}

void GameObject::update() {}

void GameObject::setTexture(string texture) {
    ResourceManager::deleteTexture(textureName);
    Sprite::setTexture(ResourceManager::getTexture(texture));
    textureName = texture;
}

string GameObject::getName() const { return name; }

int GameObject::getIndex() const { return zIndex; }

void GameObject::setIndex(int z) { zIndex = z; }