#include "../include/GameObject.hpp"
#include "../include/ResourceManager.hpp"
#include "Debug.hpp"
#include <stdlib.h>

GameObject::GameObject(): textureName("none") {
  name = "none";
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

void GameObject::onMouseMove(PEvent &e)
{
    bool wasOver = isOver;
    isOver = isMouseOver(Vector2f(e.mouseMove.x, e.mouseMove.y));
    if(not wasOver and isOver) onMouseEnter(e);
    else if(wasOver and not isOver) onMouseExit(e);
    if(isOver) onMouseOver(e);
}


void GameObject::onMouseEnter(PEvent &e){}
void GameObject::onMouseExit(PEvent &e){}
void GameObject::onMouseOver(PEvent &e){}

bool GameObject::isMouseOver(const Vector2f pos)
{
    return	(Position.x < GetPosition().x + GetSize().x) && (GetPosition().x < Position.x) &&
            (Position.y < GetPosition().y + GetSize().y) && (GetPosition().y < Position.y);
}
