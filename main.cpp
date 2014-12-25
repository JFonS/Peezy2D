#include <SFML/Graphics.hpp>

#include "GameObject.hpp"
#include "ResourceManager.hpp"

using namespace std;
using namespace sf;

int main(int argc, char* argv[]) {
    
    
    GameObject go;

    go.setTexture(ResourceManager::getTexture("img.jpg"));
    
    Vector2i winSize(600,600);
    RenderWindow window(VideoMode(winSize.x, winSize.y), "");


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        
        window.clear();
        window.draw(go);

        window.display();
    }
    
    return 0;
}

