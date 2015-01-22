#ifndef PTEXT_H
#define PTEXT_H

#include <SFML/Graphics.hpp>

#include "Debug.hpp"
#include "GameObject.hpp"
#include "ResourceManager.hpp"
#include "Scene.hpp"

using namespace std;
using namespace sf;

class PText : public Text, public Node
{
private:
    bool outline, blowing, flickering, visibleFlicker;
    int  outlineStroke, originalSize, flickerToggleTime, totalTimesFlicker, timesFlickered, blowingTime;
    float blowingMult;
    Color outlineColor;
    Clock *fClock, *bClock;
    Font *font;

public:
    PText();
    PText(const char* str);
    PText(const Vector2f& pos);
    PText(const Font& f);
    PText(const char* str, const Vector2f& pos);
    PText(const Font& f, const Vector2f& pos);
    PText(const char* str, const Font& f, const Vector2f& pos);

    virtual ~PText();

    void setOutline(bool outline);
    void setOutlineColor(Color c);
    void setOutlineStroke(int stroke);

    void blow(float multiplier, int msTotalTime);
    void flicker(int times, float msToggleTime);

    virtual void onDraw(RenderTarget& target, const Transform& transform);
    virtual void onUpdate(float dt);

    Rect<float> getBoundingBox();
};

#endif // PTEXT_H
