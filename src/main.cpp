#include <SFML/Graphics.hpp>

#include "include/Debug.hpp"
#include "include/GameObject.hpp"
#include "include/ResourceManager.hpp"
#include "include/Scene.hpp"
#include "include/PText.hpp"

using namespace std;
using namespace sf;

int main(int argc, char* argv[]) {
    
    GameObject* go = new GameObject();
    go->setTexture("img.jpg");
    go->setIndex(20);
    go->setColor(Color::Red);

    PText *t = new PText("Hola");
    t->setPosition(100.0f, 100.0f);
    t->setOutlineStroke(4);
    t->setOutlineColor(Color::Red);
    t->setColor(Color::White);
    t->flicker(100, 100);
    t->blow(5.0f, 5000);

    GameObject* go2 = new GameObject();
    go2->setTexture("img.jpg");
    go2->setRotation(45.);
    go2->move(100, 100);
    go2->setIndex(50);
    
    Scene scene;
    scene.addGameObject(go);
    scene.addGameObject(go2);
    
    Vector2i winSize(600, 600);
    RenderWindow window(VideoMode(winSize.x, winSize.y), "");

    //scene.getGameObject("go1")->setIndex(-10);
    Clock deltaClock;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        Time dt = deltaClock.restart();
        scene._update(dt);
        scene.draw(window);
        t->update();
        t->draw(window);

        window.display();
    }
    return 0;
}

