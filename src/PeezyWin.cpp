#include "PeezyWin.hpp"
#include "Debug.hpp"
#include "GameObject.hpp"

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
    GameObject* go = new GameObject();
    go->setTexture("img.jpg");
    go->setIndex(20);
    go->setColor(Color::Red);

    GameObject* go2 = new GameObject();
    go2->setTexture("img.jpg");
    go2->setRotation(45.);
    go2->move(100, 100);
    go2->setIndex(50);
    
    Scene* scene = new Scene("game");
    scene->addNode(go);
    go->addChild(go2);

    addScene(scene);
    setActiveScene("game");
};

void PeezyWin::loop(float dt){
  GameObject* p;
  p = static_cast<GameObject*>(activeScene->getNode("go0"));
  p->move(dt*20,dt*20);
}

void PeezyWin::_loop() {
    Clock deltaClock;
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed)
                window->close();
        }
        window->clear();
        Time dTime = deltaClock.restart();
        float dt = dTime.asSeconds();
        loop(dt);
        if (activeScene != NULL) {
          activeScene->_update(dt);
          activeScene->draw(*window);
        }

        window->display();
    }
}
