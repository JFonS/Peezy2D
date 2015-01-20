#include "PeezyWin.hpp"
#include "Debug.hpp"
#include "GameObject.hpp"
#include "PText.hpp"

PeezyWin::PeezyWin(Vector2i size) {
    window = new RenderWindow(VideoMode(size.x, size.y), "");
    scenes = SceneMap();
    activeScene = NULL;
    startUp();
    _loop();
}

void PeezyWin::addScene(Scene* sc) {
  DbgLog("Added scene: " << sc->getName());
  scenes.insert(pair<string,Scene*>(sc->getName(), sc));
}

void PeezyWin::setActiveScene(string scName) {
  DbgLog("Setting active: " << scName);
  if (scenes.find(scName) != scenes.end()) {
    activeScene = scenes[scName];
  } else {
    DbgWarning("The scene doesn't exist");
  }
}

void PeezyWin::startUp() {
    //sample stuff (TO REMOVE)
    GameObject* go = new GameObject();
    go->setTexture("img.jpg");
    go->setIndex(200);
    go->setRotation(45.);
    go->setColor(Color::Red);
    go->move(100, 100);

    GameObject* go2 = new GameObject();
    go2->setTexture("img.jpg");
    go2->setRotation(45.);
    go2->move(-10, -10);
    go2->setIndex(50);

    PText* text = new PText("HOLA");
    text->setIndex(200);
    text->setOutline(true);
    text->setOutlineStroke(3);
    text->setOutlineColor(Color::Green);
    text->rotate(25.);
    
    Scene* scene = new Scene("game");
    scene->addChild(go);
    scene->addChild(text);
    go->addChild(go2);

    addScene(scene);
    setActiveScene("game");
};

void PeezyWin::loop(float dt){}

void PeezyWin::_loop() {
    Clock deltaClock;
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed)
                window->close();
            else if (activeScene != NULL) {
              PEvent e(event);
              activeScene->onEvent(e);
            }
        }
        window->clear();
        Time dTime = deltaClock.restart();
        float dt = dTime.asSeconds();
        loop(dt);
        if (activeScene != NULL) {
          activeScene->update(dt);
          activeScene->draw(*window);
        }

        window->display();
    }
}
