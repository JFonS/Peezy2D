#include "../include/PeezyWin.hpp"
#include "../include/Debug.hpp"
#include "../include/GameObject.hpp"
#include "../include/PText.hpp"
#include "../include/ButtonText.hpp"

SceneStack PeezyWin::scenes = SceneStack();

PeezyWin::PeezyWin(Vector2i size) {
    window = new RenderWindow(VideoMode(size.x, size.y), "");

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
  if(scenes.empty()) return nullptr;
  return scenes.top();
}

void PeezyWin::startUp() {}

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
