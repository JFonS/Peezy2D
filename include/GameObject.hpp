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
      
    virtual void update(Time dt);
    void setTexture(string texture);
    string getName() const;
    void setIndex(int z);
    int getIndex() const;
    
private:
    string textureName;
    string name;
    int zIndex;
};

#endif	/* GAMEOBJECT_HPP */

