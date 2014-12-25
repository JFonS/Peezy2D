#include <SFML/Graphics.hpp>

#include "GameObject.hpp"
#include "ResourceManager.hpp"
#include "Scene.hpp"

using namespace std;
using namespace sf;

int main(int argc, char* argv[]) {
    
    
    GameObject* go = new GameObject();
    go->setTexture("img.jpg");
    
    Scene scene;
    scene.addGameObject(go);
    
    Vector2i winSize(600,600);
    RenderWindow window(VideoMode(winSize.x, winSize.y), "");


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        
        window.clear();
        scene.draw(window);
        //window.draw(*go);

        window.display();
    }
    
    return 0;
}

