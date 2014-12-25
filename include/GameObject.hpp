#ifndef GAMEOBJECT_HPP
#define	GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class GameObject : public Sprite {
public:
    GameObject();
    GameObject(string texture);
    GameObject(const GameObject& orig);
    ~GameObject();
      
    virtual void update();
    void setTexture(string texture);
    string getName();
    
private:
    string textureName;
    string name;
};

#endif	/* GAMEOBJECT_HPP */

