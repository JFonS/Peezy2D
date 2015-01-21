#include "../include/GameObject.hpp"
#include "../include/ResourceManager.hpp"
#include "Debug.hpp"
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
  ResourceManager::deleteSoundBuffer("assets/fart.wav");
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

void GameObject::onKeyDown(PEvent &e) {
  if (e.key.code == Keyboard::P) {
    Sound* s = new Sound();
    s->setBuffer(ResourceManager::getSoundBuffer("assets/fart.wav"));
    s->setPitch((float)(rand()%300)/100.);
    s->play();
  }
  rotate(10.);
  e.propagate = false;
}

void GameObject::onMouseEnter(PEvent &e)
{
    DbgLog("Enter " << name);
}

void GameObject::onMouseExit(PEvent &e)
{
    DbgLog("Exit " << name);
}

void GameObject::onMouseOver()
{
    //DbgLog("Over");
    //DbgLog(rand()%100);
}
