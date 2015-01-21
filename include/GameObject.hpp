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
    GameObject(string texture);
    GameObject(const GameObject& orig);
    virtual ~GameObject();

    void setTexture(string texture);
    virtual void onUpdate(float dt);

    //Sprite sprite;

protected:
    bool mouseIsOver;

    virtual void onMouseEnter(PEvent &e){}
    virtual void onMouseExit(PEvent &e){}
    virtual void onMouseOver(PEvent &e){}
private:

    void onKeyDown(PEvent &e);

    string textureName;
    virtual void onDraw(RenderTarget& target, const Transform& transform);
    const Transform & getNodeTransform();

    bool isMouseOver(const Vector2f pos);
};

#endif	/* GAMEOBJECT_HPP */
