#include "../include/PeezyWin.hpp"
#include "../include/Debug.hpp"
#include "../include/GameObject.hpp"
#include "../include/PText.hpp"

PeezyWin::PeezyWin(Vector2i size) {
    window = new RenderWindow(VideoMode(size.x, size.y), "");
    scenes = SceneStack();
    startUp();
    _loop();
}

PeezyWin::~PeezyWin()
{
    while(!scenes.empty())
    {
        delete scenes.top();
        scenes.pop();
    }
}

void PeezyWin::pushScene(Scene* sc) {
  DbgLog("Pushed scene: " << sc->getName());
  scenes.push(sc); 
}

void PeezyWin::popScene() {
  scenes.pop();
}

void PeezyWin::changeScene(Scene* sc){
  if(scenes.empty()) popScene(); 
  pushScene(sc);
  return;
}

Scene* PeezyWin::peekScene(){
  if(this->scenes.empty()) return nullptr;
  return this->scenes.top(); 
}

void PeezyWin::startUp() {
    //sample stuff (TO REMOVE)
    GameObject* go = new GameObject("red");
    go->setTexture("img.jpg");
    go->setIndex(200);
    //go->setRotation(45.);
    go->setColor(Color::Red);
    go->move(100, 100);

    GameObject* go2 = new GameObject("white");
    go2->setTexture("img.jpg");
    //go2->setRotation(45.);
    go2->move(-10, -10);
    go2->setIndex(50);

    PText* text = new PText("HOLA");
    text->setIndex(200);
    text->setOutline(true);
    text->setOutlineStroke(3);
    text->setOutlineColor(Color::Green);
    //text->rotate(25.);
    
    Scene* scene = new Scene("game");
    scene->addChild(text);
    scene->addChild(go); 
    scene->addChild(go2);
    pushScene(scene);
}

void PeezyWin::loop(float dt){}

void PeezyWin::_loop() {
    Clock deltaClock;
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();DbgLog("closed");
                return;
            }
            else if (peekScene() != NULL) {
              PEvent e(event);
              peekScene()->onEvent(e);
            }
        }
        window->clear();
        Time dTime = deltaClock.restart();
        float dt = dTime.asSeconds();
        loop(dt);
        if (peekScene() != NULL) {
          peekScene()->update(dt);
          peekScene()->draw(*window);
        }
        window->display();
    }
}
