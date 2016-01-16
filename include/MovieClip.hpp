#ifndef MOVIECLIP_H
#define MOVIECLIP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "PEvent.hpp"
#include "Debug.hpp"

using namespace std;
using namespace sf;

class MovieClip : public GameObject
{
private:

    vector<Texture*> textures;
    map<string, int> keyFrames;
    int currentFrame;
    string currentKeyFrame;
    float timeSinceLastFrame, timePerFrame;
    bool playing;

public:

    MovieClip();
    virtual ~MovieClip();

    void addFrame(string texturePath);
    void addKeyFrame(string texturePath, string keyFrameName, bool finalFrame = false);

    virtual void onUpdate(float dt);
    virtual void onMouseOver(PEvent &e) override
    {
        DbgLog("LALALLA");
    }

    void gotoAndPlay(string keyFrameName);
    void gotoAndStop(string keyFrameName);
    void play();
    void stop();

    int getKeyFrameNum(string keyFrameName);

};

#endif // MOVIECLIP_H
