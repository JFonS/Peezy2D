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

MovieClip *mc = new MovieClip();
void PeezyWin::startUp()
{
    Scene *s = new Scene("esc1");

    mc->addFrame("assets/frame1");
    mc->addKeyFrame("assets/frame2", "salta");
    mc->addFrame("assets/frame3");
    mc->addFrame("assets/frame4");
    mc->addKeyFrame("assets/frame5", "salta", true);
    mc->addFrame("assets/frame6");
    mc->setScale(0.1f, 0.1f);

    s->addChild(mc);

    MovieClip *mc2 = new MovieClip();
    mc2->addFrame("assets/frame2");
    mc2->setPosition(mc->getLocalWidth(), mc->getLocalHeight());
    //mc2->setScale(0.3f, 0.3f);

    mc->addChild(mc2);

    this->pushScene(s);
    mc->gotoAndPlay("salta");

    DbgLog(mc->getLocalBB());
    DbgLog(mc->getGlobalBB());
    DbgLog(mc2->getPosition());
}

void PeezyWin::loop(float dt)
{
    static float y = 0.0f;
    y += dt * 20.0f;
    //mc->setPosition(y, y);
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
