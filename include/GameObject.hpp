#ifndef GAMEOBJECT_HPP
#define	GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

class GameObject {
public:
    GameObject();
    GameObject(const GameObject& orig);
    virtual ~GameObject();

    Vector2i pos;
    Vector2i scale;
    float rot;
    
    Sprite sprite;
    
    void Draw();
    virtual void Update();
    
private:
    
};

#endif	/* GAMEOBJECT_HPP */

