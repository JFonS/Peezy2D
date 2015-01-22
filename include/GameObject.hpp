#ifndef GAMEOBJECT_HPP
#define	GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include <string>
#include <map>
#include <list>

using namespace sf;
using namespace std;

class GameObject : public Sprite, public Node {
public:
    GameObject();
    GameObject(string name);
    GameObject(const GameObject& orig);
    virtual ~GameObject();

    void setTexture(string texture);
    virtual void onUpdate(float dt) =0;

private:

    void onKeyDown(PEvent &e);
    void onMouseEnter(PEvent &e);
    void onMouseExit(PEvent &e);
    void onMouseOver();

    string textureName;
    virtual void onDraw(RenderTarget& target, const Transform& transform);
    const Transform & getNodeTransform();

    Rect<float> getBoundingBox();
};

#endif	/* GAMEOBJECT_HPP */
