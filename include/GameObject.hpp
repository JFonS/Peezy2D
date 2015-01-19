#ifndef GAMEOBJECT_HPP
#define	GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include <string>
#include <map>
#include <list>
using namespace sf;
using namespace std;


class GameObject : public Node, public Sprite {
public:
    GameObject();
    GameObject(string texture);
    GameObject(const GameObject& orig);
    ~GameObject();
      
    virtual void update(float dt);
    void setTexture(string texture);

private:
    string textureName;
    virtual void onDraw(RenderTarget& target, const Transform& transform) const;
};

#endif	/* GAMEOBJECT_HPP */

