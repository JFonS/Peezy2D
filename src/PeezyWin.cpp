#include "../include/PeezyWin.hpp"
#include "../include/Debug.hpp"
#include "../include/GameObject.hpp"
#include "../include/PText.hpp"
#include "../include/ButtonText.hpp"

SceneStack PeezyWin::scenes = SceneStack();

PeezyWin::PeezyWin(Vector2i size) {
    window = new RenderWindow(VideoMode(size.x, size.y), "");
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

void PeezyWin::startUp()
{
    Scene *s = new Scene("esc1");

    MovieClip *mc = new MovieClip();
    mc->addFrame("assets/frame1");
    mc->addKeyFrame("assets/frame2", "salta");
    mc->addFrame("assets/frame3");
    mc->addFrame("assets/frame4");
    mc->addKeyFrame("assets/frame5", "Fsalta");
    mc->addFrame("assets/frame6");

    s->addChild(mc);
    this->pushScene(s);
    mc->gotoAndPlay("salta");
}

void PeezyWin::loop(float dt)
{

}

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

void PeezyWin::play() {
    startUp();
    _loop();
}
