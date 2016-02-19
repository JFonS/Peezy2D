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

void PeezyWin::pushScene(Scene* sc)
{
  DbgLog("Pushed scene: " << sc->getName());
  scenes.push(sc);
}

void PeezyWin::popScene() { scenes.pop(); }

void PeezyWin::changeScene(Scene* sc)
{
  if(!scenes.empty()) popScene();
  pushScene(sc);
  return;
}

Scene* PeezyWin::getScene()
{
  if(scenes.empty()) return nullptr;
  return scenes.top();
}

MovieClip *mc, *mc2;
void PeezyWin::startUp()
{
    Scene *s = new Scene("esc1");

    mc = new MovieClip();
    mc->addFrame("assets/frame1");
    mc->addKeyFrame("assets/frame2", "salta");
    mc->addFrame("assets/frame3");
    mc->addFrame("assets/frame4");
    mc->addKeyFrame("assets/frame5", "salta", true);
    mc->addFrame("assets/frame6");
    mc->setScale(0.1f, 0.1f);
    mc->setRotation(45.0f);

    ButtonText *t = new ButtonText();
    t->textDown = t->textIdle = t->textOver = "Hi";

    t->colorIdle = sf::Color::Blue;
    t->colorOver = sf::Color::Green;
    t->colorDown = sf::Color::Red;

    t->goToIdle();

    //t->flicker(10, 500.0f);

    s->addChild(t);
    s->addChild(mc);

    mc2 = new MovieClip();
    mc2->addFrame("assets/frame2");
    mc2->setPosition(500, 500);
    mc2->setScale(0.5f, 0.5f);

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
    mc->setRotation(y);
    mc->setPosition(y, y);
    if(mc2->collidesWith(mc)) DbgLog("COLLIDING");
}

void PeezyWin::_loop()
{
    Clock deltaClock;
    while (window->isOpen())
    {
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window->close();DbgLog("closed");
                return;
            }
            else if (getScene() != NULL)
            {
              PEvent e(event);
              getScene()->onEvent(e);
            }
        }
        window->clear();

        Time dTime = deltaClock.restart();
        float dt = dTime.asSeconds();
        loop(dt);

        if (getScene() != NULL)
        {
          getScene()->update(dt);
          getScene()->draw(*window);
        }
        window->display();
    }
}

void PeezyWin::play() {
    startUp();
    _loop();
}
